#ifndef ISORPG_MAP_H
#define ISORPG_MAP_H

#include <string>
#include <list>
#include <include/states/state_base.h>

#include "include/gameEngine/resource_holder.h"
#include "include/gameEngine/resource_identifiers.h"

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
    static bool load(std::string filename, std::list<Object*>& objects);


private:
    // Handles regular layers
    static void loadLayer(Json::Value& layer, std::list<Object*>& objects, TileSize tileSize);

    // Handles object layers
    static void loadObjects(Json::Value& root, Json::Value& layer, std::list<Object*>& objects, TileSize tileSize);
};


#endif //ISORPG_MAP_H
