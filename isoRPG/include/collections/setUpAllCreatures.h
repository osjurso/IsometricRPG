
#ifndef ISORPG_SETUPALLCREATURES_H
#define ISORPG_SETUPALLCREATURES_H


#include <include/states/state_base.h>

struct setUpAllCreatures
{
public:
    setUpAllCreatures(StateBase::Context context);

    void SetUpCreatures(anax::Entity& player, bool createPlayer);

private:
    StateBase::Context context;
};


#endif //ISORPG_SETUPALLCREATURES_H
