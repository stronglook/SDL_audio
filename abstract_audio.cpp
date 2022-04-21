#include "abstract_audio.h"

AbstractAudio::AbstractAudio(int freq, SDL_AudioFormat fmt, Uint8 channels, Uint16 samples)
{
    SDL_Init(SDL_INIT_AUDIO);

    SDL_zero(m_want);
    SDL_zero(m_have);

    m_want.freq = freq;
    m_want.format = fmt;
    m_want.channels = channels;
    m_want.samples = samples;
}

void AbstractAudio::stop()
{
    SDL_PauseAudioDevice(m_device, 1);
}
