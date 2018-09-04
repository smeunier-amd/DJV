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

#include <djvMath.h>

#if defined(DJV_WINDOWS)
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <float.h>
#include <math.h>
#include <stdlib.h>

//------------------------------------------------------------------------------
// djvMath
//------------------------------------------------------------------------------

djvMath::~djvMath()
{}

const float djvMath::pi     = 3.1415927;
const float djvMath::piX2   = 6.2831853;
const float djvMath::piDiv2 = 1.5707963;
const float djvMath::piDiv4 = 0.7853981;

int djvMath::pow(int value, int power)
{
    return static_cast<int>(::floor(
        ::pow(static_cast<float>(value), static_cast<float>(power))));
}

float djvMath::pow(float value, float power)
{
    return ::powf(value, power);
}

float djvMath::sqrt(float value)
{
    return ::sqrtf(value);
}

float djvMath::exp(float value)
{
    return ::expf(value);
}

float djvMath::log(float value)
{
    return ::logf(value);
}

float djvMath::log10(float value)
{
    return ::log10f(value);
}

float djvMath::antiLog10(float value)
{
    return exp(value * log(10.f));
}

float djvMath::bias(float value, float bias)
{
    return pow(value, log(bias) / log(0.5));
}

namespace
{

const float almostZero = FLT_MIN * 2.f;
const float almostOne  = 1.f - almostZero;

} // namespace

float djvMath::gain(float value, float gain)
{
    if (value < almostZero)
    {
        return 0.f;
    }
    else if (value > almostOne)
    {
        return 1.f;
    }
    const float tmp = log(1.f - gain) / log(0.5);
    if (value < 0.5)
    {
        return pow(2.f * value, tmp) / 2.f;
    }
    else
    {
        return 1.f - pow(2.f * (1.f - value), tmp) / 2.f;
    }
}

float djvMath::softClip(float value, float softClip)
{
    const float tmp = 1.f - softClip;
    if (value > tmp)
    {
        value = tmp + (1.f - exp(-(value - tmp) / softClip)) * softClip;
    }
    return value;
}

float djvMath::sin(float value)
{
    return ::sinf(value);
}

float djvMath::cos(float value)
{
    return ::cosf(value);
}

float djvMath::tan(float value)
{
    return ::tanf(value);
}

float djvMath::arcSin(float value)
{
    return ::asinf(value);
}

float djvMath::arcCos(float value)
{
    return ::acosf(value);
}

float djvMath::arcTan(float value)
{
    return ::atanf(value);
}

float djvMath::arcTan(float a, float b)
{
    return ::atan2f(a, b);
}

//! \todo What is the correct way to handle zero values for the trigonometry
//! functions?
float djvMath::sec(float value)
{
    const float tmp = cos(value);
    return tmp != 0.f ? (1.f / tmp) : 0.f;
}

float djvMath::coSec(float value)
{
    const float tmp = sin(value);
    return tmp != 0.f ? (1.f / tmp) : 0.f;
}

float djvMath::coTan(float value)
{
    const float tmp = tan(value);
    return tmp != 0.f ? (1.f / tmp) : 0.f;
}

namespace
{
float _rand()
{
    return ::rand() / static_cast<float>(RAND_MAX);
}

} // namespace

float djvMath::rand()
{
    return _rand();
}

float djvMath::rand(float value)
{
    return value * _rand();
}

float djvMath::rand(float min, float max)
{
    return min + (max - min) * _rand();
}

void djvMath::randSeed(unsigned int value)
{
    if (! value)
    {
        //! Seed the random number generator with the current time.
#if defined(DJV_WINDOWS)
        value = ::GetTickCount();
#else // DJV_WINDOWS
        struct ::timeval tmp = { 0, 0 };
        ::gettimeofday(&tmp, 0);
        value = tmp.tv_usec;
#endif // DJV_WINDOWS
    }
    ::srand(value);
}

int djvMath::floor(float value)
{
    return static_cast<int>(::floor(value));
}

int djvMath::ceil(float value)
{
    return static_cast<int>(::ceil(value));
}

int djvMath::round(float value)
{
    return static_cast<int>(::round(value));
}

bool djvMath::fuzzyCompare(float a, float b)
{
    return fuzzyCompare(a, b, FLT_EPSILON);
}

bool djvMath::fuzzyCompare(float a, float b, float precision)
{
    return ::fabsf(a - b) < precision;
}

bool djvMath::fuzzyCompare(double a, double b)
{
    return fuzzyCompare(a, b, DBL_EPSILON);
}

bool djvMath::fuzzyCompare(double a, double b, double precision)
{
    return ::fabs(a - b) < precision;
}

