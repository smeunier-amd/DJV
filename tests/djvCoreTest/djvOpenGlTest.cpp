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

#include <djvOpenGlTest.h>

#include <djvAssert.h>
#include <djvDebug.h>
#include <djvImageContext.h>
#include <djvOpenGl.h>
#include <djvOpenGlOffscreenBuffer.h>

#include <QScopedPointer>
#include <QString>

using namespace gl;

void djvOpenGlTest::run(int &, char **)
{
    DJV_DEBUG("djvOpenGlTest::run");
    members();
}

void djvOpenGlTest::members()
{
    DJV_DEBUG("djvOpenGlTest::members");
    djvImageContext context;
    QScopedPointer<djvOpenGlOffscreenBuffer> buffer(
        new djvOpenGlOffscreenBuffer(djvPixelDataInfo(100, 100, djvPixel::RGBA_U8)));
    djvOpenGlOffscreenBufferScope bufferScope(buffer.data());
    DJV_DEBUG_PRINT("buffer = " << buffer->info());
    DJV_DEBUG_PRINT("buffer id = " << buffer->id());
    DJV_DEBUG_PRINT("buffer texture = " << buffer->texture());
    {
        djvOpenGlUtil::ortho(glm::ivec2(100, 100));
        DJV_ASSERT(GL_NO_ERROR == ::glGetError());
        djvOpenGlUtil::color(djvColor(0.5));
        DJV_ASSERT(GL_NO_ERROR == ::glGetError());
        djvOpenGlUtil::drawBox(djvBox2i(25, 25, 50, 50));
        DJV_ASSERT(GL_NO_ERROR == ::glGetError());
        djvOpenGlUtil::drawBox(djvBox2f(50.f, 50.f, 50.f, 50.f));
        DJV_ASSERT(GL_NO_ERROR == ::glGetError());
        glm::vec2 uv[4] =
        {
            glm::vec2(0.f, 0.f),
            glm::vec2(0.1, 0.f),
            glm::vec2(0.1, 1.f),
            glm::vec2(0.f, 1.f)
        };
        djvOpenGlUtil::drawBox(djvBox2i(25, 25, 50, 50), uv);
        DJV_ASSERT(GL_NO_ERROR == ::glGetError());
        djvOpenGlUtil::drawBox(djvBox2f(50.f, 50.f, 50.f, 50.f), uv);
        DJV_ASSERT(GL_NO_ERROR == ::glGetError());
    }
    {
        for (int i = 0; i < djvPixel::PIXEL_COUNT; ++i)
        {
            DJV_ASSERT(djvOpenGlUtil::format(static_cast<djvPixel::PIXEL>(i)) != GL_NONE);
            DJV_ASSERT(djvOpenGlUtil::type(static_cast<djvPixel::PIXEL>(i)) != GL_NONE);
        }
    }
}

