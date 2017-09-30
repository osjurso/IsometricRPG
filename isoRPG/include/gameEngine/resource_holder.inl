template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename)
{
    // load resource into resource ptr
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load" + filename);

    // if successful, insert resource into map
    InsertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename,
                                                const Parameter &secondParam)
{
    // load resource into resource ptr
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, secondParam))
        throw std::runtime_error("ResourceHgolder:.load - failed to load" + filename);

    // if successful, insert resource into map
    InsertResource(id, std::move(resource));
};

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::InsertResource(Identifier id, std::unique_ptr<Resource> resource)
{
    // Insert and check sucess
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}