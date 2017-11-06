#ifndef ISORPG_MUSIC_PLAYER_H
#define ISORPG_MUSIC_PLAYER_H


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>
#include <map>
#include "resource_identifiers.h"

class MusicPlayer : private sf::NonCopyable
{
public:
    MusicPlayer();

    void play(Music::ID theme);
    void stop();

    void setPaused(bool paused);
    void setVolume(float volume);

private:
    sf::Music mMusic;
    std::map<Music::ID, std::string> mFileNames;
    float mVolume;

};


#endif //ISORPG_MUSIC_PLAYER_H
