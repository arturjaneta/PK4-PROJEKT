#include "pch.h"
#include "Player.h"

Player::Player(SpriteInfo& info) :
	mSpriteInfo(info)
{
	mSprite = sf::Sprite(mSpriteInfo.mTexture);
}

Player::~Player()
{
	//dtor
}

void Player::update()
{
	mSprite.setPosition(mPosition);
}

void Player::draw(sf::RenderTarget& target)
{
	target.draw(mSprite);
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