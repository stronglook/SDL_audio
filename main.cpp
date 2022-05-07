#include <QCoreApplication>
#include "audio_capture.h"
#include "audio_playback.h"
#include "SDL_mixer.h"

#ifdef __MINGW32__
    #undef main
#endif


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    AudioCapture cap(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    //AudioPlayback pb(44100, AUDIO_S16SYS, 1, 1024);
    //pb.start();
    int result = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    if( result < 0 ) {
        qDebug() << "Unable to open audio: " << SDL_GetError();
    } else if (/*Mix_AllocateChannels(4) < 0*/0) {
        qDebug() << "Unable to allocate mixing channels: ", SDL_GetError();
    }

    auto wavChunk = Mix_LoadWAV("C:/Software/file.wav");
    Mix_PlayChannel(-1, wavChunk, 0);

    QObject::connect(&cap, &AudioCapture::sample, [&](Uint8* stream, int len)
    {
        Uint8* buf = static_cast<Uint8*>(SDL_malloc(len));
        std::memcpy(buf,stream,len);
        Mix_Chunk* chunk = Mix_QuickLoad_RAW(buf, len);
        Mix_PlayChannel(-1, chunk, 0);
        // Mix_FreeChunk(chunk);
        // pb.play(stream, len);
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
