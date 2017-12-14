#ifndef ISORPG_SETUPUI_H
#define ISORPG_SETUPUI_H

#include <anax/anax.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <collections/drawable.h>
#include <collections/drawableText.h>
#include <components/Comp_UI.h>
#include <components/Comp_Text.h>

class SetUpUI {
public:
    void setUpUI(anax::World &world, float zoom,
                 sf::Texture& bottomTexture,
                 sf::Texture& itemTexture,
                 sf::Texture& abilitiesTexture,
                 sf::Texture& healthBar,
                 sf::Texture& transperant,
                 sf::Font font, sf::View playerCam, anax::Entity player);
};
#endif //ISORPG_SETUPUI_H
