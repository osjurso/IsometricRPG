#ifndef ISORPG_SOUND_PLAYER_H
#define ISORPG_SOUND_PLAYER_H


#include <include/gameEngine/resource_identifiers.h>
#include <SFML/System/Vector2.hpp>
#include <include/gameEngine/resource_holder.h>
#include <SFML/Audio/Sound.hpp>
#include <list>

class SoundPlayer
{
public:
    SoundPlayer();
    void play(Sound::ID effect);
    void play(Sound::ID effect, sf::Vector2f position);

    void removeStoppedSounds();
    void setListenerPosition(sf::Vector2f position);
    sf::Vector2f getListenerPosition() const;

private:
    SoundBufferHolder mSoundBuffer;
    std::list<sf::Sound> mSounds;

};


#endif //ISORPG_SOUND_PLAYER_H
