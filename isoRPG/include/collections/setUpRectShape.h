#ifndef ISORPG_SETUPHEALT_H
#define ISORPG_SETUPHEALT_H

#include <anax/Entity.hpp>

class SetUpRectShape {
public:
    void setUpRectShape(anax::Entity &entity, float xPos, float yPos, float Height, float Width, float zoom,
                        sf::Color color, sf::View cam);
};


#endif //ISORPG_SETUPHEALT_H
