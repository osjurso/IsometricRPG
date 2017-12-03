
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

typedef void (*pfunc)(anax::Entity&, anax::Entity&, anax::World&);

class AddOptionDialoge
{
public:
    void addOptionDialoge(anax::Entity& entity, std::string optionString, int index, int optionNr, pfunc func)
    {
        Talkative& talkative = entity.getComponent<Talkative>();
        talkative.total[index] = optionNr;

        talkative.optionMap.insert(std::pair<int,std::string>(optionNr,optionString));
        talkative.options.insert(std::pair<int, std::map<int,std::string>>(index,talkative.optionMap));

        talkative.functionmap.insert(std::pair<int,pfunc>(optionNr,func));
        talkative.functions.insert(std::pair<int, std::map<int,pfunc>>(index,talkative.functionmap));

    }
};

#endif //ISORPG_ADDDIALOGOPTION_H
