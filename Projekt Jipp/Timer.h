#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>


class Timer
{
private:
	sf::Clock main_clock;


public:

	Timer()
	{

		main_clock.restart();
	}

	bool Basic_spawner(int milliseconds)
	{
		sf::Time elapsed = main_clock.getElapsedTime();
		sf::Time delay = sf::milliseconds(milliseconds);

		if (elapsed > delay)
		{
			main_clock.restart();
			return true;
		}
		return false;

	}
	
};