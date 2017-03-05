#ifndef SOUND_H
#define SOUND_H


class Sound
{
    int _volume;
public:
    Sound();
    void init();
    int volume() const;
    void setVolume(int volume);
};

#endif // SOUND_H
