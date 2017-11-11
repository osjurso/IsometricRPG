#ifndef ISORPG_PLAYER_H
#define ISORPG_PLAYER_H

#include <include/components/Comp_animation.h>
#include <SFML/Graphics.hpp>

class Player {

public:
    Player(sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed);
    ~Player();

    void walk(float deltaTime);

    //void draw(sf::RenderWindow& window);

private:
    AnimationComponent animation;

    sf::Sprite sBody;

    sf::Texture tbody;

    unsigned int row;
    float speed;
    bool faceRight;
    bool faceUp;

};


#endif //ISORPG_PLAYER_H
