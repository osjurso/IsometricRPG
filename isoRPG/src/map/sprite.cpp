#include <SFML/Graphics.hpp>
#include <include/components/comp_collision.h>
#include <include/collections/addPuzzle.h>
#include <include/components/Comp_looteble.h>

#include "map/sprite.h"
#include "collections/drawable.h"

void Sprite::createEntities()
{
    int tilex, tiley;
    getTileCoords(id, tilex, tiley);

    sf::IntRect tileRect = sf::IntRect(tilex, tiley, tileSize.x, tileSize.y);

    // Different offset for different sized tiles
    tilex = x + tileSize.y - 64;
    tiley = y + tileSize.y + tileSize.y - 64;

    sf::Vector2f v(tilex, tiley);
    CartesianToIsometric(v);

    sf::Sprite sprite;

    if (tileset == "spritesheet")
        sprite = sf::Sprite(context.textures->get(Textures::grasslandTileset), tileRect);
    else if (tileset == "cave_tiles")
        sprite = sf::Sprite(context.textures->get(Textures::caveTileset), tileRect);

    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height);
    anax::World& world = *context.world;

    Draweble draweble;

    anax::Entity mapEntity = world.createEntity();

    if (tileset == "spritesheet")
        draweble.makeDraweble(context.textures->get(Textures::grasslandTileset), v.x, v.y, mapEntity, "Game");
    else if (tileset == "cave_tiles")
        draweble.makeDraweble(context.textures->get(Textures::caveTileset), v.x, v.y, mapEntity, "Game");

    TextureComponent& textureComponent = mapEntity.getComponent<TextureComponent>();
    textureComponent.sprite[0] = sprite;
    textureComponent.sortKey = static_cast<int>(mapEntity.getComponent<PositionComponent>().YPos);


    if (hasPuzzle)
    {
        auto &posComp = mapEntity.getComponent<PositionComponent>();
        auto &sizeComp = mapEntity.getComponent<SizeComponent>();

        posComp.SpriteLeft = posComp.XPos - 32;
        posComp.SpriteTop = posComp.YPos - 96;

        sizeComp.SpriteWhith = tileSize.x;
        sizeComp.SpriteHeight = tileSize.y -32;

        AddPuzzle addPuzzle;
        addPuzzle.add(mapEntity, puzzleNum);
        std::cout << "Loading puzzle with puzzleNum: " << puzzleNum << std::endl;
    }
    if (lootable)
    {
        std::cout << "Lootable";
        auto &posComp = mapEntity.getComponent<PositionComponent>();
        auto &sizeComp = mapEntity.getComponent<SizeComponent>();

        posComp.SpriteLeft = posComp.XPos - 32;
        posComp.SpriteTop = posComp.YPos - 40;

        sizeComp.SpriteWhith = tileSize.x;
        sizeComp.SpriteHeight = tileSize.y - 32;

        mapEntity.addComponent<MousedOver>();
        mapEntity.addComponent<Looteble>();

        srand(time(nullptr));
        mapEntity.getComponent<Looteble>().gold = rand() % 150 + 100;
    }
}
