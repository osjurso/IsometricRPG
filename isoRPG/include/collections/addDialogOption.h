
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


class AddOptionDialoge
{
public:
    void addOptionDialoge(anax::Entity& entity, std::string file, int index)
    {
        Talkative& talkative = entity.getComponent<Talkative>();
        talkative.Optoinfiles.insert(std::pair<int, std::string>(index, file));
        talkative.numberOfOption =+1;
    }
};

#endif //ISORPG_ADDDIALOGOPTION_H
