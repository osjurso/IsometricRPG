#include "include/systems/mouse_clicked.h"

MouseClicked::MouseClicked(StateBase::Context context) :context(context)
{}

void MouseClicked::Clicked(anax::Entity &player, sf::View cam, float zoom)
{
    sf::RenderWindow& window = *context.window;
    anax::World& world = *context.world;
    auto enteties = world.getEntities();
    PositionComponent& positionComponent = player.getComponent<PositionComponent>();
    SizeComponent& sizeComponent = player.getComponent<SizeComponent>();
    int reach = 50;
    sf::IntRect playerreach;
    playerreach.top = positionComponent.YPos - reach;
    playerreach.left = positionComponent.XPos -reach;
    playerreach.height = 2*reach + sizeComponent.SpriteWhith;
    playerreach.width = 2*reach + sizeComponent.SpriteHeight;
    sf::Vector2i mouse;
    mouse.x = sf::Mouse::getPosition(window).x;
    mouse.y = sf::Mouse::getPosition(window).y;
    sf::Vector2f mouseT = window.mapPixelToCoords(mouse, cam);
    //std::cout << "X: "<< mouse.x <<"  Y:" <<mouse.y << std::endl;
    bool interacteble = false;
    for(auto i : enteties)
    {
        if(i.hasComponent<MousedOver>())
        {
            process(i,mouseT.x,mouseT.y, world,player, window, cam, zoom);
            interacteble = true;
        }
    }
    if(!interacteble)
    {
        //Move player to mouse.x, mouse.y if not interactebø
        createPlayerPath(player, mouseT.x, mouseT.y);
    }


}

void MouseClicked::createPlayerPath(anax::Entity player, float MouseX, float MouseY)
{
    PositionComponent positionComponent = player.getComponent<PositionComponent>();
    Movable& moveble = player.getComponent<Movable>();
    moveble.path = "";
    const int mapsize = 64;
    int pixelsPerBlock = 10;

    const int distaceX = (MouseX  - positionComponent.SpriteLeft)/10;
    const int distaceY = (MouseY  - positionComponent.SpriteTop)/10;

    std::string path= pathFind(mapsize/2,mapsize/2,mapsize/2 + distaceX,mapsize/2 + distaceY);
    moveble.path = path;
    for(int i = 0; i < path.length(); i++)
    {
        int temp = i;
        for(int n = 0; n < pixelsPerBlock ; n++)
        {
            char instruction = moveble.path.at(i);
            moveble.path.push_back(instruction);
            int index = i*pixelsPerBlock +n;
            if(instruction == '0')
            {
                moveble.moveX[index] = 1;
                moveble.moveY[index] = 0;
            }
            if(instruction == '1')
            {
                moveble.moveX[index] = 0.5;
                moveble.moveY[index] = 0.5;
            }
            if(instruction == '2')
            {
                moveble.moveX[index] = 0;
                moveble.moveY[index] = 1;
            }
            if(instruction == '3')
            {
                moveble.moveX[index] = -0.5;
                moveble.moveY[index] = 0.5;
            }
            if(instruction == '4')
            {
                moveble.moveX[index] = -1;
                moveble.moveY[index] = 0;
            }
            if(instruction == '5')
            {
                moveble.moveX[index] = -0.5;
                moveble.moveY[index] = -0.5;
            }
            if(instruction == '6')
            {
                moveble.moveX[index] = 0;
                moveble.moveY[index] = -1;
            }
            if(instruction == '7')
            {
                moveble.moveX[index] =0.5;
                moveble.moveY[index] = -0.5;
            }
        }
    }
}

void MouseClicked::process(anax::Entity &e, float MouseXT, float MouseYT, anax::World &world, anax::Entity player, sf::RenderWindow &window, sf::View cam, float zoom)
{
    sf::Font& font = context.fonts->get(Fonts::RPG);
    sf::Texture& paper = context.textures->get(Textures::UIConversation);
    sf::Texture& redX = context.textures->get(Textures::UIRedX);
    PositionComponent& positionComponent = e.getComponent<PositionComponent>();
    SizeComponent& sizeComponent = e.getComponent<SizeComponent>();
    sf::IntRect entityRect;
    entityRect.top = positionComponent.SpriteTop;
    entityRect.left = positionComponent.SpriteLeft;
    entityRect.width = sizeComponent.SpriteWhith;
    entityRect.height = sizeComponent.SpriteHeight;
    if(entityRect.contains(MouseXT,MouseYT) && !e.hasComponent<UIComp>())
    {
        if(e.hasComponent<Talkative>())
        {
            Talk talk;
            talk.talk(e,window, world,cam ,zoom, font, paper, redX);
        }

        if(e.hasComponent<Looteble>())
        {
            Loot loot;
            loot.loot(world,e, player);
        }
    }

    if(e.hasComponent<UIComp>())
    {
        UIComp uiComp = e.getComponent<UIComp>();
        sf::IntRect textRect;
        textRect.top = positionComponent.YPos ;
        textRect.left = positionComponent.XPos ;
        textRect.height = sizeComponent.Height;
        textRect.width = sizeComponent.Whith;

        if(textRect.contains(MouseXT,MouseYT))
        {
            e.getComponent<AssosateFunc>().voidfunc(e,player,world);
        }
    }


}