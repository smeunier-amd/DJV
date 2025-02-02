// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2020 Darby Johnston
// All rights reserved.

#include <djvAVTest/PPMTest.h>

#include <djvAV/PPM.h>

#include <djvCore/Error.h>

using namespace djv::Core;
using namespace djv::AV;
using namespace djv::AV::IO;

namespace djv
{
    namespace AVTest
    {
        PPMTest::PPMTest(
            const System::File::Path& tempPath,
            const std::shared_ptr<System::Context>& context) :
            ITest(
                "djv::AVTest::PPMTest",
                System::File::Path(tempPath, "PPMTest"),
                context)
        {}
        
        void PPMTest::run()
        {
            _serialize();
        }
        
        void PPMTest::_serialize()
        {
            {
                PPM::Options options;
                rapidjson::Document document;
                auto& allocator = document.GetAllocator();
                auto json = toJSON(options, allocator);
                PPM::Options options2;
                fromJSON(json, options2);
                DJV_ASSERT(options == options2);
            }
            
            try
            {
                auto json = rapidjson::Value(rapidjson::kObjectType);
                PPM::Options options;
                fromJSON(json, options);
                DJV_ASSERT(options == options);
            }
            catch (const std::exception& e)
            {
                _print(Error::format(e.what()));
            }
        }
        
    } // namespace AVTest
} // namespace djv

