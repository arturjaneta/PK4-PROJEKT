// projekt pk4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Assets.h"
#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Jakos szpila 2D");
	Assets::loadAssets();
	sf::Sprite testObj(Assets::sprites["ammocrate"].mTexture);
	testObj.setPosition(sf::Vector2f(300.f, 200.f));
	Player player(Assets::sprites["player"]);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

				player.handleEvents(event);
		}

		player.update();

		window.clear();
		player.draw(window);
		window.display();
	}

	return 0;
}
