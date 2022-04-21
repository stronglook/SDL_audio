#pragma once

#include <atomic>
#include <cstring>
#include "abstract_audio.h"

class AudioPlayback : public AbstractAudio
{
public:
    AudioPlayback(int freq, SDL_AudioFormat fmt, Uint8 channels, Uint16 samples);
    void start() override;
    void play(Uint8* buffer, int len);

private:
    std::atomic<int> m_availableBytes = 0;
    Uint8* m_buffer;

    static void pbCallback(void *userdata, Uint8 *stream, int len);
};

