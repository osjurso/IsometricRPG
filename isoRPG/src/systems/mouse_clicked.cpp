#include "include/systems/mouse_clicked.h"

MouseClicked::MouseClicked(StateBase::Context context) :context(context)
{}

void MouseClicked::Clicked(anax::Entity& player, sf::View cam, float zoom, std::string state)
{
    sf::RenderWindow& window = *context.window;
    anax::World& world = *context.world;

    sf::Vector2i mouse;
    mouse.x = sf::Mouse::getPosition(window).x;
    mouse.y = sf::Mouse::getPosition(window).y;
    sf::Vector2f mouseT = window.mapPixelToCoords(mouse, cam);

    bool interactable = false;
    auto enteties = world.getEntities();

    if(state == "Game")
    {
        for(auto i : enteties)
        {
            if(i.hasComponent<MousedOver>())
            {
                process(i,mouseT.x,mouseT.y, world,player, window, cam, zoom);
                interactable = true;
            }
        }
        if(!interactable)
        {
            //Move player to mouse.x, mouse.y if not intractable
            createPlayerPath(player, mouseT.x, mouseT.y);
        }
    }else if(state == "Menu")
    {
        for(auto i : enteties)
        {
            if(i.hasComponent<MousedOver>())
            {
                processMenu(i,sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y, window, cam, zoom);
            }
        }
    }

}

void MouseClicked::createPlayerPath(anax::Entity player, float MouseX, float MouseY)
{
    PositionComponent positionComponent = player.getComponent<PositionComponent>();
    Movable& moveble = player.getComponent<Movable>();
    moveble.path = "";
    const int mapsize = 64;
    int pixelsPerBlock = 10;

    const int distaceX = (MouseX  - positionComponent.SpriteLeft) / 10;
    const int distaceY = (MouseY  - positionComponent.SpriteTop) / 10;

    // TODO: Fix pathfind input

    std::string path= pathFind(mapsize/2, mapsize/2, mapsize/2 + distaceX, mapsize/2 + distaceY);
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
    sf::Texture& arrow = context.textures->get(Textures::UIArrow);
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
            talk.talk(e,window, world,cam ,zoom, font, paper, redX, arrow);
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

void MouseClicked::processMenu(anax::Entity &e, float MouseX, float MouseY, sf::RenderWindow &window, sf::View cam, float zoom)
{

}