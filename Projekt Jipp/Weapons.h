#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "GameObjects.h"
#include <vector>

class Bullet :public GameObject
{
private:
	int damage;
	float forward_dev;//domyslnie pocisk wylatuje ze srodka objektu
	float side_dev;//te zmienne decyduja o odchyleniu od srodka objektu
	Timer t1;

public:
	float angle; //kierunek strzalu ;)

	Bullet(sf::Texture &texture, sf::Vector2f position, float radius, int damage) :GameObject(texture, position,radius), damage(damage), angle(0), forward_dev(0), side_dev(0)
	{

	}
	void setDamage(int damage)
	{
		this->damage = damage;
	}

	int get_damage()
	{
		return this->damage;
	}

	void increase_damage(int value)
	{
		this->damage += value;
	}

	//ustawienie odchylenia dla pionu i poziomu
	void set_forward_deviation(float value)
	{
		this->forward_dev = value;
	}

	void set_side_deviation(float value)
	{
		this->side_dev = value;
	}

	void shoot(Player &player, sf::Clock &bulletClock)
	{
		this->angle = (player.getRotation() - 90) *M_PI / 180;
		sf::Vector2f forward_deviation = sf::Vector2f(cos(angle)*forward_dev, sin(angle)*forward_dev);
		sf::Vector2f side_deviation = sf::Vector2f(sin(angle)*side_dev, cos(angle)*side_dev);


		this->exists = true;
		this->setPosition(player.getPosition()+forward_deviation+side_deviation);
		this->setRotation(player.getRotation());
		this->collider.setPosition(this->getPosition());
		this->collider.setRotation(player.getRotation());

		player.canShoot = false;

		bulletClock.restart();


	}


	bool check_collision(Enemy &enemy)
	{
		if (this->collider.getGlobalBounds().intersects(enemy.getCollider().getGlobalBounds())&&enemy.exists)
		{
			return true;
		}
		else return false;
	}


	void move(sf::RenderWindow &window,float speed)
	{
		this->sprite.move(speed*cos(angle), speed*sin(angle));
		this->collider.move(speed*cos(angle), speed*sin(angle));



		if (this->sprite.getPosition().x > window.getSize().x+25 || this->sprite.getPosition().x<-25 || this->sprite.getPosition().y>window.getSize().y+25 || this->sprite.getPosition().y < -25)
		{
			exists = false;
		}

	}

	void attack(Enemy &enemy,Points &points_object)
	{

			enemy.get_damage(this->damage, points_object);

	}


	void move_with_collision(sf::RenderWindow &window, float speed, std::vector<Enemy> &enemies,bool disappear,Points &points_object,int collision_delay)
	{
		this->move(window, speed);

		for (int i = 0; i < enemies.size(); i++)
		{
			if (this->check_collision(enemies[i]) && exists == true)
			{
				//std::cout << "Kolizja z pociskiem" << std::endl;
				if(disappear)
				this->exists = false;

				if (t1.Basic_spawner(collision_delay))
				attack(enemies[i],points_object);
			}
		}

	}




};

//Sluzy do indeksowania tablicy pociskow, tak zeby indeks po osiagnieciu max zmienial sie na 0
class BulletData
{
public:

	int nextBullet;//liczba dostepnych pociskow

	BulletData():nextBullet(0){}
	void Next(int totalBullets)
	{
		if (nextBullet < totalBullets) nextBullet += 1;
		if (nextBullet == totalBullets) nextBullet = 0;

	}


};



class Weapon
{
private:
	std::vector<Bullet> bullets;
	float speed;
	float fire_rate;
	float _f_rate;
	BulletData bData;


	sf::Clock bullet_clock;
	

public:
	Weapon(Bullet pattern,int num_of_bullets,float speed,float fire_rate):speed(speed),fire_rate(1000/fire_rate),_f_rate(fire_rate)
	{
		for (int i = 0; i < num_of_bullets; i++)
		{
			bullets.push_back(pattern);
			bullet_clock.restart();
		}
	}

	~Weapon()
	{
		bullets.clear();
	}



	void increase_damage(int value)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].increase_damage(value);
		}
	}

	void increase_fire_rate(float value)
	{
		this->_f_rate += value;
		this->fire_rate = 1000 / _f_rate;
	}


	void DrawBullet(sf::RenderWindow &window)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if(bullets[i].exists)
			bullets[i].draw(window);
		}
	}

	


	void MoveBullet(sf::RenderWindow &window)
	{



		for (int i = 0; i < bullets.size(); i++)
		{

			if (bullets[i].exists) 
			{ 
				bullets[i].move(window, this->speed);
			}

		}

	}






	void play(sf::RenderWindow &window, std::vector<Enemy> &enemies, bool disappear, Points &points_object,int collision_delay)//rysuje i porusza pociskiem
	{
		for (int i = 0; i < bullets.size(); i++)
		{

			if (bullets[i].exists)
			{
				bullets[i].move_with_collision(window, this->speed, enemies, disappear, points_object,collision_delay);
			}

			if (bullets[i].exists)
				bullets[i].draw(window);

		}
	}




	void CheckBulletClock(Player &player) //tu nastepuje zmiana pocisku w tablicy co okreslony czas
	{

		sf::Time elapsed = bullet_clock.getElapsedTime();
		sf::Time delay = sf::milliseconds(fire_rate);

		if (elapsed > delay)
		{
			bData.Next(bullets.size());
			player.canShoot = true;
			//std::cout << "moze strzelac" << std::endl;
			bullet_clock.restart();



		}




	}


	void shoot(Player &player)
	{
		if (!bullets[bData.nextBullet].exists)
		{
			bullets[bData.nextBullet].shoot(player, bullet_clock);
		}
	}

	void shoot_and_consume_energy(Player &player,int energy_cost)
	{
		if (!bullets[bData.nextBullet].exists)
		{
			player.lose_energy(energy_cost);
			bullets[bData.nextBullet].shoot(player, bullet_clock);
		}
	}






};





