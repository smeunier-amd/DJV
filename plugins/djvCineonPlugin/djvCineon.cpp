//------------------------------------------------------------------------------
// Copyright (c) 2004-2015 Darby Johnston
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions, and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions, and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the names of the copyright holders nor the names of any
//   contributors may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

#include <djvCineon.h>

#include <djvAssert.h>

#include <QCoreApplication>

//------------------------------------------------------------------------------
// djvCineon::Options
//------------------------------------------------------------------------------

djvCineon::Options::Options() :
    inputColorProfile (djvCineon::COLOR_PROFILE_AUTO),
    outputColorProfile(djvCineon::COLOR_PROFILE_FILM_PRINT)
{}

//------------------------------------------------------------------------------
// djvCineon
//------------------------------------------------------------------------------

const QString djvCineon::staticName = "Cineon";

const QStringList & djvCineon::colorProfileLabels()
{
    static const QStringList data = QStringList() <<
        qApp->translate("djvCineon", "Auto") <<
        qApp->translate("djvCineon", "None") <<
        qApp->translate("djvCineon", "Film Print");
    DJV_ASSERT(data.count() == COLOR_PROFILE_COUNT);
    return data;
}

djvPixelData djvCineon::linearToFilmPrintLut(const LinearToFilmPrint & value)
{
    //DJV_DEBUG("djvCineon::linearToFilmPrintLut");
    //DJV_DEBUG_PRINT("black = " << value.black);
    //DJV_DEBUG_PRINT("white = " << value.white);
    //DJV_DEBUG_PRINT("gamma = " << value.gamma);
    djvPixelData out(djvPixelDataInfo(1024, 1, djvPixel::L_F32));
    const int size = out.w();
    //DJV_DEBUG_PRINT("size = " << size);
    djvPixel::F32_T * data = reinterpret_cast<djvPixel::F32_T *>(out.data());
    const float gain =
        1.f / (
            1.f - djvMath::pow(
                djvMath::pow(10.f, (value.black - value.white) * .002f / .6f),
                value.gamma / 1.7f));
    const float offset = gain - 1.f;
    //DJV_DEBUG_PRINT("gain = " << gain * 255);
    //DJV_DEBUG_PRINT("offset = " << offset * 255);
    for (int i = 0; i < size; ++i)
    {
        data[i] = i / djvPixel::F32_T(size - 1);
    }
    for (int i = 0; i < size; ++i)
    {
        data[i] = djvPixel::F32_T(
            value.white / 1023.f +
            djvMath::log10(
                djvMath::pow((data[i] + offset) / gain, 1.7f / value.gamma)) /
                    (2.048f / .6f));
        //DJV_DEBUG_PRINT("lut[" << i << "] = " <<
        //    data[i] << " " << static_cast<int>(data[i] * 1024));
    }
    return out;
}

djvPixelData djvCineon::filmPrintToLinearLut(const FilmPrintToLinear & value)
{
    //DJV_DEBUG("djvCineon::filmPrintToLinearLut");
    //DJV_DEBUG_PRINT("black = " << value.black);
    //DJV_DEBUG_PRINT("white = " << value.white);
    //DJV_DEBUG_PRINT("gamma = " << value.gamma);
    //DJV_DEBUG_PRINT("soft clip = " << value.softClip);
    djvPixelData out(djvPixelDataInfo(1024, 1, djvPixel::L_F32));
    const int size = out.w();
    //DJV_DEBUG_PRINT("size = " << size);
    djvPixel::F32_T * data = reinterpret_cast<djvPixel::F32_T *>(out.data());
    const float gain =
        1.f / (
            1.f - djvMath::pow(
                djvMath::pow(10.f, (value.black - value.white) * .002f / .6f),
                value.gamma / 1.7f));
    const float offset = gain - 1.f;
    //DJV_DEBUG_PRINT("gain = " << gain * 255);
    //DJV_DEBUG_PRINT("offset = " << offset * 255);
    const int breakPoint = value.white - value.softClip;
    const float kneeOffset =
        djvMath::pow(
            djvMath::pow(10.f, (breakPoint - value.white) * .002f / .6f),
            value.gamma / 1.7f
        ) *
        gain - offset;
    const float kneeGain =
        (
            (255 - (kneeOffset * 255)) /
            djvMath::pow(5.f * value.softClip, value.softClip / 100.f)
        ) / 255.f;
    //DJV_DEBUG_PRINT("break point = " << breakPoint);
    //DJV_DEBUG_PRINT("knee offset = " << kneeOffset * 255);
    //DJV_DEBUG_PRINT("knee gain = " << kneeGain * 255);
    for (int i = 0; i < size; ++i)
    {
        data[i] = i / djvPixel::F32_T(size - 1);
    }
    for (int i = 0; i < size; ++i)
    {
        const int tmp = static_cast<int>(data[i] * 1023.f);
        if (tmp < value.black)
        {
            data[i] = 0.f;
        }
        else if (tmp > breakPoint)
        {
            data[i] = djvPixel::F32_T((djvMath::pow(
                static_cast<float>(tmp - breakPoint),
                value.softClip / 100.f) *
                kneeGain * 255 + kneeOffset * 255) / 255.f);
        }
        else
        {
            data[i] = djvPixel::F32_T(djvMath::pow(
                djvMath::pow(10.f, (tmp - value.white) * .002f / .6f),
                value.gamma / 1.7f) * gain - offset);
        }
        //DJV_DEBUG_PRINT("lut[" << i << "] = " <<
        //  in[i] << " " << static_cast<int>(in[i] * 255.f));
    }
    return out;
}

const QStringList & djvCineon::tagLabels()
{
    static const QStringList data = QStringList() <<
        qApp->translate("djvCineon", "Source Offset") <<
        qApp->translate("djvCineon", "Source File") <<
        qApp->translate("djvCineon", "Source Time") <<
        qApp->translate("djvCineon", "Source Input Device") <<
        qApp->translate("djvCineon", "Source Input Model") <<
        qApp->translate("djvCineon", "Source Input Serial") <<
        qApp->translate("djvCineon", "Source Input Pitch") <<
        qApp->translate("djvCineon", "Source Gamma") <<
        qApp->translate("djvCineon", "Film Format") <<
        qApp->translate("djvCineon", "Film Frame") <<
        qApp->translate("djvCineon", "Film Frame Rate") <<
        qApp->translate("djvCineon", "Film Frame ID") <<
        qApp->translate("djvCineon", "Film Slate");
    DJV_ASSERT(data.count() == TAG_COUNT);
    return data;
}

const QStringList & djvCineon::optionsLabels()
{
    static const QStringList data = QStringList() <<
        qApp->translate("djvCineon", "Input Color Profile") <<
        qApp->translate("djvCineon", "Input Film Print") <<
        qApp->translate("djvCineon", "Output Color Profile") <<
        qApp->translate("djvCineon", "Output Film Print");
    DJV_ASSERT(data.count() == OPTIONS_COUNT);
    return data;
}

bool operator == (
    const djvCineon::LinearToFilmPrint & a,
    const djvCineon::LinearToFilmPrint & b)
{
    return
        a.black == b.black &&
        a.white == b.white &&
        a.gamma == b.gamma;
}

bool operator == (
    const djvCineon::FilmPrintToLinear & a,
    const djvCineon::FilmPrintToLinear & b)
{
    return
        a.black == b.black &&
        a.white == b.white &&
        a.gamma == b.gamma &&
        a.softClip == b.softClip;
}

bool operator != (
    const djvCineon::LinearToFilmPrint & a,
    const djvCineon::LinearToFilmPrint & b)
{
    return ! (a == b);
}

bool operator != (
    const djvCineon::FilmPrintToLinear & a,
    const djvCineon::FilmPrintToLinear & b)
{
    return ! (a == b);
}

QStringList & operator >> (QStringList & in,
    djvCineon::LinearToFilmPrint & out) throw (QString)
{
    return in >>
        out.black >>
        out.white >>
        out.gamma;
}

QStringList & operator << (QStringList & out,
    const djvCineon::LinearToFilmPrint & in)
{
    return out <<
        in.black <<
        in.white <<
        in.gamma;
}

QStringList & operator >> (QStringList & in,
    djvCineon::FilmPrintToLinear & out) throw (QString)
{
    return in >>
        out.black >>
        out.white >>
        out.gamma >>
        out.softClip;
}

QStringList & operator << (QStringList & out,
    const djvCineon::FilmPrintToLinear & in)
{
    return out <<
        in.black <<
        in.white <<
        in.gamma <<
        in.softClip;
}

_DJV_STRING_OPERATOR_LABEL(djvCineon::COLOR_PROFILE,
    djvCineon::colorProfileLabels())
