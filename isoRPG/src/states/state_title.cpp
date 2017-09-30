#include <SFML/Graphics.hpp>

#include "include/states/state_title.h"
#include "include/gameEngine/resource_holder.h"
#include "include/util/utility.h"

namespace
{
    template <class T>
    inline T linearInterpolation(const T& start, const T& end, const float alpha)
    {
        return static_cast<T>(start * (1.f - alpha) + end * alpha);
    }
}

StateTitle::StateTitle(StateStack& stack, Context context)
        : StateBase(stack, context)
        , screenSize(context.window->getSize())
        , startingView({ 0.f, 0.f }, { screenSize.y * (context.window->getView().getSize().x / context.window->getView().getSize().y), screenSize.y })
        , shakeStart(sf::seconds(1.944f))
        , shakeStrength(50.f)
        , letterScale(0.7f)
        , shakeLength(sf::seconds(0.6f))
        , fadeStart(sf::seconds(11.f))
        , length(sf::seconds(10.f))
        , inAnimation(true)
{
    logoSprite.setTexture(context.textures->get(Textures::TitleLogo));
    isoSprite.setTexture(context.textures->get(Textures::TitleText));
    isoSprite.setTextureRect(sf::IntRect(0, 0, 175, 155));
    rpgSprite.setTexture(context.textures->get(Textures::TitleText));
    rpgSprite.setTextureRect(sf::IntRect(200, 0, 260, 155));

    centerOrigin(logoSprite);
    centerOrigin(isoSprite);
    centerOrigin(rpgSprite);
}

void StateTitle::draw()
{
    sf::RenderWindow& window = *getContext().window;

    srand(static_cast<unsigned int>(time(nullptr)));
    prepareAnimations();
    clock.restart();

    // Todo: Need to separate into draw/update/handleEvents
    while (inAnimation)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                inAnimation = false;
                requestStackPop();
                requestStackPush(States::Menu);
            }
        }
        currentTime = clock.getElapsedTime();
        if (currentTime > length)
            inAnimation = false;

        updateObjects(logoSprite, animationLogo);
        updateObjects(isoSprite, animationIso);
        updateObjects(rpgSprite, animationRpg);
        updateFade();
        updateShake(startingView);

        window.setView(view);
        window.clear();
        window.draw(logoSprite);
        window.draw(isoSprite);
        window.draw(rpgSprite);
        window.display();
    }

}

bool StateTitle::update(sf::Time dt)
{
    // update fade
    if (currentTime > fadeStart)
    {
        const float ratio{ (currentTime - fadeStart) / (length - fadeStart) };
        const sf::Color color(255, 255, 255, static_cast<sf::Uint8>(255.f * (1.f - ratio)));
        logoSprite.setColor(color);
        isoSprite.setColor(color);
        rpgSprite.setColor(color);
    }

    // update shake
    view = startingView;
    if ((currentTime >= shakeStart) && (currentTime <= (shakeStart + shakeLength)))
    {
        const float ratio{ (currentTime - shakeStart) / shakeLength };
        const float strength{ shakeStrength * (1.f - ratio) };
        view.move({ (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength, (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength });
    }

    // Switch state when animation is done
    if (currentTime > length)
    {
        requestStateChange(States::Menu);
    }
}

bool StateTitle::handleEvent(const sf::Event& event)
{
    // If any key is pressed, enter the Menu state
    if (event.type == sf::Event::KeyPressed)
    {
        requestStateChange(States::Menu);
    }

    return true;
}

void StateTitle::prepareAnimations()
{
    //Define animations for Logo, IsoText and RpgText
    animationLogo.start.time = sf::seconds(1.7f);
    animationLogo.end.time = sf::seconds(1.944f);
    animationLogo.start.position = { screenSize.x * 0.3f, -screenSize.y * 0.4f };
    animationLogo.end.position = { 0.f, -screenSize.y * 0.15f };
    animationLogo.start.scale = 0.f;
    animationLogo.end.scale = 1.f;

    animationIso.start.time = sf::seconds(2.8f);
    animationIso.end.time = sf::seconds(3.f);
    animationIso.start.position = { 0.f, -screenSize.y * 0.15f };
    animationIso.end.position = { -123.f * letterScale, screenSize.y / 6 };
    animationIso.start.scale = 0.f;
    animationIso.end.scale = letterScale;

    animationRpg.start.time = sf::seconds(3.2f);
    animationRpg.end.time = sf::seconds(3.4f);
    animationRpg.start.position = { 0.f, -screenSize.y * 0.1f };
    animationRpg.end.position = { 123.f * letterScale, screenSize.y / 6 };
    animationRpg.start.scale = 0.f;
    animationRpg.end.scale = letterScale;
}

void StateTitle::updateObjects(sf::Sprite &sprite, const StateTitle::Animation &animation)
{
    if (currentTime <= animation.start.time)
    {
        sprite.setPosition(animation.start.position);
        sprite.setScale({ animation.start.scale, animation.start.scale });
    }
    else if (currentTime >= animation.end.time)
    {
        sprite.setPosition(animation.end.position);
        sprite.setScale({ animation.end.scale, animation.end.scale });
    }
    else
    {
        const float ratio{ (currentTime - animation.start.time) / (animation.end.time - animation.start.time) };
        sprite.setPosition(linearInterpolation(animation.start.position, animation.end.position, ratio));
        const float scale{ linearInterpolation(animation.start.scale, animation.end.scale, ratio) };
        sprite.setScale({ scale, scale });
    }
}

void StateTitle::updateFade()
{
    if (currentTime > fadeStart)
    {
        const float ratio{ (currentTime - fadeStart) / (length - fadeStart) };
        const sf::Color color(255, 255, 255, static_cast<sf::Uint8>(255.f * (1.f - ratio)));
        logoSprite.setColor(color);
        isoSprite.setColor(color);
        rpgSprite.setColor(color);
    }

    view = startingView;
    if ((currentTime >= shakeStart) && (currentTime <= (shakeStart + shakeLength)))
    {
        const float ratio{ (currentTime - shakeStart) / shakeLength };
        const float strength{ shakeStrength * (1.f - ratio) };
        view.move({ (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength, (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength });
    }
}

void StateTitle::updateShake(const sf::View &startingView)
{
    view = startingView;
    if ((currentTime >= shakeStart) && (currentTime <= (shakeStart + shakeLength)))
    {
        const float ratio{ (currentTime - shakeStart) / shakeLength };
        const float strength{ shakeStrength * (1.f - ratio) };
        view.move({ (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength, (static_cast<float>(rand() % 200) / 100.f - 1.f) * strength });
    }
}
