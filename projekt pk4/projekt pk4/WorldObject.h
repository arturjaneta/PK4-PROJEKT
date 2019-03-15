#pragma once
#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "SpriteObject.h"
class WorldObject : public SpriteObject
{
public:
	WorldObject(SpriteInfo& info, sf::Vector2f pos);
	~WorldObject();

	void update();
	void draw(sf::RenderTarget& target);

private:
};

#endif // WORLDOBJECT_H