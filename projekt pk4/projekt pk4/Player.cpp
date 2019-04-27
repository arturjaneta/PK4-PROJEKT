#include "pch.h"
#include "Player.h"

Player::Player(SpriteInfo& info, sf::Vector2f pos) :
	WorldObject(info, pos)
{

}

void Player::update()
{
	SpriteObject::update();

	mOldPhysicsPosition = mPhysicsPosition;		//zapisanie poprzedniej pozycji
	mPhysicsPosition += mVelocity;				//ustawienie nowej pozycji
}

void Player::draw(sf::RenderTarget& target)
{
	SpriteObject::draw(target);

	mRenderPosition = mPhysicsPosition;			//taka sama fizyczna pozycja i widoczna
}

void Player::handleEvents(sf::Event& event)							//poruszanie sie
{
	if (event.type == sf::Event::KeyPressed)					
	{
		if (event.key.code == sf::Keyboard::W)
			mVelocity.y = -1.f;										//predkosc przemieszczania
		else if (event.key.code == sf::Keyboard::S)
			mVelocity.y = 1.f;
		if (event.key.code == sf::Keyboard::A)
			mVelocity.x = -1.f;
		else if (event.key.code == sf::Keyboard::D)
			mVelocity.x = 1.f;
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W)
			mVelocity.y = 0.f;
		else if (event.key.code == sf::Keyboard::S)
			mVelocity.y = 0.f;
		if (event.key.code == sf::Keyboard::A)
			mVelocity.x = 0.f;
		else if (event.key.code == sf::Keyboard::D)
			mVelocity.x = 0.f;
	}
}