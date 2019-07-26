#pragma once
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <memory>

template<typename Identifier, typename Resource>
class ResourceHolder {
public:
	void load(const std::string& fileName, Identifier ID);

	Resource& get(Identifier ID);

private:
	std::unordered_map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};
#include "ResourceHolder.inl"
