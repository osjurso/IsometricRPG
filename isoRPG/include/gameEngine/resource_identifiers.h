#ifndef ISORPG_RESOURCE_IDENTIFIERS_H
#define ISORPG_RESOURCE_IDENTIFIERS_H

namespace sf
{
    class Texture;
    class Font;
    class SoundBuffer;
}

namespace Textures
{
    enum ID
    {
        Hero,
        TitleLogo,
        TitleText,
        MenuBackdrop,
        MenuFire,
        SettingsBackdorp,
        SettingsSlider,
        SettingKnob,
        CharacterBox
    };
}

namespace Fonts
{
    enum ID
    {
        Main,
        RPG,
    };
}

namespace Music
{
    enum ID
    {
        Menu,
        Test,
    };
}

namespace Sound
{
    enum ID
    {
        Test,
    };
}

namespace Music
{
    enum ID
    {
        Menu,
        Test,
    };
}

namespace Sound
{
    enum ID
    {
        Test,
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, Sound::ID> SoundBufferHolder;


#endif //ISORPG_RESOURCE_IDENTIFIERS_H
