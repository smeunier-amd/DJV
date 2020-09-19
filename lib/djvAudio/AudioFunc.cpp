// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#include <djvAudio/AudioFunc.h>

#include <algorithm>
#include <array>

namespace djv
{
    namespace Audio
    {
        /*std::string getALErrorString(ALenum value)
        {
            std::string out = DJV_TEXT("error_unknown");
            switch (value)
            {
            case AL_OUT_OF_MEMORY: out = DJV_TEXT("error_al_out_of_memory"); break;
            case AL_INVALID_VALUE: out = DJV_TEXT("error_al_invalid_value"); break;
            case AL_INVALID_ENUM:  out = DJV_TEXT("error_al_invalid_enum");  break;
            default: break;
            }
            return out;
        }*/
        
        DJV_ENUM_HELPERS_IMPLEMENTATION(Type);

    } // namespace Audio

    DJV_ENUM_SERIALIZE_HELPERS_IMPLEMENTATION(
        Audio,
        Type,
        DJV_TEXT("audio_type_none"),
        DJV_TEXT("audio_type_u8"),
        DJV_TEXT("audio_type_s16"),
        DJV_TEXT("audio_type_s32"),
        DJV_TEXT("audio_type_f32"),
        DJV_TEXT("audio_type_f64"));

} // namespace djv

