#ifndef ISORPG_ADDPUZZLE_H
#define ISORPG_ADDPUZZLE_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "states/state_base.h"
#include "application.h"
#include "addDialogueOption.h"
#include "addDialogue.h"
#include "mouseClickedFunctions.h"

#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_animation.h>
#include <components/Comp_talk.h>
#include <components/Comp_mousedOver.h>


class AddPuzzle
{
public:
    void add(anax::Entity& speaker, int puzzleNum)
    {
            AddDialogue addDialogue;
            AddOptionDialogue optionDialogue;
            //int randomIndex = rand() % numbers.size();
            //int number = numbers.at(randomIndex);

            speaker.addComponent<Talkative>();
            speaker.addComponent<MousedOver>();

            if(puzzleNum == 0)
            {
                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_0_question.txt", 0);
                optionDialogue.addOptionDialogue(speaker, "Wolfsbane", 0, 0, ArmorReward); //revard
                optionDialogue.addOptionDialogue(speaker, "Madrake root", 0, 1, healthPunishment);
                optionDialogue.addOptionDialogue(speaker, "Blood grass", 0, 2, healthPunishment);

                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_0_default.txt", 1);
            }
            if(puzzleNum == 1)
            {
                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_1_question.txt", 0);
                optionDialogue.addOptionDialogue(speaker, "Dragon", 0, 0, healthPunishment);
                optionDialogue.addOptionDialogue(speaker, "Orc", 0, 1, healthPunishment);
                optionDialogue.addOptionDialogue(speaker, "Baselisk", 0, 2, ArmorReward); //revard

                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_1_default.txt", 1);
            }
            if(puzzleNum == 2)
            {
                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_2_question.txt", 0);
                optionDialogue.addOptionDialogue(speaker, "Undead", 0, 0, healthPunishment);
                optionDialogue.addOptionDialogue(speaker, "Devil", 0, 1, ArmorReward); //revard
                optionDialogue.addOptionDialogue(speaker, "Demon", 0, 2, healthPunishment);

                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_2_default.txt", 1);
            }
            if(puzzleNum == 3)
            {
                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_3_question.txt", 0);
                optionDialogue.addOptionDialogue(speaker, "Golden Cage", 0, 0, healthPunishment);
                optionDialogue.addOptionDialogue(speaker, "Silver", 0, 1, healthPunishment);
                optionDialogue.addOptionDialogue(speaker, "Phylactery", 0, 2, ArmorReward); //revard

                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_1_question.txt", 1);
            }
            if(puzzleNum == 4)
            {
                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_4_question.txt", 0);
                optionDialogue.addOptionDialogue(speaker, "Fey", 0, 0, ArmorReward);//revard
                optionDialogue.addOptionDialogue(speaker, "Infernal", 0, 1, healthPunishment);
                optionDialogue.addOptionDialogue(speaker, "Elemental", 0, 2, healthPunishment);

                addDialogue.addDialogue(speaker, "assets/dialog/puzzle_0_default.txt", 1);
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
