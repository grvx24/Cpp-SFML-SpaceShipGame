#pragma once

#include "GameObjects.h"
#include "Points.h"

#include <cstdlib>
#include <string>
#include <SFML\Graphics.hpp>


class Interface
{
private:
	sf::Font font;


public:

	Interface(sf::Font font)
	{
		this->font = font;
	}

	
	bool CheckForMouseTrigger(sf::Text &text, sf::RenderWindow &window)
	{

		int mouseX = sf::Mouse::getPosition().x;
		int mouseY = sf::Mouse::getPosition().y;

		sf::Vector2i windowPosition = window.getPosition();

		if (mouseX > text.getPosition().x + windowPosition.x && mouseX < (text.getPosition().x + text.getGlobalBounds().width + windowPosition.x)
			&& mouseY > text.getPosition().y + windowPosition.y + 30 && mouseY < (text.getPosition().y + text.getGlobalBounds().height + windowPosition.y + 30))
		{
			text.setColor(sf::Color::Red);
			window.draw(text);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				return true;
			}
			return false;
		}

		return false;

	}

	void draw_text(std::string text, sf::RenderWindow &window, unsigned int size, float x_pos, float y_pos, sf::Color color)
	{
		sf::Text txt(text, this->font, size);
		txt.setPosition(x_pos, y_pos);
		txt.setColor(color);
		window.draw(txt);
	}


	void draw_integer(int number,sf::RenderWindow &window,unsigned int size,float x_pos,float y_pos,sf::Color color)
	{
		std::string str = std::to_string(number);
		sf::Text text(str, this->font, size);
		text.setPosition(x_pos, y_pos);
		text.setColor(color);
		window.draw(text);
	}



	void main_Menu(sf::RenderWindow &window,bool &menu,Points &points,sf::Sprite &menu_theme)
	{
		sf::Font font1;
		font1.loadFromFile("fonts/optimus/Optimus Bold.otf");

		window.draw(menu_theme);



		sf::Text start("New Game", font1, 100);
		start.setPosition(100,300);

		sf::Text _exit("Exit", font1, 100);
		_exit.setColor(sf::Color::White);
		_exit.setPosition(100, 500);

		window.draw(start);
		window.draw(_exit);


		draw_text("Controlls", window, 40, 800, 0, sf::Color::White);
		draw_text("Mouse buttons - weapons", window, 40, 800, 100, sf::Color::White);
		draw_text("WASD - movement", window, 40,800, 200, sf::Color::White);
		draw_text("Esc - Upgrades", window, 40, 800, 300, sf::Color::White);



		if (CheckForMouseTrigger(start, window))
		{
			points.reset_points();
			menu = false;
		}



		if (CheckForMouseTrigger(_exit, window))
		{
			exit(0);
		}




	}




	void draw_HP(Player &player,sf::RenderWindow &window)
	{
		std::string hp_num = std::to_string(player.get_HP());
	
		
		sf::Text hp_number(hp_num, this->font, 80);
		hp_number.setColor(sf::Color::Red);
		hp_number.setPosition(window.getSize().x - 400,window.getSize().y-100);


		window.draw(hp_number);



	}


	void draw_Energy(Player &player, sf::RenderWindow &window)
	{
		std::string energy_num = std::to_string(player.get_Energy());


		sf::Text energy_number(energy_num, this->font, 80);
		energy_number.setColor(sf::Color::Yellow);

		energy_number.setPosition(window.getSize().x - 200, window.getSize().y - 100);


		window.draw(energy_number);



	}

	void draw_cash(Points &points, sf::RenderWindow &window)
	{
		std::string cash_num = std::to_string(points.get_cash());


		sf::Text cash_number(cash_num+" $", this->font, 80);
		cash_number.setColor(sf::Color::Green);

		cash_number.setPosition(window.getSize().x - 850, window.getSize().y - 100);


		window.draw(cash_number);
		
	}


	void draw_points(Points &points, sf::RenderWindow &window)
	{
		std::string points_num = std::to_string(points.get_points());


		sf::Text points_number(points_num + " *", this->font, 80);
		points_number.setColor(sf::Color::White);

		points_number.setPosition(window.getSize().x - 1300, window.getSize().y - 100);


		window.draw(points_number);

	}


	void draw_game_over(sf::RenderWindow &window,Points &points)
	{
		std::string points_string = std::to_string(points.get_points());
		sf::Text game_over("Game over - your score: " + points_string, this->font,80);
		game_over.setPosition(100, 100);
		game_over.setColor(sf::Color::Red);
		window.draw(game_over);

	}
};