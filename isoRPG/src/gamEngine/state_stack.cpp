#include "include/gameEngine/state_stack.h"

#include <cassert>

StateStack::StateStack(StateBase::Context context)
        : mStack()
        , mPendingList()
        , mContext(context)
        , mFactories()
{
}

void StateStack::update(sf::Time dt)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(dt))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    for (StateBase::Ptr& state: mStack)
        state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void StateStack::pushState(States::ID stateId)
{
    mPendingList.push_back(PendingChange(Push, stateId));
}

void StateStack::popState()
{
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
    mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

StateBase::Ptr StateStack::createState(States::ID stateId)
{
    auto found = mFactories.find(stateId);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for (PendingChange change : mPendingList)
    {
        switch (change.action)
        {
            case Push:
                mStack.push_back(createState(change.stateID));
                break;

            case Pop:
                mStack.pop_back();
                break;

            case Clear:
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateId)
        : action(action)
        , stateID(stateId)
{
}
