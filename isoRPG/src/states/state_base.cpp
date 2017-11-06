#include "include/states/state_base.h"
#include "include/gameEngine/state_stack.h"

StateBase::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, anax::World& world, MusicPlayer& music, SoundPlayer& sounds)
        : window(&window)
        , textures(&textures)
        , fonts(&fonts)
        , world(&world)
        , music(&music)
        , sounds(&sounds)
{
}

StateBase::StateBase(StateStack& stack, Context context)
        : mStack(&stack)
        , mContext(context)
{
}

StateBase::~StateBase()
{
}

void StateBase::requestStackPush(States::ID stateId)
{
    mStack->pushState(stateId);
}

void StateBase::requestStateChange(States::ID stateId)
{
    requestStackPop();
    requestStackPush(stateId);
}

void StateBase::requestStackPop()
{
    mStack->popState();
}

void StateBase::requestStateClear()
{
    mStack->clearStates();
}

StateBase::Context StateBase::getContext() const
{
    return mContext;
}
