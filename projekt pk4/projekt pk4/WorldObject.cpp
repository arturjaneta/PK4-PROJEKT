#include "pch.h"
#include "WorldObject.h"


WorldObject::WorldObject(SpriteInfo& info, sf::Vector2f pos) :
	SpriteObject(info, pos),
	ICollideable(info.mHitBox, info.mFrameDim, pos)
{

}

void WorldObject::update()
{
	SpriteObject::update();

	mOldPhysicsPosition = mPhysicsPosition;				//zapsanie poprzedniej pozycji
	mPhysicsPosition += mVelocity;						//ustawienie nowej pozycji
}

void WorldObject::draw(sf::RenderTarget& target)
{
	SpriteObject::draw(target);
	mRenderPosition = mPhysicsPosition;					//taka sama pozycja fizyczna i widoczna
}