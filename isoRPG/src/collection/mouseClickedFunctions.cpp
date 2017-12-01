#include <include/components/Comp_Texture.h>
#include <include/components/Comp_Text.h>
#include "collections/mouseClikedFunctions.h"
#include "components/Comp_Children.h"

void killChildren(anax::Entity entity)
{
    ChildComponent& childComponent = entity.getComponent<ChildComponent>();

    for(int i =0; i < childComponent.children.size(); i++)
    {
        std::cout << childComponent.children.at(i).getId() << std::endl;
        anax::Entity& tempE = childComponent.children.at(i);

        if(tempE.hasComponent<TextureComponent>())tempE.getComponent<TextureComponent>().draw = false;
        if(tempE.hasComponent<TextComponent>())tempE.getComponent<TextComponent>().draw = false;

    }
    entity.getComponent<TextureComponent>().draw = false;



}
void printTempVoid(anax::Entity entity)
{
    std::cout << "Hello from temp" << std::endl;
}
