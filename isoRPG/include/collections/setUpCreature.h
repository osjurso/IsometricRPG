
#ifndef ISORPG_SETUPPLAYER_H
#define ISORPG_SETUPPLAYER_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <include/components/Comp_animation.h>
#include <include/components/Comp_moveble.h>
#include <include/components/Comp_healt.h>
#include <include/components/Comp_looteble.h>
#include <include/components/Comp_State.h>
#include <include/components/Comp_mousedOver.h>


class SetUpCreature
{
public:
    void setUpPlayer(anax::Entity& entity, sf::RenderWindow& window);

    void setUpEnemie(anax::Entity& entity, sf::Texture& texture, sf::RenderWindow& window, int Xpos, int Ypos, std::string diffeculty);

    void setUpNPC(anax::Entity& entity, sf::Texture& texture, sf::RenderWindow& window, int Xpos, int Ypos);
};

#endif //ISORPG_SETUPPLAYER_H
