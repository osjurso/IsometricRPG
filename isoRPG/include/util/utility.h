#ifndef ISORPG_UTILITY_H
#define ISORPG_UTILITY_H

namespace sf
{
    class Sprite;
    class Text;
    class View;
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);


#endif //ISORPG_UTILITY_H
