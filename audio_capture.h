#pragma once

#include <QObject>
#include "abstract_audio.h"

class AudioCapture : public QObject, public AbstractAudio
{
    Q_OBJECT
public:
    AudioCapture(int freq, SDL_AudioFormat fmt, Uint8 channels, Uint16 samples);
    void start() override;

    static void recCallback(void* userdata, Uint8* stream, int len);
signals:
    void sample(Uint8* stream, int len);
};
