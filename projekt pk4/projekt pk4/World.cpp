#include "pch.h"
#include "World.h"
#include <fstream>
#include "Assets.h"
#include "SpriteInfo.h"


World::World(std::string path)
{
	mPlayer = std::make_shared<Player>(Assets::sprites["player"],sf::Vector2f(0.f, 0.f));		//cos tu nie tak

	loadWorld(path);
}

World::~World()
{
	//dtor
}

void World::update()
{
	mPlayer->update();

	for (auto& obj : mWorldObjects)
		obj->update();
}

void World::draw(sf::RenderTarget& target)
{
	mPlayer->draw(target);

	for (auto& obj : mWorldObjects)
		obj->draw(target);
}

void World::handleEvents(sf::Event& event)
{
	mPlayer->handleEvents(event);
}
void World::loadWorld(std::string path)
{
	
	std::string line = "";
	std::ifstream file(path);

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string id = "";
			float x = 0;
			float y = 0;
			file >> id >> x >> y;

			auto newObj = std::make_shared<WorldObject>(Assets::sprites[id], sf::Vector2f(x, y));
			mWorldObjects.push_back(newObj);
		}
	}
}