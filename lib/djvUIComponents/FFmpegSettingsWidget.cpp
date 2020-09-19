// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#include <djvUIComponents/FFmpegSettingsWidget.h>

#include <djvUI/FormLayout.h>
#include <djvUI/GroupBox.h>
#include <djvUI/IntSlider.h>

#include <djvAV/FFmpeg.h>
#include <djvAV/IOSystem.h>

#include <djvSystem/Context.h>

using namespace djv::Core;

namespace djv
{
    namespace UI
    {
        struct FFmpegSettingsWidget::Private
        {
            std::shared_ptr<IntSlider> threadCountSlider;
            std::shared_ptr<FormLayout> layout;
        };

        void FFmpegSettingsWidget::_init(const std::shared_ptr<System::Context>& context)
        {
            ISettingsWidget::_init(context);

            DJV_PRIVATE_PTR();
            setClassName("djv::UI::FFmpegSettingsWidget");

            p.threadCountSlider = IntSlider::create(context);
            p.threadCountSlider->setRange(Math::IntRange(1, 16));

            p.layout = FormLayout::create(context);
            p.layout->addChild(p.threadCountSlider);
            addChild(p.layout);

            _widgetUpdate();

            auto weak = std::weak_ptr<FFmpegSettingsWidget>(std::dynamic_pointer_cast<FFmpegSettingsWidget>(shared_from_this()));
            auto contextWeak = std::weak_ptr<System::Context>(context);
            p.threadCountSlider->setValueCallback(
                [weak, contextWeak](int value)
                {
                    if (auto context = contextWeak.lock())
                    {
                        if (auto widget = weak.lock())
                        {
                            auto io = context->getSystemT<AV::IO::IOSystem>();
                            AV::IO::FFmpeg::Options options;
                            rapidjson::Document document;
                            auto& allocator = document.GetAllocator();
                            fromJSON(io->getOptions(AV::IO::FFmpeg::pluginName, allocator), options);
                            options.threadCount = value;
                            io->setOptions(AV::IO::FFmpeg::pluginName, toJSON(options, allocator));
                        }
                    }
                });
        }

        FFmpegSettingsWidget::FFmpegSettingsWidget() :
            _p(new Private)
        {}

        std::shared_ptr<FFmpegSettingsWidget> FFmpegSettingsWidget::create(const std::shared_ptr<System::Context>& context)
        {
            auto out = std::shared_ptr<FFmpegSettingsWidget>(new FFmpegSettingsWidget);
            out->_init(context);
            return out;
        }

        std::string FFmpegSettingsWidget::getSettingsName() const
        {
            return DJV_TEXT("settings_io_section_ffmpeg");
        }

        std::string FFmpegSettingsWidget::getSettingsGroup() const
        {
            return DJV_TEXT("settings_title_io");
        }

        std::string FFmpegSettingsWidget::getSettingsSortKey() const
        {
            return "ZZZZ";
        }

        void FFmpegSettingsWidget::setLabelSizeGroup(const std::weak_ptr<LabelSizeGroup>& value)
        {
            _p->layout->setLabelSizeGroup(value);
        }

        void FFmpegSettingsWidget::_initEvent(System::Event::Init& event)
        {
            ISettingsWidget::_initEvent(event);
            DJV_PRIVATE_PTR();
            if (event.getData().text)
            {
                p.layout->setText(p.threadCountSlider, _getText(DJV_TEXT("settings_io_ffmpeg_thread_count")) + ":");
            }
        }

        void FFmpegSettingsWidget::_widgetUpdate()
        {
            DJV_PRIVATE_PTR();
            if (auto context = getContext().lock())
            {
                auto io = context->getSystemT<AV::IO::IOSystem>();
                AV::IO::FFmpeg::Options options;
                rapidjson::Document document;
                auto& allocator = document.GetAllocator();
                fromJSON(io->getOptions(AV::IO::FFmpeg::pluginName, allocator), options);
                p.threadCountSlider->setValue(options.threadCount);
            }
        }

    } // namespace UI
} // namespace djv

