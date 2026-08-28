#include <system/audio.h>
#include <utils/String16.h>
#include <media/stagefright/AudioSource.h>

// Shim for frameworks/av/media/libstagefright/AudioSource

namespace android {

    // Define the missing constructor symbol that older code expects
    // Old signature: AudioSource(audio_source_t, const String16&, uint32_t, uint32_t, uint32_t, uint32_t, int, int, audio_microphone_direction_t, float)
    extern "C" void _ZN7android11AudioSourceC1E14audio_source_tRKNS_8String16Ejjjji(audio_source_t inputSource, const String16 &opPackageName,
        uint32_t sampleRate, uint32_t channelCount, uint32_t outSampleRate, uint32_t uid, int pid,
        audio_microphone_direction_t selectedMicDirection, float selectedMicFieldDimension)
    {
        // Create audio_attributes_t from audio_source_t
        audio_attributes_t attr = AUDIO_ATTRIBUTES_INITIALIZER;
        attr.source = inputSource;
        attr.usage = AUDIO_USAGE_MEDIA;  // default usage
        
        // Call the current legacy constructor directly using C++
        new AudioSource(&attr, opPackageName, sampleRate, channelCount, outSampleRate, uid, pid,
                        AUDIO_PORT_HANDLE_NONE, selectedMicDirection, selectedMicFieldDimension);
    }

}
