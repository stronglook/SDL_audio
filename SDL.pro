QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        abstract_audio.cpp \
        audio_capture.cpp \
        audio_playback.cpp \
        main.cpp

LIBS += -L"C:\Software\SDL2-2.0.20\lib\x64" -lSDL2
LIBS += -L"C:\Software\SDL2_mixer-2.0.4\lib" -lSDL2_mixer
INCLUDEPATH += "C:\Software\SDL2-2.0.20\include"
INCLUDEPATH += "C:\Software\SDL2_mixer-2.0.4"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    abstract_audio.h \
    audio_capture.h \
    audio_playback.h
