
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
#include <include/components/Comp_mousedOver.h>
#include "addDialogOption.h"
#include "addDialoge.h"
#include "mouseClikedFunctions.h"


class AddPuzzle
{
public:
    void add(anax::Entity& speaker, int puzzleNum)
    {
            AddDialoge addDialoge;
            AddOptionDialoge optionDialoge;
            //int randomIndex = rand() % numbers.size();
            //int number = numbers.at(randomIndex);

            speaker.addComponent<Talkative>();
            speaker.addComponent<MousedOver>();

            if(puzzleNum == 0)
            {
                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_0_question.txt",0);
                optionDialoge.addOptionDialoge(speaker,"Wolfsbane"   ,0,0,healtPotionRevard); //revard
                optionDialoge.addOptionDialoge(speaker,"Madrake root",0,1,healtPunishment);
                optionDialoge.addOptionDialoge(speaker,"Blood grass" ,0,2,healtPunishment);

                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_0_default.txt",1);
            }
            if(puzzleNum == 1)
            {
                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_1_question.txt",0);
                optionDialoge.addOptionDialoge(speaker,"Dragon",0,3,healtPunishment);
                optionDialoge.addOptionDialoge(speaker,"Orc"   ,0,4,healtPunishment);
                optionDialoge.addOptionDialoge(speaker,"Baselisk",0,5,healtPotionRevard); //revard

                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_1_default.txt",1);
            }
            if(puzzleNum == 2)
            {
                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_2_question.txt",0);
                optionDialoge.addOptionDialoge(speaker,"Undead",0,3,healtPunishment);
                optionDialoge.addOptionDialoge(speaker,"Devil"   ,0,4,healtPotionRevard); //revard
                optionDialoge.addOptionDialoge(speaker,"Demon",0,5,healtPunishment);

                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_2_default.txt",1);
            }
            if(puzzleNum == 3)
            {
                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_3_question.txt",0);
                optionDialoge.addOptionDialoge(speaker,"Golden Cage",0,3,healtPunishment);
                optionDialoge.addOptionDialoge(speaker,"Silver"   ,0,4,healtPunishment);
                optionDialoge.addOptionDialoge(speaker,"Phylactery",0,5,healtPotionRevard); //revard

                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_1_question.txt",1);
            }
            if(puzzleNum == 4)
            {
                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_4_question.txt",0);
                optionDialoge.addOptionDialoge(speaker,"Fey",0,3,healtPotionRevard);//revard
                optionDialoge.addOptionDialoge(speaker,"Infernal"   ,0,4,healtPunishment);
                optionDialoge.addOptionDialoge(speaker,"Elemental",0,5,healtPunishment);

                addDialoge.addDialoge(speaker,"assets/dialog/puzzle_0_default.txt",1);
            }

            //numbers.erase(numbers.begin()+randomIndex-1);

            speaker.getComponent<Talkative>().TotalOfDialogs = 1;
            speaker.getComponent<Talkative>().Default = 1;
            speaker.getComponent<Talkative>().Current = 0;

        }//End of if(numbers.size != 0)

private:
    //std::vector<int> numbers = {0,1,2,3,4};
};


#endif //ISORPG_ADDPUZZLE_H
