
#ifndef ISORPG_MOUSE_CLICKED_H
#define ISORPG_MOUSE_CLICKED_H

#include <anax/System.hpp>
#include <states/state_base.h>


#include <include/components/Comp_size.h>
#include <include/components/Comp_mousedOver.h>
#include <components/Comp_position.h>

struct MouseClicked : anax::System<anax::Requires<PositionComponent, SizeComponent, MousedOver>>
{
public:
    MouseClicked()
    {}
    void Clicked(float MouseX, float MouseY)
    {
        auto enteties = getEntities();

        for(auto i : enteties)
        {
            process(i,MouseX,MouseY);
        }
    }

private:
    void process(anax::Entity& e, float MouseX, float MouseY)
    {
        PositionComponent& positionComponent = e.getComponent<PositionComponent>();
        SizeComponent& sizeComponent = e.getComponent<SizeComponent>();
        MousedOver& mousedOver = e.getComponent<MousedOver>();

        if(MouseX <= positionComponent.XPos && MouseX >= positionComponent.XPos + sizeComponent.Whith)
        {
            if(MouseY<= positionComponent.YPos && MouseY >= positionComponent.YPos + sizeComponent.Height)
            {
                //MouseClicked entety e
                mousedOver.MousedOver = true;

            }else
            {
                mousedOver.MousedOver = false;
            }
        }
    }
};

#endif //ISORPG_MOUSE_CLICKED_H
