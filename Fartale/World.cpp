#include "World.h"
#include "TextNode.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "SpriteNode.h"
#include "CollisionNode.h"
#include "Utilities.h"
#include <iomanip>
#include <sstream>

#include <SFML/Graphics/RectangleShape.hpp>

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
	, mStatistics("", fonts.get(Fonts::MAIN), 12)

{
	buildScene();
	loadMap();
	mWindow.setKeyRepeatEnabled(false);
	mStatistics.setPosition(5, 20);
	mStatistics.setFillColor(sf::Color::Black);
}
void World::update(sf::Time dT)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2)
		<< "VEL: X[" << mPlayer->getVelocity().x
		<< "] Y[" << mPlayer->getVelocity().y << "]" << "\n"
		<< "POS: X[" << mPlayer->getWorldPosition().x << "] Y["
		<< mPlayer->getPosition().y << "]";

	std::string stats = ss.str();
	mStatistics.setString(stats);

	//mWorldView.setCenter(mPlayer->getPosition());

	//mPlayer->setVelocity(0, 0);

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dT);

	//adaptPlayerVelocity();
	mSceneGraph.update(dT);
	handleCollisions(dT);
}
void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatistics);
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
	mTextures.load("assets/Textures/Abstract Platformer/PNG/Other/blockBrown.png", Textures::PlayerSheet);
	std::unique_ptr<Player> player(new Player(mTextures));
	player->setPosition(64, 64);

	mPlayer = player.get();

	mSceneLayers[Category::COLLISIONBLOCK]->attachNode(std::move(player));
}

void World::loadMap()
{
	mLevelLoader.load("assets/Map/jumper.tmx");
	std::unique_ptr<SpriteNode> mBackground(new SpriteNode(mLevelLoader.getMapTexture()));
	mSceneLayers[Category::BACKGROUND]->attachNode(std::move(mBackground));
}

void World::handleCollisions(sf::Time dT)
{
	std::vector<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs, getViewBounds());

	/*sf::Vector2f playerPos = mPlayer->getWorldPosition();*/

	/*std::sort(collisionPairs.begin(), collisionPairs.end(), [&playerPos](auto pairL, auto pairR) {
		auto left = static_cast<SceneNode*>(pairL.second);
		auto right = static_cast<SceneNode*>(pairR.second);
		sf::Vector2f vec = playerPos - left->getWorldPosition();
		float lengthLeft = (vec.x * vec.x) + (vec.y * vec.y);

		sf::Vector2f vec2 = playerPos - right->getWorldPosition();
		float lengthRight = (vec2.x * vec.x) + (vec2.y * vec.y);

		return lengthLeft < lengthRight;
		});*/

	for (SceneNode::Pair pair : collisionPairs) {
		if (matchesCategories(pair, Category::PLAYER, Category::COLLISIONBLOCK)) {
			auto& player = static_cast<Player&>(*pair.first);
			auto& collisionBlock = static_cast<CollisionNode&>(*pair.second);

			sf::FloatRect intersection;
			player.getBoundingRect().intersects(collisionBlock.getBoundingRect(), intersection);

			sf::Vector2f direction = player.getWorldPosition() - collisionBlock.getWorldPosition();
			sf::Vector2f offset(0, 0);

			if (fabs(direction.x) < fabs(direction.y)) {
				if (direction.y < 0) {
					offset.y = intersection.height;
				}
				else if (direction.y > 0) {
					offset.y = -1 * intersection.height;
				}
			}

			if (fabs(direction.x) > fabs(direction.y)) {
				if (direction.x < 0) {
					offset.x = intersection.width;
				}
				else if (direction.x > 0) {
					offset.x = -1 * intersection.width;
				}
			}
			player.setPosition(player.getPosition() - offset);
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