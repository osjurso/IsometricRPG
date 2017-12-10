#ifndef ISORPG_LIGHTING_SYSTEM_H
#define ISORPG_LIGHTING_SYSTEM_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <anax/World.hpp>

struct Light
{
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Color color;
    Light(sf::Vector2f nposition, sf::Vector2f nscale, sf::Color ncolor) :
            position(nposition),
            scale(nscale),
            color(ncolor)
    {
    }
};

class LightingSystem
{
public:
    LightingSystem(sf::Texture &texture);

    void draw(sf::RenderWindow& window, anax::World& world);

    void addLight(sf::Vector2f position);
    void addLight(float x, float y);

private:
    sf::Texture lightTexture;
    sf::Sprite light;

    sf::RenderTexture lightMapTexture;
    sf::Sprite lightMap;

    std::vector<Light> lights; // Contains all the lights
};


#endif //ISORPG_LIGHTING_SYSTEM_H
