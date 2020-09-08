// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2020 Darby Johnston
// All rights reserved.

#include <djvTestLib/Test.h>

namespace djv
{
    namespace AVTest
    {
        class Render3DCameraTest : public Test::ITest
        {
        public:
            Render3DCameraTest(
                const Core::FileSystem::Path& tempPath,
                const std::shared_ptr<Core::Context>&);
            
            void run() override;
        };
        
    } // namespace AVTest
} // namespace djv

