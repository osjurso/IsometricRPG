#ifndef ISORPG_STATE_H
#define ISORPG_STATE_H
#include <memory>

#include <SFML/Graphics.hpp>
#include <anax/anax.hpp>

#include "include/gameEngine/state_identifiers.h"
#include "include/gameEngine/resource_identifiers.h"

namespace sf
{
    class RenderWindow;
}

class StateStack;
class Player;

class StateBase
{
public:
    typedef std::unique_ptr<StateBase> Ptr;

    struct Context
    {
        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, anax::World& world);

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        anax::World* world;

    };


public:
    StateBase(StateStack& stack, Context context);
    virtual	~StateBase();

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;


protected:
    void requestStackPush(States::ID stateId);
    void requestStateChange(States::ID stateId);
    void requestStackPop();
    void requestStateClear();

    Context getContext() const;


private:
    StateStack* mStack;
    Context	mContext;
};

#endif //ISORPG_STATE_H
