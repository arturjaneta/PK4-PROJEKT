#include "pch.h"
#include "WorldObject.h"


WorldObject::WorldObject(SpriteInfo& info, sf::Vector2f pos) :
	SpriteObject(info, pos)
{
	//ctor
}

WorldObject::~WorldObject()
{
	//dtor
}

void WorldObject::update()
{
	SpriteObject::update();
}

void WorldObject::draw(sf::RenderTarget& target)
{
	SpriteObject::draw(target);
}