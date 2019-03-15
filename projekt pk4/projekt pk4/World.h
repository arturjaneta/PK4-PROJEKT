#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.h"
#include "WorldObject.h"

class World
{
public:
	~World();

	void update();
	void draw(sf::RenderTarget& target);
	void handleEvents(sf::Event& event);

	void loadWorld(std::string path);
	World(std::string path);
private:
	std::shared_ptr<Player> mPlayer;
	std::vector<std::shared_ptr<WorldObject>> mWorldObjects;
};

#endif // WORLD_H
