#include "audio_playback.h"

AudioPlayback::AudioPlayback(int freq, SDL_AudioFormat fmt, Uint8 channels, Uint16 samples)
    : AbstractAudio(freq, fmt, channels, samples){}

void AudioPlayback::start()
{
    m_want.callback = &pbCallback;
    m_want.userdata = this;

    m_device = SDL_OpenAudioDevice(NULL, SDL_FALSE, &m_want, &m_have, 0);
    if (m_device == 0) {
        throw std::runtime_error("Failed to open audio device");
    }

    SDL_PauseAudioDevice(m_device, 0);
}

void AudioPlayback::play(Uint8* buffer, int len)
{
    m_buffer = buffer;
    m_availableBytes = len;
}

void AudioPlayback::pbCallback(void *userdata, Uint8 *stream, int len)
{
    AudioPlayback* capture = static_cast<AudioPlayback*>(userdata);
    while (capture->m_availableBytes == 0);

    if (len != capture->m_availableBytes) {
        throw std::runtime_error("Available bytes does not match pending bytes");
    }

    std::memcpy(stream, capture->m_buffer, len);
    capture->m_availableBytes = 0;
}
