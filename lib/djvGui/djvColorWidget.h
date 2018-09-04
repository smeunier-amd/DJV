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

#include <djvGuiExport.h>

#include <djvColor.h>
#include <djvUtil.h>

#include <QWidget>

#include <memory>

class djvGuiContext;

class QHBoxLayout;

//! \addtogroup djvGuiWidget
//@{

//------------------------------------------------------------------------------
//! \class djvColorWidget
//!
//! This class provides color picker widget.
//------------------------------------------------------------------------------

class DJV_GUI_EXPORT djvColorWidget : public QWidget
{
    Q_OBJECT
    
    //! This property holds the color.    
    Q_PROPERTY(
        djvColor color
        READ     color
        WRITE    setColor
        NOTIFY   colorChanged)
    
public:
    explicit djvColorWidget(djvGuiContext *, QWidget * parent = 0);

    virtual ~djvColorWidget();

    //! Get the color.
    const djvColor & color() const;

    //! Get the minimum floating point value.
    float floatMin() const;

    //! Get the maximum floating point value.
    float floatMax() const;

    //! Set the floating point range.
    void setFloatRange(float min, float max);

    //! Get the bottom layout.
    QHBoxLayout * bottomLayout();

public Q_SLOTS:
    //! Set the color.
    void setColor(const djvColor &);

Q_SIGNALS:
    //! This signal is emitted when the color is changed.
    void colorChanged(const djvColor &);

private Q_SLOTS:
    void intCallback(int);
    void floatCallback(float);
    void formatCallback(int);
    void typeCallback(int);

private:
    void widgetUpdate();
    void valueUpdate();
    
    DJV_PRIVATE_COPY(djvColorWidget);
    
    struct Private;
    std::unique_ptr<Private> _p;
};

//@} // djvGuiWidget

