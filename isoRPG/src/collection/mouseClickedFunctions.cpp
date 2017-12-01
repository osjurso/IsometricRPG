#include "collections/mouseClikedFunctions.h"
#include "components/Comp_Children.h"

void killChildren(anax::Entity entity)
{
    ChildComponent& childComponent = entity.getComponent<ChildComponent>();

    for(int i =0; i < childComponent.children.size(); i++)
    {
        std::cout << childComponent.children.at(i).getId() << std::endl;
    }

}
void printTempVoid(anax::Entity entity)
{
    std::cout << "Hello from temp" << std::endl;
}
