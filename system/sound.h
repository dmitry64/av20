#ifndef SOUND_H
#define SOUND_H

#include "common/commonfunctions.h"
#include "settings.h"

class Sound
{
    int _volume;
public:
    Sound();
    void init(Settings * settings);
    int volume() const;
    void setVolume(int volume);
};

#endif // SOUND_H
