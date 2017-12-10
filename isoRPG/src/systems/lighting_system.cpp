#include <include/collections/drawable.h>
#include "include/systems/lighting_system.h"

LightingSystem::LightingSystem(sf::Texture &texture)
{
    // Make a lightMap that can cover our screen
    lightMapTexture.create(1920, 1080);

    // Centering the render texture canvas
    sf::View view = lightMapTexture.getView();
    view.setCenter(0, 0);
    lightMapTexture.setView(view);

    // Make our lightMap sprite use the correct texture
    lightMap.setTexture(lightMapTexture.getTexture());

    lightTexture = texture;
    lightTexture.setSmooth(true);

    // Make our lightsprite use our loaded image
    light.setTexture(lightTexture);
    // Set where on the image we will take the sprite (X position, Y position, Width, Height)
    light.setTextureRect(sf::IntRect(0, 0, 512, 512));
    // This will offset where we draw our lights so the center of the light is right over where we want our light to be
    light.setOrigin(256.f, 256.f);
}

void LightingSystem::draw(sf::RenderWindow &window, anax::World& world)
{
    // Adjusting the placement of the view
    sf::View view = window.getView();
    view.setViewport(sf::FloatRect(0.0f, -0.185f, 1.0f, 1.0f));
    window.setView(view);

    // Clear the buffer where we draw the lights, this color could be changed depending on the time of day in the game to show a night/daytime cycle
    lightMapTexture.clear(sf::Color(50, 50, 80));

    // Loop over the lights in the vector
    for (std::size_t i = 0; i < lights.size(); ++i)
    {
        // Set the attributes of the light sprite to those of the current light
        light.setScale(lights[i].scale);
        light.setColor(lights[i].color);
        light.setPosition(lights[i].position);

        //Draw it to the lightMap
        lightMapTexture.draw(light, sf::BlendAdd); // This blendmode is used so the black in our lightimage won't be drawn to the lightMap

    }
    // Need to make sure the rendertexture is displayed
    lightMapTexture.display();

    // What from the lightMap we will draw
    lightMap.setTextureRect(sf::IntRect(0, -70, 1920, 1080));
    // Where on the backbuffer we will draw
    lightMap.setPosition((-lightMap.getGlobalBounds().width/2), 0);


    // This blendmode is used to add the darkness from the lightMap with the parts where we draw ur light image show up brighter
    window.draw(lightMap, sf::BlendMultiply);
}

void LightingSystem::addLight(sf::Vector2f position)
{
    // Create a light
    lights.push_back(Light(position, sf::Vector2f(0.9f, 0.9f),  sf::Color(255, 180, 130, 255)));
}

void LightingSystem::addLight(float x, float y)
{
    addLight(sf::Vector2f(x, y));
}
