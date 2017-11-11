#include "include/components/Player.h"

Player::Player(sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed) :
        animation(texture, imageCount, switchTime) {
    this->speed = speed;
    row = 6;
    faceRight = true;
    faceUp = true;

    sBody.setTexture(texture);
    sBody.setTextureRect(animation.animationRect);
}

Player::~Player() {}

void Player::walk(float deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += speed * deltaTime;

    //if (movement.x == 0.0f || movement.y == 0.0f)
    //  row = 6;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        row = 6;
        faceUp = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        row = 2;
        faceUp = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        row = 0;
        faceRight = false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        row = 4;
        faceRight = true;
    }

    if (movement.x && movement.y) { // TO DO - Finne en måte hvordan man kan stå idle skrått
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            row = 3;
            faceUp = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            row = 1;
            faceUp = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            row = 5;
            faceUp = false;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            row = 7;
            faceUp = false;
        }
    }

    animation.walk(row, deltaTime, faceRight, faceUp ,movement);

    sBody.setTextureRect(animation.animationRect);

    sBody.move(movement);

}