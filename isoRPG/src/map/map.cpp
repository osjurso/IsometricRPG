#include <fstream>
#include <cstring>

#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "map/map.h"
#include "map/sprite.h"
#include "map/layer.h"

bool Map::load(std::string filename, std::list<Object*>& objects, StateBase::Context context)
{
    // Will contain the data we read in
    Json::Value root;


    //TODO: Switch to CharReader and CharReaderBuilder
    // Parses the file
    Json::Reader reader;

    // Stream used for reading the data file. The data file has been saved as JSON in Tiled
    std::ifstream file(filename);

    // Read data from file into root object
    bool parsingSuccessful = reader.parse(file, root);

    // Check for success
    if (!parsingSuccessful)
        return false;

    // Get tile size information
    TileSize tileSize;
    tileSize.x = root["tilesets"][0u]["tilewidth"].asInt();
    tileSize.y = root["tilesets"][0u]["tileheight"].asInt();
    tileSize.s = root["tilesets"][0u]["spacing"].asInt();

    // Read in each layer
    for (Json::Value& layer: root["layers"])
    {
        if (layer["name"].asString() != "objects")
            loadLayer(layer, objects, tileSize, context);
        else
            loadObjects(root, layer, objects, tileSize, context);
    }

    // Read in tileset TODO: Should be handled by a resource handler
    sf::Texture* tileset = new sf::Texture();
    tileset->loadFromFile("assets/map/" + root["tilesets"][0u]["image"].asString());

    // Assign tileset to every object
    for (Object* object: objects)
        object->texture = tileset;



    for (Object* object : objects)
    {
        object->process(1.f/60.f);
        object->draw();
    }


    return true;
}

void Map::loadLayer(Json::Value& layer, std::list<Object*>& objects, TileSize tileSize, StateBase::Context context)
{

    Layer* tmp = new Layer(tileSize, context);

    // Store info on layer
    tmp->width = layer["width"].asInt();
    tmp->height = layer["height"].asInt();
    tmp->priority = layer["priority"]["Priority"].asInt();

    // Clear tilemap
    memset(tmp->tilemap, 0, sizeof(tmp->tilemap));

    // Read in tilemap
    for (size_t i = 0; i < layer["data"].size(); i++)
        tmp->tilemap[i % tmp->width][i / tmp->width] = layer["data"][(int)i].asInt();


    objects.push_back(tmp);
}

void Map::loadObjects(Json::Value& root, Json::Value& layer, std::list<Object*>& objects, TileSize tileSize, StateBase::Context context)
{
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

        // Load animation data
        Json::Value& tileInfo = root["tilesets"][0u]["tiles"][std::to_string(sprite->id - 1)];
        sprite->frame = 0;
        sprite->frameCount = tileInfo["animation"].size();
        sprite->frameDuration = tileInfo["animation"][0u]["duration"].asInt();

        objects.push_back(sprite);
    }
}

void Map::loadCollision(Json::Value &root, Json::Value &layer, StateBase::Context context)
{
    int colissionMap[100][100];

    int width = layer["width"].asInt();
    int height = layer["height"].asInt();

    for (size_t i = 0; i < layer["data"].size(); i++)
        colissionMap[i % width][i / width] = layer["data"][(int)i].asInt();

}