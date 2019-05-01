#include "pch.h"
#include "World.h"
#include <fstream>
#include "Assets.h"
#define xGravity 0.f
#define yGravity 0.1f

World::World(std::string path)
{
	mPlayer = std::make_shared<Player>(Assets::sprites["player"], sf::Vector2f());
	mCollideables.push_back(mPlayer);
	Gravity = sf::Vector2f(xGravity, yGravity);
	loadWorld(path);
}

bool World::checkCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
{
	sf::Vector2f a1 = a.lock()->getPhysicsPosition() + sf::Vector2f(a.lock()->getHitBox().left, a.lock()->getHitBox().top);
	sf::Vector2f a2 = sf::Vector2f(a.lock()->getHitBox().width, a.lock()->getHitBox().height);

	sf::Vector2f b1 = b.lock()->getPhysicsPosition() + sf::Vector2f(b.lock()->getHitBox().left, b.lock()->getHitBox().top);
	sf::Vector2f b2 = sf::Vector2f(b.lock()->getHitBox().width, b.lock()->getHitBox().height);

	sf::FloatRect aRect(a1, a2);
	sf::FloatRect bRect(b1, b2);

	if (aRect.intersects(bRect))
		return true;

	return false;
}

void World::resolveCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
{


	auto aLeft = a.lock()->getPhysicsPosition().x + a.lock()->getHitBox().left;
	auto aTop = a.lock()->getPhysicsPosition().y + a.lock()->getHitBox().top;
	auto aRight = aLeft + a.lock()->getHitBox().width;
	auto aBottom = aTop + a.lock()->getHitBox().height;

	auto bLeft = b.lock()->getPhysicsPosition().x + b.lock()->getHitBox().left;
	auto bTop = b.lock()->getPhysicsPosition().y + b.lock()->getHitBox().top;
	auto bRight = bLeft + b.lock()->getHitBox().width;
	auto bBottom = bTop + b.lock()->getHitBox().height;

	float overlapLeft{ aRight - bLeft };
	float overlapRight{ bRight - aLeft };
	float overlapTop{ aBottom - bTop };
	float overlapBottom{ bBottom - aTop };

	bool fromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
	bool fromTop(std::abs(overlapTop) < std::abs(overlapBottom));

	float minOverlapX{ fromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ fromTop ? overlapTop : overlapBottom };

	auto y_collision = [a, fromTop](float overlapY)
	{
		a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
		if (fromTop)
		{
			a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x, a.lock()->getPhysicsPosition().y - overlapY));
		}
		else if (!fromTop)
		{
			a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x, a.lock()->getPhysicsPosition().y + overlapY));
		}
	};

	auto x_collision = [a, fromLeft, fromTop, y_collision](float overlapX)
	{

		a.lock()->setVelocity(sf::Vector2f(0.f, a.lock()->getVelocity().y));

		if (fromLeft)
		{
			a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x - overlapX, a.lock()->getPhysicsPosition().y));
		}
		else if (!fromLeft)
		{
			a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x + overlapX, a.lock()->getPhysicsPosition().y));
		}
	};
	if (a.lock()->ContactBegin(b, fromLeft, fromTop) && b.lock()->ContactBegin(a, fromLeft, fromTop))
	{
		if (std::abs(minOverlapX) > std::abs(minOverlapY)) // y overlap
		{
			y_collision(minOverlapY);
		}
		else // x overlap
		{
			x_collision(minOverlapX);
		}
	}
		a.lock()->ContactEnd(b);
		b.lock()->ContactEnd(a);
}


void World::update()
{
	mPlayer->update();
	mPlayer->setVelocity(mPlayer->getVelocity()+Gravity*0.0166f);

	for (auto& obj : mWorldObjects) {
		obj->update();
		if (!obj->isStatic()) {
			obj->setVelocity(obj->getVelocity() + Gravity * 0.0166f);
		}
	}

	// check collisions
	for (std::size_t x = 0; x < mCollideables.size(); x++)
	{
		for (std::size_t y = x + 1; y < mCollideables.size(); y++)
		{
			auto dynamic = mCollideables[x];
			auto _static = mCollideables[y];

			if (!mCollideables[x].lock()->isStatic())
				dynamic = mCollideables[x];
			else if (!mCollideables[y].lock()->isStatic())
				dynamic = mCollideables[y];

			if (mCollideables[x].lock()->isStatic())
				_static = mCollideables[x];
			else if (mCollideables[x].lock()->isStatic())
				_static = mCollideables[y];

			if (checkCollision(dynamic, _static) && dynamic.lock()->isCollisionActive() && _static.lock()->isCollisionActive())
				resolveCollision(dynamic, _static);
		}
	}
}

void World::draw(sf::RenderTarget& target)
{
	mPlayer->draw(target);

	for (auto& obj : mWorldObjects)
		obj->draw(target);
}

void World::handleEvents(sf::Event& event)
{
	mPlayer->handleEvents(event);
}

void World::loadWorld(std::string path)
{
	std::ifstream file(path);

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string id = "";
			float x = 0;
			float y = 0;
			file >> id >> x >> y;

			auto newObj = std::make_shared<WorldObject>(Assets::sprites[id], sf::Vector2f(x, y));
			mWorldObjects.push_back(newObj);
			mCollideables.push_back(newObj);
		}
	}
}