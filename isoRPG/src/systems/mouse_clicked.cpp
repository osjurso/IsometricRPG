#include "include/systems/mouse_clicked.h"

MouseClicked::MouseClicked(StateBase::Context context)
        : context(context)
{
}

void MouseClicked::Clicked(anax::Entity &player,sf::View cam, float zoom)
{
    anax::World& world = *context.world;
    sf::RenderWindow& window = *context.window;

    sf::Font font = context.fonts->get(Fonts::RPG);

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
    for(auto i : enteties)
    {
        if(i.hasComponent<MousedOver>())
        {
            process(i,mouseT.x,mouseT.y, player,cam, zoom);
        }else
        {
            //Move player to mouse.x, mouse.y
            createPlayerPath(player, mouseT.x, mouseT.y);
        }
    }
}

void MouseClicked::createPlayerPath(anax::Entity player, float MouseX, float MouseY)
{
    PositionComponent positionComponent = player.getComponent<PositionComponent>();
    Movable& moveble = player.getComponent<Movable>();
    moveble.path = "";
    const int mapsize = 64;

    const int distaceX = (MouseX  - positionComponent.SpriteLeft)/10;
    const int distaceY = (MouseY  - positionComponent.SpriteTop)/10;

    std::string path= pathFind(mapsize/2,mapsize/2,mapsize/2 + distaceX,mapsize/2 + distaceY);
    moveble.path = path;
}

void MouseClicked::process(anax::Entity &e, float MouseX, float MouseY, anax::Entity player, sf::View cam, float zoom)
{
    PositionComponent& positionComponent = e.getComponent<PositionComponent>();
    SizeComponent& sizeComponent = e.getComponent<SizeComponent>();
    sf::IntRect entityRect;
    entityRect.top = positionComponent.SpriteTop;
    entityRect.left = positionComponent.SpriteLeft;
    entityRect.width = sizeComponent.SpriteWhith;
    entityRect.height = sizeComponent.SpriteHeight;
    if(entityRect.contains(MouseX,MouseY))
    {
        if(e.hasComponent<Talkative>())
        {
            sf::RenderWindow& window = *context.window;
            sf::Font& font = context.fonts->get(Fonts::RPG);
            anax::World& world = *context.world;

            std::cout << e.getId() << std::endl;
            Talk talk;

            talk.talk(e,window, world,cam ,zoom, font);
        }

        if(e.hasComponent<Looteble>())
        {
            anax::World& world = *context.world;
            Loot loot;
            loot.loot(world,e, player);
        }
    }
}