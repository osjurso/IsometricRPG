#ifndef ISORPG_SOUND_PLAYER_H
#define ISORPG_SOUND_PLAYER_H


#include <include/gameEngine/resource_identifiers.h>
#include <SFML/System/Vector2.hpp>
#include <include/gameEngine/resource_holder.h>
#include <SFML/Audio/Sound.hpp>
#include <list>

class SoundPlayer : private sf::NonCopyable
{
public:
    SoundPlayer();

    void play(SoundEffects::ID effect);

    void removeStoppedSounds();

private:
    SoundBufferHolder mSoundBuffers;
    std::list<sf::Sound> mSounds;
};


#endif //ISORPG_SOUND_PLAYER_H
