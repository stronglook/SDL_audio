#include <QCoreApplication>
#include "audio_capture.h"
#include "audio_playback.h"

#ifdef __MINGW32__
    #undef main
#endif


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    AudioCapture cap(44100, AUDIO_S16SYS, 1, 1024);
    AudioPlayback pb(44100, AUDIO_S16SYS, 1, 1024);
    pb.start();

    QObject::connect(&cap, &AudioCapture::sample, [&](Uint8* stream, int len)
    {
        pb.play(stream, len);
    });

    cap.start();


    /*
        //Calculate per sample bytes
        int bytesPerSample = want.channels * ( SDL_AUDIO_BITSIZE( want.format ) / 8 );

        //Calculate bytes per second
        int bytesPerSecond = want.freq * bytesPerSample;

        //Calculate buffer size
        gBufferByteSize = RECORDING_BUFFER_SECONDS * bytesPerSecond;

        //Calculate max buffer use
        gBufferByteMaxPosition = MAX_RECORDING_SECONDS * bytesPerSecond;

        //Allocate and initialize byte buffer
        gRecordingBuffer = new Uint8[ gBufferByteSize ];
        memset( gRecordingBuffer, 0, gBufferByteSize );
    */

    return app.exec();
}
