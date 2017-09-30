#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "include/util/utility.h"

void centerOrigin(sf::Sprite &sprite)
{
 sprite.setOrigin(sprite.getLocalBounds().width / 2,
                  sprite.getLocalBounds().height / 2);
}

void centerOrigin(sf::Text &text)
{
    text.setOrigin(text.getLocalBounds().width / 2,
                   text.getLocalBounds().height / 2);
}
