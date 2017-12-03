//
// Created by Bjornar on 12/3/2017.
//

#ifndef ISORPG_SETUPHEALT_H
#define ISORPG_SETUPHEALT_H


#include <anax/Entity.hpp>

class SetUpHealt {
public:
    void setUpHealt(anax::Entity& entity, float xPos,float yPos, float Height, float Width, float zoom, sf::Color color, sf::View cam);
};


#endif //ISORPG_SETUPHEALT_H
