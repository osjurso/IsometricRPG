#include "collections/mouseClikedFunctions.h"
#include "components/Comp_Children.h"

void killChildren(anax::Entity& entity)
{
    ChildComponent& childComponent = entity.getComponent<ChildComponent>();

    for(int i =0; i < sizeof(childComponent.children) ; i++)
    {
        childComponent.children[i].kill();
    }

}
void printTempVoid(anax::Entity entity)
{
    std::cout << "Hello from temp" << std::endl;
}
