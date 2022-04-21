#pragma once

#include <stdexcept>
#include "SDL.h"

class AbstractAudio
{
public:
    AbstractAudio(int freq, SDL_AudioFormat fmt, Uint8 channels, Uint16 samples);
    virtual void start() = 0;
    virtual ~AbstractAudio() = default;
    void stop();

protected:
    SDL_AudioDeviceID m_device;
    SDL_AudioSpec m_want;
    SDL_AudioSpec m_have;
};
