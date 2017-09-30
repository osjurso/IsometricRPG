#ifndef ISORPG_STATE_STACK_H
#define ISORPG_STATE_STACK_H

#include "include/states/state_base.h"
#include "state_identifiers.h"
#include "resource_identifiers.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>


#include <functional>
#include <vector>
#include <map>

namespace sf
{
    class Event;
    class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };


public:
    explicit StateStack(StateBase::Context context);

    template <typename T>
    void registerState(States::ID stateId);

    void update(sf::Time dt);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushState(States::ID stateId);
    void popState();
    void clearStates();

    bool isEmpty() const;


private:
    StateBase::Ptr createState(States::ID stateId);
    void applyPendingChanges();


private:
    struct PendingChange
    {
        explicit PendingChange(Action action, States::ID stateId = States::None);

        Action action;
        States::ID stateID;
    };


private:
    std::vector<StateBase::Ptr>	mStack;
    std::vector<PendingChange> mPendingList;

    StateBase::Context mContext;
    std::map<States::ID, std::function<StateBase::Ptr()>> mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateId)
{
    mFactories[stateId] = [this] () -> StateBase::Ptr
    {
        return StateBase::Ptr(new T(*this, mContext));
    };
}
#endif //ISORPG_STATE_STACK_H
