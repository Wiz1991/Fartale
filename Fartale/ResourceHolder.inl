#include "ResourceHolder.h"
#pragma once

template<typename Identifier, typename Resource>
inline void ResourceHolder<Identifier, Resource>::load(std::string fileName, Identifier ID)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource.loadFromFile(fileName))
		throw std::runtime_error(std::string("ResourceHolder::load() - failed to load:  " + fileName));
	mResourceMap.insert(std::make_pair(Identifier, std::move(resource)));
}

template<typename Identifier, typename Resource>
inline Resource& ResourceHolder<Identifier, Resource>::get(Identifier ID)
{
	auto found = mResourceMap.find(Identifier);

	return *found->second;
}