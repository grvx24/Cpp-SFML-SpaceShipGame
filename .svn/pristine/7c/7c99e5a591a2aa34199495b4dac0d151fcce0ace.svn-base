#pragma once
#include "GameObjects.h"
#include "Points.h"



class Upgrades
{
private:
	Timer t1;


	sf::Texture hp_up;
	sf::Texture hp_reg_up;

	sf::Texture en_up;
	sf::Texture en_reg_up;

	sf::Texture weap1_dmg;
	sf::Texture weap1_fr;

	sf::Texture weap2_dmg;
	sf::Texture weap2_fr;

	sf::Texture weap3_dmg;
	sf::Texture weap3_fr;

	sf::Sprite hp_upgrade;
	sf::Sprite hp_regen_upgrade;

	sf::Sprite energy_upgrade;
	sf::Sprite energy_regen_upgrade;

	sf::Sprite weapon1_damage_upgrade;
	sf::Sprite weapon1_rapid_fire_upgrade;

	sf::Sprite weapon2_damage_upgrade;
	sf::Sprite weapon2_rapid_fire_upgrade;

	sf::Sprite weapon3_damage_upgrade;
	sf::Sprite weapon3_rapid_fire_upgrade;


	unsigned int hp_lvl=1;
	unsigned int energy_lvl=1;
	unsigned int hp_regen_lvl=1;
	unsigned int energy_regen_lvl=1;
	unsigned int weapon1_damage_lvl=1;
	unsigned int weapon1_fire_rate_lvl=1;
	unsigned int weapon2_damage_lvl = 1;
	unsigned int weapon2_fire_rate_lvl = 1;
	unsigned int weapon3_damage_lvl = 1;
	unsigned int weapon3_fire_rate_lvl = 1;

	unsigned int average_lvl = (hp_lvl + energy_lvl + hp_regen_lvl + energy_regen_lvl + weapon1_damage_lvl + weapon1_fire_rate_lvl) / 6;

public:
	Upgrades()
	{

		hp_up.loadFromFile("textures/upgrades/Hp_upgrade.png");
		this->hp_upgrade.setTexture(hp_up);


		hp_reg_up.loadFromFile("textures/upgrades/Hp_regen_upgrade.png");
		this->hp_regen_upgrade.setTexture(hp_reg_up);


		en_up.loadFromFile("textures/upgrades/Energy_upgrade.png");
		this->energy_upgrade.setTexture(en_up);

		en_reg_up.loadFromFile("textures/upgrades/Energy_regen_upgrade.png");
		this->energy_regen_upgrade.setTexture(en_reg_up);


		weap1_dmg.loadFromFile("textures/upgrades/Basic_laser_dmg_upgrade.png");
		this->weapon1_damage_upgrade.setTexture(weap1_dmg);

		weap1_fr.loadFromFile("textures/upgrades/Basic_laser_fire_rate_upgrade.png");
		this->weapon1_rapid_fire_upgrade.setTexture(weap1_fr);


		weap2_dmg.loadFromFile("textures/upgrades/Energy_ball_dmg_upgrade.png");
		this->weapon2_damage_upgrade.setTexture(weap2_dmg);

		weap2_fr.loadFromFile("textures/upgrades/Energy_ball_fire_rate_upgrade.png");
		this->weapon2_rapid_fire_upgrade.setTexture(weap2_fr);


		weap3_dmg.loadFromFile("textures/upgrades/Blue_laser_dmg_upgrade.png");
		this->weapon3_damage_upgrade.setTexture(weap3_dmg);

		weap3_fr.loadFromFile("textures/upgrades/Blue_laser_fire_rate_upgrade.png");
		this->weapon3_rapid_fire_upgrade.setTexture(weap3_fr);


		hp_upgrade.setPosition(550, 400);
		hp_regen_upgrade.setPosition(750, 300);

		energy_upgrade.setPosition(900, 100);
		energy_regen_upgrade.setPosition(1100, 100);

		weapon1_damage_upgrade.setPosition(200, 550);
		weapon1_rapid_fire_upgrade.setPosition(400, 550);

		weapon2_damage_upgrade.setPosition(750, 500);
		weapon2_rapid_fire_upgrade.setPosition(900, 500);

		weapon3_damage_upgrade.setPosition(1000, 350);
		weapon3_rapid_fire_upgrade.setPosition(1200, 350);


	}

	void draw_integer(int number,sf::RenderWindow &window)
	{


	}


	bool CheckForMouseTrigger(sf::Sprite &sprite, sf::RenderWindow &window)
	{

		int mouseX = sf::Mouse::getPosition().x;
		int mouseY = sf::Mouse::getPosition().y;

		
		sf::Vector2i windowPosition = window.getPosition();

		if (mouseX > sprite.getPosition().x + windowPosition.x && mouseX < (sprite.getPosition().x + sprite.getGlobalBounds().width + windowPosition.x)
			&& mouseY > sprite.getPosition().y + windowPosition.y + 30 && mouseY < (sprite.getPosition().y + sprite.getGlobalBounds().height + windowPosition.y + 30))
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				return true;
			}
			return false;
		}

		return false;

	}


	bool CheckIfMouseOnObject(sf::Sprite &sprite, sf::RenderWindow &window)
	{

		int mouseX = sf::Mouse::getPosition().x;
		int mouseY = sf::Mouse::getPosition().y;


		sf::Vector2i windowPosition = window.getPosition();

		if (mouseX > sprite.getPosition().x + windowPosition.x && mouseX < (sprite.getPosition().x + sprite.getGlobalBounds().width + windowPosition.x)
			&& mouseY > sprite.getPosition().y + windowPosition.y + 30 && mouseY < (sprite.getPosition().y + sprite.getGlobalBounds().height + windowPosition.y + 30))
		{

			return true;
		}

		return false;

	}


	void draw_all(sf::RenderWindow &window,Points &points,Interface &inter,Player &player)
	{
		window.draw(this->hp_upgrade);
		window.draw(this->hp_regen_upgrade);

		window.draw(this->energy_upgrade);
		window.draw(this->energy_regen_upgrade);

		window.draw(this->weapon1_damage_upgrade);
		window.draw(this->weapon1_rapid_fire_upgrade);

		window.draw(this->weapon2_damage_upgrade);
		window.draw(this->weapon2_rapid_fire_upgrade);

		window.draw(this->weapon3_damage_upgrade);
		window.draw(this->weapon3_rapid_fire_upgrade);


		inter.draw_HP(player, window);
		inter.draw_Energy(player, window);
		inter.draw_points(points, window);
		inter.draw_cash(points, window);
		

	}
	

	void upgrade_on_click(sf::RenderWindow &window, Player &player, Weapon &weapon1, Weapon &weapon2, Weapon &weapon3,Points &points,Interface &inter)
	{
		if (CheckIfMouseOnObject(this->hp_upgrade, window))
		{
			inter.draw_text("Max HP", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * hp_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(hp_lvl, window, 80, 400, 200, sf::Color::Black);

		}

		if (CheckForMouseTrigger(this->hp_upgrade, window)&&t1.Basic_spawner(500))
		{
		
			
			if (points.get_cash() >= 100*hp_lvl)
			{	

				points.consume_cash(100*hp_lvl);
				player.increase_max_hp(20);
				player.heal_up(10000);
				hp_lvl++;

			}


		}

		if (CheckIfMouseOnObject(this->hp_regen_upgrade, window))
		{
			inter.draw_text("HP regeneration", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * hp_regen_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(hp_regen_lvl, window, 80, 400, 200, sf::Color::Black);

		}
			
		if (CheckForMouseTrigger(this->hp_regen_upgrade, window) && t1.Basic_spawner(500))
		{

			if (points.get_cash() >= 100 * hp_regen_lvl)
			{
				points.consume_cash(100 * hp_regen_lvl);
				player.increase_hp_regen(1);

				hp_regen_lvl++;

			}


		}

		if (CheckIfMouseOnObject(this->energy_upgrade, window))
		{
			inter.draw_text("Max Energy", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * energy_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(energy_lvl, window, 80, 400, 200, sf::Color::Black);

		}

		if (CheckForMouseTrigger(this->energy_upgrade, window) && t1.Basic_spawner(500))
		{

			if (points.get_cash() >= 100 * energy_lvl)
			{

				points.consume_cash(100 * energy_lvl);
				player.increase_max_energy(20);

				energy_lvl++;

			}


		}

		if (CheckIfMouseOnObject(this->energy_regen_upgrade, window))
		{
			inter.draw_text("Energy regeneration", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * energy_regen_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(energy_regen_lvl, window, 80, 400, 200, sf::Color::Black);

		}

		if (CheckForMouseTrigger(this->energy_regen_upgrade, window) && t1.Basic_spawner(500))
		{

			if (points.get_cash() >= 100 * energy_regen_lvl)
			{

				points.consume_cash(100 * energy_regen_lvl);
				player.increase_energy_regen(1);

				energy_regen_lvl++;

			}


		}

		if (CheckIfMouseOnObject(this->weapon1_damage_upgrade, window))
		{
			inter.draw_text("Damage", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * weapon1_damage_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(weapon1_damage_lvl, window, 80, 400, 200, sf::Color::Black);

		}

		if (CheckForMouseTrigger(this->weapon1_damage_upgrade, window) && t1.Basic_spawner(500))
		{

			if (points.get_cash() >= 100 * weapon1_damage_lvl)
			{

				points.consume_cash(100 * weapon1_damage_lvl);
				weapon1.increase_damage(10);

				weapon1_damage_lvl++;

			}


		}


		if (CheckIfMouseOnObject(this->weapon1_rapid_fire_upgrade, window))
		{
			inter.draw_text("Fire rate", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * weapon1_fire_rate_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(weapon1_fire_rate_lvl, window, 80, 400, 200, sf::Color::Black);

		}




		if (CheckForMouseTrigger(this->weapon1_rapid_fire_upgrade, window) && t1.Basic_spawner(500))
		{

			if (points.get_cash() >= 100 * weapon1_fire_rate_lvl)
			{
				points.consume_cash(100 * weapon1_fire_rate_lvl);
				weapon1.increase_fire_rate(0.5f);

				weapon1_fire_rate_lvl++;

			}


		}


		if (CheckIfMouseOnObject(this->weapon2_damage_upgrade, window))
		{
			inter.draw_text("Damage", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * weapon2_damage_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(weapon2_damage_lvl, window, 80, 400, 200, sf::Color::Black);

		}

		if (CheckForMouseTrigger(this->weapon2_damage_upgrade, window) && t1.Basic_spawner(500))
		{

			if (points.get_cash() >= 100 * weapon2_damage_lvl)
			{

				points.consume_cash(100 * weapon2_damage_lvl);
				weapon1.increase_damage(10);

				weapon2_damage_lvl++;

			}


		}


		if (CheckIfMouseOnObject(this->weapon2_rapid_fire_upgrade, window))
		{
			inter.draw_text("Fire rate", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * weapon2_fire_rate_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(weapon2_fire_rate_lvl, window, 80, 400, 200, sf::Color::Black);

		}

		if (CheckForMouseTrigger(this->weapon2_rapid_fire_upgrade, window) && t1.Basic_spawner(500))
		{

			if (points.get_cash() >= 100 * weapon2_fire_rate_lvl)
			{
				points.consume_cash(100 * weapon2_fire_rate_lvl);
				weapon1.increase_fire_rate(0.5f);

				weapon2_fire_rate_lvl++;

			}


		}


		////

		if (CheckIfMouseOnObject(this->weapon3_damage_upgrade, window))
		{
			inter.draw_text("Damage", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * weapon3_damage_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(weapon3_damage_lvl, window, 80, 400, 200, sf::Color::Black);

		}

		if (CheckForMouseTrigger(this->weapon3_damage_upgrade, window) && t1.Basic_spawner(500))
		{

			if (points.get_cash() >= 100 * weapon3_damage_lvl)
			{

				points.consume_cash(100 * weapon3_damage_lvl);
				weapon1.increase_damage(10);

				weapon3_damage_lvl++;

			}


		}


		if (CheckIfMouseOnObject(this->weapon3_rapid_fire_upgrade, window))
		{
			inter.draw_text("Fire rate", window, 80, 50, 0, sf::Color::Black);

			inter.draw_text("Price: ", window, 80, 50, 100, sf::Color::Black);
			inter.draw_integer(100 * weapon3_fire_rate_lvl, window, 80, 400, 100, sf::Color::Black);

			inter.draw_text("Level: ", window, 80, 50, 200, sf::Color::Black);
			inter.draw_integer(weapon3_fire_rate_lvl, window, 80, 400, 200, sf::Color::Black);

		}

		if (CheckForMouseTrigger(this->weapon3_rapid_fire_upgrade, window) && t1.Basic_spawner(500))
		{

			if (points.get_cash() >= 100 * weapon3_fire_rate_lvl)
			{
				points.consume_cash(100 * weapon3_fire_rate_lvl);
				weapon1.increase_fire_rate(0.5f);

				weapon3_fire_rate_lvl++;

			}


		}




	}


};



