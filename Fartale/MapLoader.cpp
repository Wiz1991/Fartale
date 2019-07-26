#include "MapLoader.h"
#include <SFML/Graphics/Sprite.hpp>
#include "SceneNode.h"
#include "CollisionNode.h"
MapLoader::MapLoader(std::array<SceneNode*, Category::Type::TOTAL>& sceneLayers, TextureManager& textureHolder
	, float sizeX, float sizeY)
	: mSceneLayers(sceneLayers)
	, mTextureHolder(textureHolder)
{
	mMapTexture.clear();
}

void MapLoader::setSize(float sizeX, float sizeY)
{
	mMapTexture.clear();
	mMapTexture.create(sizeX, sizeY);
}

void MapLoader::load(const std::string& fileName)
{
	tmx::Map map;
	if (!map.load(fileName))
		throw std::runtime_error("MapLoader::load - failed to load map: " + fileName);

	mMapTexture.create(map.getBounds().width, map.getBounds().height);
	const auto& tileSets = map.getTilesets();
	mTextureHolder.load(tileSets[0].getImagePath(), Textures::SpriteSheet);

	sf::IntRect textureRect(0, 0, (map.getTileSize().x), (map.getTileSize().y));
	sf::Sprite tileSprite;

	mMapTexture.clear(sf::Color::White);

	const auto& layers = map.getLayers();
	int layerCount = 0;

	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Tile)
		{
			const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
			const auto& tiles = tileLayer.getTiles();

			for (auto y = 0u; y < map.getTileCount().y; ++y)
			{
				for (auto x = 0u; x < map.getTileCount().x; ++x)
				{
					auto posX = static_cast<float>(x * map.getTileSize().x);
					auto posY = static_cast<float>(y * map.getTileSize().y);
					sf::Vector2f position(posX, posY);

					auto tileID = tiles[y * map.getTileCount().x + x].ID;

					if (tileID == 0)
					{
						continue; //empty tile
					}

					auto i = 0;
					while (tileID < tileSets[i].getFirstGID())
					{
						++i;
					}

					auto relativeID = tileID - tileSets[i].getFirstGID();

					auto tileX = relativeID % tileSets[i].getColumnCount();
					auto tileY = relativeID / tileSets[i].getColumnCount();

					textureRect.left = tileX * tileSets[i].getTileSize().x;
					textureRect.top = tileY * tileSets[i].getTileSize().y;

					sf::Sprite tileSprite(mTextureHolder.get(Textures::SpriteSheet), textureRect);
					tileSprite.setPosition(position);
					mMapTexture.draw(tileSprite);
				}
			}
			mMapTexture.display();
		}

		if (layer->getType() == tmx::Layer::Type::Object) {
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();

			for (auto& obj : objects) {
				sf::FloatRect rect;
				rect.left = obj.getAABB().left;
				rect.height = obj.getAABB().height;
				rect.width = obj.getAABB().width;
				rect.top = obj.getAABB().top;

				std::unique_ptr<CollisionNode> mask(new CollisionNode(rect));
				sf::Vector2f pos(obj.getPosition().x, obj.getPosition().y);

				mask->setPosition(pos);
				mSceneLayers[Category::COLLISIONBLOCK]->attachNode(std::move(mask));
			}
		}
	}
}

const sf::Texture& MapLoader::getMapTexture()
{
	return mMapTexture.getTexture();
}