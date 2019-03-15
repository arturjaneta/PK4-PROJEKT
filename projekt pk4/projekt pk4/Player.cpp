#include "pch.h"
#include "Player.h"

Player::Player(SpriteInfo& info, sf::Vector2f pos) :
	SpriteObject(info, pos)
{
	//ctor
}

Player::~Player()
{
	//dtor
}

void Player::update()
{
	SpriteObject::update();
}

void Player::draw(sf::RenderTarget& target)
{
	SpriteObject::draw(target);
}

void Player::handleEvents(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::W)
		{
			mPosition.y -= 5.f;
		}
		else if (event.key.code == sf::Keyboard::S)
		{
			mPosition.y += 5.f;
		}

		if (event.key.code == sf::Keyboard::A)
		{
			mPosition.x -= 5.f;
		}
		else if (event.key.code == sf::Keyboard::D)
		{
			mPosition.x += 5.f;
		}
	}
}