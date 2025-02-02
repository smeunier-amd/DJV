// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvViewApp/IViewAppSystem.h>

namespace djv
{
    namespace ViewApp
    {
        //! Audio system.
        class AudioSystem : public IViewAppSystem
        {
            DJV_NON_COPYABLE(AudioSystem);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            AudioSystem();

        public:
            ~AudioSystem() override;

            static std::shared_ptr<AudioSystem> create(const std::shared_ptr<System::Context>&);

            int getSortKey() const override;
            std::map<std::string, std::shared_ptr<UI::Action> > getActions() const override;
            std::vector<std::shared_ptr<UI::Menu> > getMenus() const override;

        protected:
            void _actionsUpdate();

            void _textUpdate() override;
            void _shortcutsUpdate() override;

        private:
            DJV_PRIVATE();
        };

    } // namespace ViewApp
} // namespace djv

