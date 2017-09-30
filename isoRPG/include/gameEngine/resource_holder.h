#ifndef ISORPG_TEXTURE_HOLDER_H
#define ISORPG_TEXTURE_HOLDER_H

#include <memory>
#include <map>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void load(Identifier id, const std::string &filename);
    template <typename Parameter>
    void load(Identifier id, const std::string &filename, const Parameter &secondParam);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

    void InsertResource(Identifier id, std::unique_ptr<Resource> resource);

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "resource_holder.inl"

#endif //ISORPG_TEXTURE_HOLDER_H
