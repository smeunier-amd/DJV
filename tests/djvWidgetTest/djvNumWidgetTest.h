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

#pragma once

#include <djvAbstractWidgetTest.h>

#include <QWidget>

class djvFloatDisplay;
class djvFloatEdit;
class djvFloatEditSlider;
class djvIntDisplay;
class djvIntEdit;
class djvIntEditSlider;

class djvNumWidgetTest : public djvAbstractWidgetTest
{
    Q_OBJECT
    
public:

    djvNumWidgetTest(djvGuiContext *);

    virtual QString name();

    virtual void run(const QStringList & args = QStringList());
};

class djvNumWidgetTestWidget : public QWidget
{
    Q_OBJECT

public:

    djvNumWidgetTestWidget(djvGuiContext *);
    
private Q_SLOTS:

    void intCallback(int);
    void floatCallback(float);

    void widgetUpdate();
    
private:

    int   _intValue;
    float _floatValue;
    
    djvIntEdit *         _intEdit;
    djvIntDisplay *      _intDisplay;
    djvIntEditSlider *   _intSlider;
    djvFloatEdit *       _floatEdit;
    djvFloatDisplay *    _floatDisplay;
    djvFloatEditSlider * _floatSlider;
};
