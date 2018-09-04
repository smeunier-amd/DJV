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

#include <djvOpenGlImageTest.h>

#include <djvAssert.h>
#include <djvDebug.h>
#include <djvImageContext.h>
#include <djvOpenGl.h>
#include <djvOpenGlImage.h>
#include <djvOpenGlOffscreenBuffer.h>

#include <QScopedPointer>
#include <QStringList>

using namespace gl;

void djvOpenGlImageTest::run(int &, char **)
{
    DJV_DEBUG("djvOpenGlImageTest::run");
    ctors();
    members();
    operators();
}

void djvOpenGlImageTest::ctors()
{
    DJV_DEBUG("djvOpenGlImageTest::ctors");
    {
        DJV_DEBUG_PRINT(djvOpenGlImageXform());
    }
    {
        DJV_DEBUG_PRINT(djvOpenGlImageColor());
    }
    {
        DJV_DEBUG_PRINT(djvOpenGlImageLevels());
    }
    {
        DJV_DEBUG_PRINT(djvOpenGlImageDisplayProfile());
    }
    {
        DJV_DEBUG_PRINT(djvOpenGlImageFilter());
        DJV_DEBUG_PRINT(djvOpenGlImageFilter(
            djvOpenGlImageFilter::BOX, djvOpenGlImageFilter::TRIANGLE));
    }
    {
        DJV_DEBUG_PRINT(djvOpenGlImageOptions());
    }
}

void djvOpenGlImageTest::members()
{
    DJV_DEBUG("djvOpenGlImageTest::members");
    {
        DJV_DEBUG_PRINT(djvOpenGlImageXform::xformMatrix(djvOpenGlImageXform()));
    }
    {
        DJV_DEBUG_PRINT(djvOpenGlImageColor::brightnessMatrix(1.f, 0.f, 0.f));
        DJV_DEBUG_PRINT(djvOpenGlImageColor::contrastMatrix(1.f, 0.f, 0.f));
        DJV_DEBUG_PRINT(djvOpenGlImageColor::saturationMatrix(1.f, 0.f, 0.f));
        DJV_DEBUG_PRINT(djvOpenGlImageColor::colorMatrix(djvOpenGlImageColor()));
    }
    {
        DJV_DEBUG_PRINT(djvOpenGlImageLevels::colorLut(djvOpenGlImageLevels(), .5f));
    }
    {
        DJV_ASSERT(djvOpenGlImageFilter::toGl(djvOpenGlImageFilter::NEAREST) != GL_NONE);
        DJV_ASSERT(djvOpenGlImageFilter::toGl(djvOpenGlImageFilter::LINEAR) != GL_NONE);
        DJV_ASSERT(djvOpenGlImageFilter::toGl(djvOpenGlImageFilter::BOX) == GL_NONE);
    }
    {
        djvImageContext context;
        for (int i = 0; i < djvPixel::PIXEL_COUNT; ++i)
        {
            const djvPixel::PIXEL pixel = static_cast<djvPixel::PIXEL>(i);
            DJV_DEBUG_PRINT("pixel = " << pixel);
            djvPixelData
                a(djvPixelDataInfo(1, 1, pixel)),
                b(djvPixelDataInfo(1, 1, pixel));
            djvColor color(pixel);
            djvColorUtil::convert(djvColor(0.5), color);
            DJV_DEBUG_PRINT("color = " << color);
            memcpy(a.data(), color.data(), a.dataByteCount());
            DJV_DEBUG_PRINT("pixel = " << djvOpenGlImage::pixel(a, 0, 0));

            djvOpenGlImage::copy(a, b);
            DJV_DEBUG_PRINT("compare = " << (a == b));
            djvOpenGlImage::average(a, color);

            DJV_DEBUG_PRINT("average = " << color);
            djvColor min, max;
            djvOpenGlImage::histogram(a, b, 1, min, max);

            DJV_DEBUG_PRINT("histogram = " << b);
            DJV_DEBUG_PRINT("min = " << min);
            DJV_DEBUG_PRINT("max = " << max);
            DJV_DEBUG_PRINT("");
        }
    }
}

void djvOpenGlImageTest::operators()
{
    DJV_DEBUG("djvOpenGlImageTest::operators");
    {
        djvOpenGlImageXform a, b;
        a.mirror = b.mirror = djvPixelDataInfo::Mirror(true, true);
        DJV_ASSERT(a == b);
        DJV_ASSERT(a != djvOpenGlImageXform());
    }
    {
        djvOpenGlImageColor a, b;
        a.brightness = b.brightness = 2.f;
        DJV_ASSERT(a == b);
        DJV_ASSERT(a != djvOpenGlImageColor());
    }
    {
        djvOpenGlImageLevels a, b;
        a.gamma = b.gamma = 2.2f;
        DJV_ASSERT(a == b);
        DJV_ASSERT(a != djvOpenGlImageLevels());
    }
    {
        djvOpenGlImageDisplayProfile a, b;
        a.softClip = b.softClip = .5f;
        DJV_ASSERT(a == b);
        DJV_ASSERT(a != djvOpenGlImageDisplayProfile());
    }
    {
        djvOpenGlImageFilter a, b;
        a.min = b.min = djvOpenGlImageFilter::BOX;
        DJV_ASSERT(a == b);
        DJV_ASSERT(a != djvOpenGlImageFilter());
    }
    {
        djvOpenGlImageOptions a, b;
        a.channel = b.channel = djvOpenGlImageOptions::CHANNEL_RED;
        DJV_ASSERT(a == b);
        DJV_ASSERT(a != djvOpenGlImageOptions());
    }
    {
        djvOpenGlImageXform a;
        a.mirror   = djvPixelDataInfo::Mirror(true, true);
        a.position = glm::vec2(1.f, 2.f);
        a.scale    = glm::vec2(3.f, 4.f);
        a.rotate   = 5.f;
        QStringList tmp;
        tmp << a;
        djvOpenGlImageXform b;
        tmp >> b;
        DJV_ASSERT(a == b);
    }
    {
        djvOpenGlImageColor a;
        a.brightness = 1.f;
        a.contrast   = 2.f;
        a.saturation = 3.f;
        QStringList tmp;
        tmp << a;
        djvOpenGlImageColor b;
        tmp >> b;
        DJV_ASSERT(a == b);
    }
    {
        djvOpenGlImageLevels a;
        a.inLow   = 1.f;
        a.inHigh  = 2.f;
        a.gamma   = 3.f;
        a.outLow  = 4.f;
        a.outHigh = 5.f;
        QStringList tmp;
        tmp << a;
        djvOpenGlImageLevels b;
        tmp >> b;
        DJV_ASSERT(a == b);
    }
    {
        DJV_DEBUG_PRINT(djvOpenGlImageFilter::BELL);
        DJV_DEBUG_PRINT(djvOpenGlImageOptions::CHANNEL_RED);
    }
}

