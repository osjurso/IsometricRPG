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

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif //ISORPG_RESOURCE_IDENTIFIERS_H
