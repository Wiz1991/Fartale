#pragma once
#include "SceneCategories.h"
#include <array>
#include <stdexcept>

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/LayerGroup.hpp>

#include "ResourceIdentifiers.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>

class SceneNode;
class SpriteNode;

class MapLoader
{
public:
	MapLoader(std::array<SceneNode*, Category::Type::TOTAL>& sceneLayers, TextureManager& textureHolder
		, float sizeX = 0, float sizeY = 0);

	void setSize(float sizeX, float sizeY);

	void load(const std::string& fileName);

	const sf::Texture& getMapTexture();

private:
	std::array<SceneNode*, Category::Type::TOTAL>& mSceneLayers;
	TextureManager& mTextureHolder;

	sf::RenderTexture mMapTexture;
};
