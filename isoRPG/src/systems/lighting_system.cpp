#include <include/collections/drawable.h>
#include <iostream>
#include "include/systems/lighting_system.h"

LightingSystem::LightingSystem(sf::Texture &texture)
        : ambientLight(sf::Color(50, 50, 80))
        , duskTime(sf::seconds(720.0f))
        , dawnTime(sf::seconds(1440.0f))
        , dayNightCycle(false)
{
    // Make a lightMap that can cover our screen
    lightMapTexture.create(4096, 2160);

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

    clock.restart();
}

void LightingSystem::draw(sf::RenderWindow &window, anax::World& world)
{
    // Adjusting the placement of the view
    sf::View view = window.getView();
    view.setViewport(sf::FloatRect(0.0f, -0.185f, 1.0f, 1.0f));
    window.setView(view);

    // Clear the buffer where we draw the lights, this color could be changed depending on the time of day in the game to show a night/daytime cycle
    lightMapTexture.clear(ambientLight);

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
    lightMap.setTextureRect(sf::IntRect(0, -70, 4096, 2160));
    // Where on the backbuffer we will draw
    lightMap.setPosition((-lightMap.getGlobalBounds().width/2), 0);


    // This blendmode is used to add the darkness from the lightMap with the parts where we draw ur light image show up brighter
    window.draw(lightMap, sf::BlendMultiply);
}

void LightingSystem::update(float dt)
{
    if (dayNightCycle)
    {
        currentTime = clock.getElapsedTime();
        // "From dusk til dawn"
        if (currentTime < duskTime)
        {
            const float ratio{ currentTime / duskTime };
            ambientLight = sf::Color(static_cast<sf::Uint8>(50.f + 200.f * ratio), static_cast<sf::Uint8>(50.f + 200.f * ratio), static_cast<sf::Uint8>(80.f + 175.f * ratio));
        }
            //f "From dawn til dusk"
        else if (currentTime > duskTime && currentTime < dawnTime)
        {
            const float ratio{ (currentTime - duskTime) / (dawnTime - duskTime) };
            ambientLight = sf::Color(static_cast<sf::Uint8>(50.f + 200.f * (1.f - ratio)), static_cast<sf::Uint8>(50.f + 200.f * (1.f - ratio)), static_cast<sf::Uint8>(80.f + 175.f * (1.f - ratio)));
        }
            // Start a new day
        else if(currentTime > dawnTime)
            clock.restart();

    }
}

void LightingSystem::updateMovingLight(sf::Vector2f position)
{
    // Updates player light source
    lights.back().position = position;
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
