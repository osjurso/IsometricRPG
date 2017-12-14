#ifndef ISORPG_ADDDIALOGE_H
#define ISORPG_ADDDIALOGE_H


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "states/state_base.h"
#include "application.h"

#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_animation.h>
#include <components/Comp_talk.h>


class AddDialogue
{
public:
    void addDialogue(anax::Entity &entity, std::string file, int index)
    {
        Talkative& talkative = entity.getComponent<Talkative>();
        talkative.talkingFiles.insert(std::pair<int, std::string>(index, file));
    }
};

#endif //ISORPG_ADDDIALOGE_H
