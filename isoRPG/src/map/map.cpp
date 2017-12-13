#include <fstream>
#include <cstring>
#include <random>

#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <include/collections/setUpCreature.h>
#include <include/systems/pathfinding.h>
#include <include/systems/lighting_system.h>

#include "map/map.h"
#include "map/sprite.h"
#include "map/layer.h"

bool Map::load(std::string filename, StateBase::Context context, LightingSystem &lightingSystem)
{
    // Will contain the data we read in
    Json::Value root;

    // Stream used for reading the data file. The data file has been saved as JSON in Tiled
    std::ifstream file(filename, std::ifstream::binary);

    file >> root;

    // Get tile size information
    TileSize tileSize;
    tileSize.x = root["tilesets"][0u]["tilewidth"].asInt();
    tileSize.y = root["tilesets"][0u]["tileheight"].asInt();
    tileSize.s = root["tilesets"][0u]["spacing"].asInt();
    std::string tileset = root["tilesets"][0u]["name"].asString();


    // Read in each layer
    for (Json::Value& layer: root["layers"])
    {
        if (layer["name"].asString() == "enemy")
            continue;
            //loadEntities(root, layer, context);
        else if (layer["name"].asString() == "objects")
            loadObjects(root, layer, tileSize, context, tileset);
        else if (layer["name"].asString() == "collision")
            loadCollision(root, layer);
        else if (layer["name"].asString() == "lights")
            loadLights(root, layer, context, lightingSystem);
        else
         loadLayer(layer, tileSize, context, tileset);
    }

    return true;
}

void Map::loadLayer(Json::Value& layer, TileSize tileSize, StateBase::Context context, std::string tileset)
{

    Layer* tmp = new Layer(tileSize, context);

    // Store info on layer
    tmp->width = layer["width"].asInt();
    tmp->height = layer["height"].asInt();
    tmp->priority = layer["priority"]["Priority"].asInt();
    tmp->tileset = tileset;

    // Clear tilemap
    memset(tmp->tilemap, 0, sizeof(tmp->tilemap));

    // Read in tilemap
    for (size_t i = 0; i < layer["data"].size(); i++)
        tmp->tilemap[i % tmp->width][i / tmp->width] = layer["data"][(int)i].asInt();

    tmp->createEntities();
}

void Map::loadObjects(Json::Value& root, Json::Value& layer, TileSize tileSize, StateBase::Context context, std::string tileset)
{
    int puzzleNum = 0;
    // Get all objects from layer
    for (Json::Value& object: layer["objects"])
    {
        Json::Value properties = root["tilesets"][0u]["tileproperties"];
        int gid = object["gid"].asInt() - 1;

        // Resetting tile height
        tileSize.y = 64;

        if (properties[std::to_string(gid)].isMember("Height"))
        {
            if (properties[std::to_string(gid)]["Height"].asInt() == 0)
                continue;
            else
                tileSize.y *= properties[std::to_string(gid)]["Height"].asInt();
        }

        Sprite* sprite = new Sprite(tileSize, context);

        // Load basic object info
        sprite->x = object["x"].asInt();
        sprite->y = object["y"].asInt() - sprite->tileSize.y;
        sprite->id = object["gid"].asInt();
        sprite->priority = object["y"].asInt();
        sprite->tileset = tileset;
        sprite->puzzleNum = puzzleNum;

        if (object["properties"].isMember("lootable"))
            sprite->lootable = object["properties"]["lootable"].asBool();

        if (object["properties"].isMember("hasPuzzle"))
        {
            sprite->hasPuzzle = object["properties"]["hasPuzzle"].asBool();
            puzzleNum++;
        }

        sprite->createEntities();

        delete sprite;
    }
}

void Map::loadCollision(Json::Value& root, Json::Value& layer)
{
    int width = layer["width"].asInt();
    int height = layer["height"].asInt();

    int collisionMap[64][64];

    // Clear tilemap
    memset(collisionMap, 0, sizeof(collisionMap));

    for (size_t i = 0; i < layer["data"].size(); i++)
    {
        collisionMap[i % width][i / width] = layer["data"][(int)i].asInt();

        // TODO: Cleaner way to replace >0 values?
        if (collisionMap[i % width][i / width] != 0)
            collisionMap[i % width][i / width] = 1;
    }

    std::ofstream collisionData;
    collisionData.open("assets/map/collision_data");


    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            collisionData << collisionMap[j][i];
        }
        collisionData << std::endl;
    }

    collisionData.close();

    node node1(0, 0, 0, 0);
    node1.loadMapData(width, height);
}

void Map::loadLights(Json::Value &root, Json::Value &layer, StateBase::Context context, LightingSystem &lightingSystem)
{
    // Store info on layer
    int width = layer["width"].asInt();
    int height = layer["height"].asInt();

    int lightMap[width][height];

    // Clear tilemap
    memset(lightMap, 0, sizeof(lightMap));

    for (size_t i = 0; i < layer["data"].size(); i++)
    {
        lightMap[i % width][i / width] = layer["data"][(int)i].asInt();
    }

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (lightMap[x][y] == 0)
                continue;

            sf::Vector2f v(x, y);

            v.x = (v.x - 12) * 32;
            v.y = (v.y - 15) * 32;


            v = sf::Vector2f((v.x - v.y), (v.x + v.y) / 2);

            lightingSystem.addLight(v);
        }
    }
}

void Map::loadEntities(Json::Value &root, Json::Value &layer, StateBase::Context context)
{
    for (Json::Value& object: layer["objects"])
    {
        anax::World& world = *context.world;
        SetUpCreature creatureSetup;

        std::string category = object["properties"]["category"].asString();
        int minNum = object["properties"]["minNum"].asInt();
        int maxNum = object["properties"]["maxNum"].asInt();
        std::string difficulty = object["properties"]["difficulty"].asString();

        int left = object["x"].asInt();
        int top = object["y"].asInt();
        int width = object["width"].asInt();
        int height = object["height"].asInt();

        // TODO: Load texture by category property
        sf::Texture& texture = context.textures->get(Textures::Goblin);

        // Bad distribution, but good enough
        srand(time(nullptr));
        int number = minNum + rand() % (maxNum - minNum + 1);

        // Uniform distribution needed to prevent repetitive placement
        std::default_random_engine generator;
        std::uniform_int_distribution<int> xDist(left, left + width);
        std::uniform_int_distribution<int> yDist(top, top + height);

        for (int i = 0; i < number; ++i)
        {
            int posX = xDist(generator);
            int posY = yDist(generator);

            sf::Vector2i v = sf::Vector2i((posX - posY), (posX + posY)/2);

            // quick offset fix, wont be accurate for different sized enemies
            v.y -= 90;
            v.x -= 64;

            anax::Entity entity = world.createEntity();
            creatureSetup.setUpEnemie(entity, texture, *context.window, v.x, v.y, difficulty);
            world.refresh();
        }
    }
}
