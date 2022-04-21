#include "audio_capture.h"

AudioCapture::AudioCapture(int freq,
                           SDL_AudioFormat fmt,
                           Uint8 channels,
                           Uint16 samples) : AbstractAudio(freq,fmt,channels,samples)
{

}

void AudioCapture::start()
{
    m_want.userdata = this;
    m_want.callback = recCallback;

    m_device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, 1), 1, &m_want, &m_have, 0);

    if (m_device == 0) {
        throw std::runtime_error("Cannot open recording device");
    }

    if (m_have.format != m_want.format) {
        throw std::runtime_error("Didn't get the wanted format");
    }

    SDL_PauseAudioDevice(m_device, 0);
}

void AudioCapture::recCallback(void *userdata, Uint8 *stream, int len)
{
    AudioCapture* capture = static_cast<AudioCapture*>(userdata);
    emit capture->sample(stream, len);
}
