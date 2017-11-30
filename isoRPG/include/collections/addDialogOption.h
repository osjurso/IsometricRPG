

#ifndef ISORPG_ADDDIALOGOPTION_H
#define ISORPG_ADDDIALOGOPTION_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <include/components/Comp_animation.h>
#include <include/components/Comp_talk.h>
#include <iostream>


class AddDialogeOption
{
public:
    void addOption(anax::Entity& entity, std::string file)
    {
        Talkative& talkative = entity.getComponent<Talkative>();
        talkative.Optionfiles.insert(std::pair<int, std::string>(talkative.numberOfDialoges, file));
        talkative.numberOfOptions =+1;

    }
};

#endif //ISORPG_ADDDIALOGOPTION_H
