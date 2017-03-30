#include "sound.h"

int Sound::volume() const
{
    return _volume;
}

void Sound::setVolume(int volume)
{
    logEvent("Sound","Volume set to " + QString::number(volume) + "%");
    _volume = volume;
}

Sound::Sound() :_volume(0)
{

}

void Sound::init(Settings *settings)
{
    _volume = settings->getSystemSoundVolume();
    logEvent("Sound","Ready");
}
