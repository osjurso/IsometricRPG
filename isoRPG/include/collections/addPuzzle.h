
#ifndef ISORPG_ADDPUZZLE_H
#define ISORPG_ADDPUZZLE_H


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
#include "addDialogOption.h"
#include "addDialoge.h"
#include "mouseClikedFunctions.h"


class AddPuzzle
{
public:
    void add(anax::Entity& speaker)
    {
        AddDialoge addDialoge;
        AddOptionDialoge optionDialoge;
    int number = 0;

        if(number == 0)
        {
            addDialoge.addDialoge(speaker,"assets/dialog/trader_dialog_0.txt",0);
            optionDialoge.addOptionDialoge(speaker,"wolfsbane"   ,0,0,healtPotionRevard);
            optionDialoge.addOptionDialoge(speaker,"madrake root",0,1,healtPunishment);
            optionDialoge.addOptionDialoge(speaker,"blood grass" ,0,2,healtPunishment);


            addDialoge.addDialoge(speaker,"assets/dialog/puzzle_0_default",1);
        }
        if(number == 1)
        {
            addDialoge.addDialoge(speaker,"assets/dialog/trader_dialog_1.txt",1);
            optionDialoge.addOptionDialoge(speaker,"Ground dragon scales",1,3,healtPunishment);
            optionDialoge.addOptionDialoge(speaker,"Holy Water"          ,1,4,healtPunishment);
            optionDialoge.addOptionDialoge(speaker,"Baselisk blod"       ,1,5,healtPotionRevard);

        }




        speaker.getComponent<Talkative>().TotalOfDialogs = 2;
        speaker.getComponent<Talkative>().Default = 1;
        speaker.getComponent<Talkative>().Current = 0;

    }
};

#endif //ISORPG_ADDPUZZLE_H
