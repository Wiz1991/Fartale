#pragma once
#include "MapLoader.h"
#include "SceneNode.h"
#include <array>
#include "SceneCategories.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Player.h"
#include "CommandQueue.h"
#include "Command.h"
namespace sf {
	class RenderWindow;
	class Time;
	class Event;
}

class World
{
public:
	World(sf::RenderWindow& window, FontManager& fonts);

	void update(sf::Time dT);
	void draw();

	CommandQueue& getWorldCommandQueue();
private:
	void buildScene();
	void loadMap();
	void handleCollisions();
	void adaptPlayerVelocity();
	sf::FloatRect getViewBounds() const;
private:
	sf::RenderWindow& mWindow;

	CommandQueue mCommandQueue;

	std::array<SceneNode*, Category::Type::TOTAL> mSceneLayers;
	SceneNode mSceneGraph;
	MapLoader mLevelLoader;

	TextureManager mTextures;
	FontManager& mFonts;
	sf::View mWorldView;
	Player* mPlayer;

	//DEBUGGING
};
bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);