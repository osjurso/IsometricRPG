#include <complex>
#include "include/gameEngine/sound_player.h"
#include "SFML/Audio.hpp"

SoundPlayer::SoundPlayer()
        : mSoundBuffers()
        , mSounds()
{
    mSoundBuffers.load(SoundEffects::Test, "assets/sounds/test.wav");
    mSoundBuffers.load(SoundEffects::Click, "assets/sounds/click.wav");

}

void SoundPlayer::play(SoundEffects::ID effect)
{
    mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
    mSounds.back().play();

}

void SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([] (const sf::Sound& s)
                      {
                          return s.getStatus() == sf::Sound::Stopped;
                      });
}
