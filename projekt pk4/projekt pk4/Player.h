#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "SpriteInfo.h"

class Player
{
public:
	Player(SpriteInfo& info);
	~Player();

	void update();
	void draw(sf::RenderTarget& target);
	void handleEvents(sf::Event& event);

private:
	SpriteInfo& mSpriteInfo;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
};

#endif // PLAYER_H