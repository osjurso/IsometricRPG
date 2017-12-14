#include "systems/mouse_clicked.h"

MouseClicked::MouseClicked(StateBase::Context context) : context(context) {}

void MouseClicked::Clicked(anax::Entity &player, sf::View cam, float zoom, std::string state) {
    sf::RenderWindow &window = *context.window;
    anax::World &world = *context.world;

    sf::Vector2i mouse;
    mouse.x = sf::Mouse::getPosition(window).x;
    mouse.y = sf::Mouse::getPosition(window).y;
    sf::Vector2f mouseT = window.mapPixelToCoords(mouse, cam);

    auto enteties = world.getEntities();

    if (state == "Game") {
        bool interactive = false;
        for (auto i : enteties) {
            if (i.hasComponent<MousedOver>()) {
                PositionComponent &positionComponent = i.getComponent<PositionComponent>();
                SizeComponent &sizeComponent = i.getComponent<SizeComponent>();
                sf::IntRect entityRect;
                entityRect.top = positionComponent.SpriteTop;
                entityRect.left = positionComponent.SpriteLeft;
                entityRect.width = sizeComponent.SpriteWidth;
                entityRect.height = sizeComponent.SpriteHeight;

                std::cout << "top: " << entityRect.top << "  left: " << entityRect.left << "  Height: "
                          << entityRect.height << "  width: " << entityRect.width << std::endl;
                std::cout << "  MouseX: " << mouseT.x << "  MouseY: " << mouseT.y << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;

                if (entityRect.contains(mouseT.x, mouseT.y) && !i.hasComponent<UIComp>()) {
                    process(i, mouseT.x, mouseT.y, world, player, window, cam, zoom);
                    interactive = true;
                } else if (i.hasComponent<UIComp>()) {
                    UIComp uiComp = i.getComponent<UIComp>();
                    sf::IntRect textRect;
                    textRect.top = positionComponent.YPos;
                    textRect.left = positionComponent.XPos;
                    textRect.height = sizeComponent.Height;
                    textRect.width = sizeComponent.width;

                    if (textRect.contains(mouseT.x, mouseT.y)) {
                        i.getComponent<AssosateFunc>().voidfunc(i, player, world);
                        interactive = true;
                    }
                }
            }
        }
        //Move player to mouse.x, mouse.y if not intractable
        //if(!interactive)createPlayerPath(player, mouseT.x, mouseT.y);

    }
}

void MouseClicked::createPlayerPath(anax::Entity player, float MouseX, float MouseY) {
    Movable &moveble = player.getComponent<Movable>();
    moveble.path = "";
    moveble.current = 0;
    const int mapsize = 64;
    int pixelsPerBlock = 10;

    auto heroSize = player.getComponent<SizeComponent>();
    auto heroPos = player.getComponent<PositionComponent>();

    // Calculating the tile position of the hero
    sf::Vector2i heroTilePos = sf::Vector2i(heroPos.XPos + heroSize.width / 2, heroPos.SpriteTop);
    heroTilePos = sf::Vector2i((2 * heroTilePos.y + heroTilePos.x) / 64, (2 * heroTilePos.y - heroTilePos.x) / 64);

    sf::Vector2i MousePos = sf::Vector2i(MouseX + 17, MouseY + 25);
    MousePos = sf::Vector2i((2 * MousePos.y + MousePos.x) / 64, (2 * MousePos.y - MousePos.x) / 64);

    if (0 < heroTilePos.x < mapsize && 0 < heroTilePos.y < mapsize) {
        std::string path = pathFind(heroTilePos.x, heroTilePos.y, MousePos.x, MousePos.y);

        moveble.path = path;

        for (int i = 0; i < path.length(); i++) {
            for (int n = 0; n < pixelsPerBlock; n++) {
                char instruction = moveble.path.at(i);
                moveble.path.push_back(instruction);
                int index = i * pixelsPerBlock + n;

                if (instruction == '7') {
                    moveble.moveX[index] = 1;
                    moveble.moveY[index] = 0;
                }
                if (instruction == '0') {
                    moveble.moveX[index] = 0.5;
                    moveble.moveY[index] = 0.5;
                }
                if (instruction == '1') {
                    moveble.moveX[index] = 0;
                    moveble.moveY[index] = 1;
                }
                if (instruction == '2') {
                    moveble.moveX[index] = -0.5;
                    moveble.moveY[index] = 0.5;
                }
                if (instruction == '3') {
                    moveble.moveX[index] = -1;
                    moveble.moveY[index] = 0;
                }
                if (instruction == '4') {
                    moveble.moveX[index] = -0.5;
                    moveble.moveY[index] = -0.5;
                }
                if (instruction == '5') {
                    moveble.moveX[index] = 0;
                    moveble.moveY[index] = -1;
                }
                if (instruction == '6') {
                    moveble.moveX[index] = 0.5;
                    moveble.moveY[index] = -0.5;
                }
            }
        }
        player.getComponent<AnimationComponent>().action = "Walk";
    }
}

void MouseClicked::process(anax::Entity &e, float MouseXT, float MouseYT, anax::World &world, anax::Entity player,
                           sf::RenderWindow &window, sf::View cam, float zoom) {
    sf::Font &font = context.fonts->get(Fonts::RPG);
    sf::Texture &paper = context.textures->get(Textures::UIConversation);
    sf::Texture &redX = context.textures->get(Textures::UIRedX);
    sf::Texture &arrow = context.textures->get(Textures::UIArrow);

    if (e.hasComponent<Talkative>()) {
        Talk talk;
        talk.talk(e, window, world, cam, zoom, font, paper, redX, arrow);
    }

    if (e.hasComponent<Lootable>()) {
        Loot loot;
        loot.loot(world, e, player);
    }
}
