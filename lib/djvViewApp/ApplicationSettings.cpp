//------------------------------------------------------------------------------
// Copyright (c) 2020 Darby Johnston
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions, and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions, and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
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

#include <djvViewApp/ApplicationSettings.h>

#include <djvCore/Context.h>

// These need to be included last on OSX.
#include <djvCore/PicoJSONTemplates.h>
#include <djvUI/ISettingsTemplates.h>

using namespace djv::Core;

namespace djv
{
    namespace ViewApp
    {
        struct ApplicationSettings::Private
        {
            std::shared_ptr<MapSubject<std::string, bool> > settingsBellows;
        };

        void ApplicationSettings::_init(const std::shared_ptr<Core::Context>& context)
        {
            ISettings::_init("djv::ViewApp::ApplicationSettings", context);

            DJV_PRIVATE_PTR();
            p.settingsBellows = MapSubject<std::string, bool>::create();
            _load();
        }

        ApplicationSettings::ApplicationSettings() :
            _p(new Private)
        {}

        std::shared_ptr<ApplicationSettings> ApplicationSettings::create(const std::shared_ptr<Core::Context>& context)
        {
            auto out = std::shared_ptr<ApplicationSettings>(new ApplicationSettings);
            out->_init(context);
            return out;
        }

        std::shared_ptr<IMapSubject<std::string, bool> > ApplicationSettings::observeSettingsBellows() const
        {
            return _p->settingsBellows;
        }

        void ApplicationSettings::setSettingsBellows(const std::map<std::string, bool>& value)
        {
            _p->settingsBellows->setIfChanged(value);
        }

        void ApplicationSettings::load(const picojson::value & value)
        {
            if (value.is<picojson::object>())
            {
                DJV_PRIVATE_PTR();
                const auto & object = value.get<picojson::object>();
                UI::Settings::read("SettingsBellows", object, p.settingsBellows);
            }
        }

        picojson::value ApplicationSettings::save()
        {
            DJV_PRIVATE_PTR();
            picojson::value out(picojson::object_type, true);
            auto & object = out.get<picojson::object>();
            UI::Settings::write("SettingsBellows", p.settingsBellows->get(), object);
            return out;
        }

    } // namespace ViewApp
} // namespace djv

