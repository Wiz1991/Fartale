#include "World.h"
#include "TextNode.h"
#include <SFML/Graphics/RenderWindow.hpp>
World::World(sf::RenderWindow& window, FontManager& fonts)
	: mTextures()
	, mFonts(fonts)
	, mWindow(window)
	, mSceneGraph()
	, mSceneLayers()
{
	buildScene();
}
void World::update(sf::Time dT)
{
}
void World::draw()
{
	mWindow.draw(mSceneGraph);
}
void World::buildScene()
{
	for (int i = 0; i < Layers::TOTAL; ++i) {
		SceneNode::Ptr layer(new SceneNode(static_cast<Layers>(i)));

		mSceneLayers[i] = layer.get();
		mSceneGraph.attachNode(std::move(layer));
	}

	std::unique_ptr<TextNode> test(new TextNode(mFonts));
	test->setText("HEEEY");
	test->setPosition(100, 100);
	test->setColor(sf::Color::Red);

	mSceneLayers[Layers::UI]->attachNode(std::move(test));
}