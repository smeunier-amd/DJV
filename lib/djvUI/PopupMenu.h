// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvUI/Widget.h>

namespace djv
{
    namespace UI
    {
        class Menu;

        //! Popup menu.
        class PopupMenu : public Widget
        {
            DJV_NON_COPYABLE(PopupMenu);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            PopupMenu();

        public:
            ~PopupMenu() override;

            static std::shared_ptr<PopupMenu> create(const std::shared_ptr<System::Context>&);

            void setMenu(const std::shared_ptr<Menu>&);

            MetricsRole getInsideMargin() const;

            void setInsideMargin(MetricsRole);

        protected:
            void _preLayoutEvent(System::Event::PreLayout&) override;
            void _layoutEvent(System::Event::Layout&) override;

        private:
            DJV_PRIVATE();
        };

    } // namespace UI
} // namespace djv

