#include "World.h"
#include "TextNode.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "SpriteNode.h"
#include "CollisionNode.h"
World::World(sf::RenderWindow& window, FontManager& fonts)
	: mWorldView(window.getDefaultView())
	, mTextures()
	, mFonts(fonts)
	, mWindow(window)
	, mSceneGraph()
	, mSceneLayers()
	, mLevelLoader(mSceneLayers, mTextures)
	, mPlayer(nullptr)
	, mCommandQueue()

{
	buildScene();
	loadMap();
}
void World::update(sf::Time dT)
{
	mWorldView.setCenter(mPlayer->getPosition());
	mPlayer->setVelocity(0, 0);

	if (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dT);

	adaptPlayerVelocity();
	//handleCollisions();
	printf("%2f,%2f\n", mPlayer->getVelocity().x, mPlayer->getVelocity().y);
	mSceneGraph.update(dT);
}
void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}
CommandQueue& World::getWorldCommandQueue()
{
	return mCommandQueue;
}
void World::buildScene()
{
	for (int i = 0; i < Category::Type::TOTAL; ++i) {
		SceneNode::Ptr layer(new SceneNode(Category::NONE));

		mSceneLayers[i] = layer.get();
		mSceneGraph.attachNode(std::move(layer));
	}
	mTextures.load("assets/Textures/Abstract Platformer/PNG/Players/Player Blue/playerBlue_stand.png", Textures::PlayerSheet);
	std::unique_ptr<Player> player(new Player(mTextures));
	player->setPosition(80, 300);

	mPlayer = player.get();

	mSceneLayers[Category::COLLISIONBLOCK]->attachNode(std::move(player));
}

void World::loadMap()
{
	mLevelLoader.load("assets/Map/jumper.tmx");
	std::unique_ptr<SpriteNode> mBackground(new SpriteNode(mLevelLoader.getMapTexture()));
	mSceneLayers[Category::BACKGROUND]->attachNode(std::move(mBackground));
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs, getViewBounds());
	for (SceneNode::Pair pair : collisionPairs) {
		if (matchesCategories(pair, Category::PLAYER, Category::COLLISIONBLOCK)) {
			sf::FloatRect intersection;
			pair.first->getBoundingRect().intersects(pair.second->getBoundingRect(), intersection);
			auto& player = static_cast<Player&>(*pair.first);
			auto& collision = static_cast<CollisionNode&>(*pair.second);

			sf::Vector2f distance(collision.getPosition().x - player.getPosition().x,
				collision.getPosition().y - player.getPosition().y);

			sf::Vector2f playerPos(player.getPosition());

			float deltaX = player.getPosition().x - collision.getPosition().x;
			float deltaY = player.getPosition().y - collision.getPosition().y;
			if (std::abs(deltaX) > std::abs(deltaY))
				if (deltaX > 0)
					player.setPosition(playerPos.x + intersection.width, playerPos.y);
				else
					player.setPosition(playerPos.x + intersection.width, playerPos.y);
			else
				if (deltaY > 0)
					player.setPosition(playerPos.x, playerPos.y + intersection.height + 5);
				else
					player.setPosition(playerPos.x, playerPos.y + intersection.height - 5);
		}

		if (matchesCategories(pair, Category::PLAYER, Category::ENEMIES)) {
			printf("COL: P & E\n");
		}
	}
}
bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}
sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}
void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayer->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayer->setVelocity(velocity / std::sqrt(2.f));
}