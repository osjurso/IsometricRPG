#ifndef ISORPG_MAP_H
#define ISORPG_MAP_H

#include <string>
#include <list>

#include "object.h"

namespace Json
{
    class Value;
}

// Class with a single public static function that loads a map into an object list
class Map
{
public:
    // Load map from Tiled JSON file
    static bool load(std::string filename, StateBase::Context context, LightingSystem &lightingSystem);


private:
    // Handles regular layers
    static void loadLayer(Json::Value& layer, TileSize tileSize, StateBase::Context context, std::string tileset);

    // Handles object layers
    static void loadObjects(Json::Value& root, Json::Value& layer, TileSize tileSize, StateBase::Context context, std::string tileset);

    // Handles collsion layer
    static void loadCollision(Json::Value& root, Json::Value& layer);

    static void loadLights(Json::Value& root, Json::Value& layer, StateBase::Context context, LightingSystem &lightingSystem);

    static void loadEntities(Json::Value& root, Json::Value& layer, StateBase::Context context);
};


#endif //ISORPG_MAP_H
