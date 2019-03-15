#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "SpriteObject.h"
#include "SpriteInfo.h"

class Player : public SpriteObject
{
public:
	Player(SpriteInfo& info, sf::Vector2f pos);
	~Player();

	void update();
	void draw(sf::RenderTarget& target);
	void handleEvents(sf::Event& event);

private:
	sf::Vector2f mPosition;
};

#endif // PLAYER_H