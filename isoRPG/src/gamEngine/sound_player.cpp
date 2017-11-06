#include <complex>
#include "sound_player.h"
#include <SFML/Audio/Listener.hpp>

namespace
{
    const float ListenerZ = 300.f;
    const float Attenuation = 8.f;
    const float MinDistance2D = 200.f;
    const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

SoundPlayer::SoundPlayer()
        : mSoundBuffer()
        , mSounds()
{
    mSoundBuffer.load(Sound::Test, "assets/sounds/test.wav");
}

void SoundPlayer::play(Sound::ID effect)
{
    play(effect, getListenerPosition());
}

void SoundPlayer::play(Sound::ID effect, sf::Vector2f position)
{
    mSounds.push_back(sf::Sound(mSoundBuffer.get(effect)));
    sf::Sound& sound = mSounds.back();

    sound.setBuffer(mSoundBuffer.get(effect));

    //TODO: Fix coordinates
    sound.setPosition(position.x, -position.y, 0.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);

    sound.play();

}

void SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([] (const sf::Sound& s)
                      {
                          return s.getStatus() == sf::Sound::Stopped;
                      });
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
    //TODO: Fix coordinates
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
    sf::Vector2f position(sf::Listener::getPosition().x, sf::Listener::getPosition().y);

    return position;
}
