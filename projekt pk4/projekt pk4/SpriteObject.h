#pragma once
#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <SFML/Graphics.hpp>

#include "IRenderable.h"
#include "SpriteInfo.h"

class SpriteObject : public IRenderable
{
public:
	SpriteObject(SpriteInfo& info, sf::Vector2f pos);
	virtual ~SpriteObject() {}

	virtual void update();
	virtual void draw(sf::RenderTarget& target);

	// Mutators
	virtual void setPosition(sf::Vector2f pos) { mRenderPosition = pos; }
	void setFrameLoop(int start, int stop, bool loop = true);
	// Accessors
	SpriteInfo getSpriteInfo() { return mSpriteInfo; }
	sf::Sprite& getSprite() { return mSprite; }
	sf::Vector2f getRenderPosition() { return mRenderPosition; }

protected:
	SpriteInfo& mSpriteInfo;
	sf::Sprite mSprite;
	sf::Vector2f mRenderPosition;

	int mCurrentFrame;
	sf::Clock mAnimClock;
	float mFrameDelay;
	bool mLoopAnim;
	int mStartFrame;
	int mEndFrame;
	int mFrameDir;
};

#endif // SPRITEOBJECT_H