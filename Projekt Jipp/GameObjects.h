#pragma once
#include <SFML\Graphics.hpp>


#define _USE_MATH_DEFINES
#include <math.h>
#include <list>

#include "Timer.h"
#include "Points.h"


class GameObject
{


protected:
	sf::Sprite sprite;
	sf::CircleShape collider;

public:
	

	GameObject(sf::Texture &texture, sf::Vector2f position,float collider_radius) :exists(false)
	{	
		this->sprite.setTexture(texture);
		this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
		this->sprite.setPosition(position);
		this->collider.setOrigin(collider_radius,collider_radius);
		this->collider.setRadius(collider_radius);
		this->collider.setPosition(position);
		this->collider.setFillColor(sf::Color::Green);
	}
	~GameObject()
	{

	}

	//ustawianie parametrow
	virtual void setPosition(sf::Vector2f position)
	{
		this->sprite.setPosition(position);
		this->collider.setPosition(position);
	}
	virtual void setPosition(float x, float y)
	{
		this->sprite.setPosition(x,y);
		this->collider.setPosition(x,y);
	}
	virtual void setRotation(float angle)
	{
		this->sprite.setRotation(angle);
	}

	virtual void setCollider_Radius(float x)
	{
		this->collider.setRadius(x);
	}

	//odczyt parametrow
	virtual sf::Vector2f getPosition()
	{
		return this->sprite.getPosition();
	}
	virtual sf::Sprite getSprite()
	{
		return this->sprite;
	}
	virtual sf::CircleShape getCollider()
	{
		return this->collider;
	}
	virtual float getRotation()
	{
		return this->sprite.getRotation();
	}

	

	// poruszanie
	void move(sf::Vector2f position)
	{
		this->sprite.move(position);
		this->collider.move(position);
	}
	void move(float x, float y)
	{
		this->sprite.move(x, y);
		this->collider.move(x, y);
	}

	//czy ma byc widoczne czy nie
	bool exists;

	virtual void draw(sf::RenderWindow &window)
	{
		if(this->exists)
		window.draw(this->sprite);
		//window.draw(this->collider);
	}




};





class Player : public GameObject
{
private:
	int hp;
	int energy;
	float speed;
	float acceleration;

	int hp_reg=0;
	int energy_reg=1;


	int curr_hp;
	int curr_energy;
	Timer hp_timer;
	Timer energy_timer;

	float curr_speed = 0;



public:

	bool canShoot;

	Player(sf::Texture &texture, sf::Vector2f position,float radius,int hp, int energy, float speed,float acceleration):GameObject(texture,position,radius),hp(hp),energy(energy),speed(speed),acceleration(acceleration),canShoot(true),curr_hp(hp), curr_energy(energy)
	{

	}

	void change_speed(float value)
	{
		this->speed = value;
	}

	void change_acceleration(float value)
	{
		this->acceleration = value;
	}

	int get_HP()
	{
		return this->curr_hp;
	}

	int get_Energy()
	{
		return this->curr_energy;
	}


	void get_damage(int value)
	{
		this->curr_hp -= value;
		if (this->curr_hp <= 0)
		{
			exists = false;
		}
	}

	void lose_energy(int value)
	{
		if(curr_energy>0)
		this->curr_energy -= value;

	}

	void hp_regen(int time_miliseconds)
	{
		if (this->curr_hp > hp) this->curr_hp = hp;

		if (this->hp_timer.Basic_spawner(time_miliseconds) && this->curr_hp<hp)
		{

			this->curr_hp += this->hp_reg;
		}
	}


	void energy_regen(int time_miliseconds)
	{
		if (this->energy_timer.Basic_spawner(time_miliseconds)&&this->curr_energy<energy)
		{
			if (this->curr_energy > energy) this->curr_energy = energy;

			this->curr_energy += this->energy_reg;
		}
	}



	void heal_up(int value)
	{
		this->curr_hp += value;
		if (curr_hp > hp)
			curr_hp = hp;
	}
	void energy_up(int value)
	{
		this->curr_energy += value;
		if (curr_energy > energy)
			curr_energy = energy;
		
	}


	bool game_over()
	{
		if (exists == false)
			return true;
		else return false;
	}


	void Controller(sf::RenderWindow &window)
	{
		if (this->sprite.getPosition().x > window.getSize().x - 25)
		{
			this->sprite.setPosition(this->sprite.getPosition().x + (-5), this->sprite.getPosition().y);
			this->collider.setPosition(this->collider.getPosition().x + (-5), this->collider.getPosition().y);
		}
		if (this->sprite.getPosition().x < 0 + 25)
		{
			this->sprite.setPosition(this->sprite.getPosition().x + 5, this->sprite.getPosition().y);
			this->collider.setPosition(this->collider.getPosition().x + 5, this->collider.getPosition().y);
		}
		if (this->sprite.getPosition().y > window.getSize().y - 25)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + (-5));
			this->collider.setPosition(this->collider.getPosition().x, this->collider.getPosition().y + (-5));
		}

		if (this->sprite.getPosition().y < 0 + 25)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + 5);
			this->collider.setPosition(this->collider.getPosition().x, this->collider.getPosition().y + 5);
		}


		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f playerPosition = this->sprite.getPosition();



		float radian = atan2(mousePosition.x - playerPosition.x, mousePosition.y - playerPosition.y);
		float angle = 180 * radian / M_PI;
		
		this->sprite.setRotation(-angle + 180);


	
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->curr_speed+= acceleration;
			if (curr_speed > this->speed)curr_speed = this->speed;


			this->move(0.0f, -curr_speed);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{

			curr_speed += acceleration;
			if (curr_speed > this->speed)curr_speed = this->speed;


			this->move(0.0f, curr_speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{

			curr_speed += acceleration;
			if (curr_speed > this->speed)curr_speed = this->speed;


			this->move(-curr_speed, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{

			curr_speed += acceleration;
			if (curr_speed > this->speed)curr_speed = this->speed;


			this->move(curr_speed, 0.0f);
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			curr_speed =0;
		}




	}


	//do ulepszania

	void increase_max_hp(int value)
	{
		this->hp += value;
	}

	void increase_max_energy(int value)
	{
		this->energy += value;
	}

	void increase_hp_regen(int value)
	{
		this->hp_reg += value;
	}
	
	void increase_energy_regen(int value)
	{
		this->energy_reg += value;
	}


};


class Enemy_Bullet :public GameObject
{
private:

public:

	Enemy_Bullet(sf::Texture &texture, sf::Vector2f position, float collider_radius) :GameObject(texture, position, collider_radius)
	{
	}

	bool collision_with_player(Player &player,int damage)
	{
		if (this->collider.getGlobalBounds().intersects(player.getCollider().getGlobalBounds()) &&this->exists)
		{
			player.get_damage(damage);
			this->exists = false;
			return true;
		}
		else
			return false;
	}

	void shoot(sf::Vector2f starting_pos, float angle,float speed)
	{
		if (exists == false)
		{
			this->setPosition(starting_pos);
			this->setRotation(angle);
		}
		this->exists = true;



	}


	void draw(sf::RenderWindow &window)
	{
		if (exists)
		{
			window.draw(this->getSprite());
		}
	}

	void move(float speed,sf::RenderWindow &window)
	{
		this->sprite.move(speed*cos((this->getRotation()-90)*M_PI/180), speed*sin((this->getRotation() - 90)*M_PI / 180));
		this->collider.move(speed*cos((this->getRotation() - 90)*M_PI / 180), speed*sin((this->getRotation() - 90)*M_PI / 180));

		if (this->getPosition().x > window.getSize().x + 25 || this->getPosition().x<-25 || this->getPosition().y>window.getSize().y + 25 || this->getPosition().y < -25)
		{
			exists = false;
		}
	}

	

};

enum class enemy_type{Shooting_enemy,Suicide_enemy,Big_enemy};



class Enemy : public GameObject
{
private:
	int hp;
	int damage;


	
	Timer timer1;
	std::vector<Enemy_Bullet> bullets;
	int max_bullets;
	int curr_bullet = 0;

	int money_received;
	int points_received;


public:
	bool died = false;
	bool too_close = false;
	enemy_type type;

	Enemy(sf::Texture &texture, sf::Vector2f position, float radius, int hp, int damage,int max_bullets,Enemy_Bullet bullet,int money_received, int points_received, enemy_type type)
		: GameObject(texture, position, radius), hp(hp), damage(damage),max_bullets(max_bullets),money_received(money_received),points_received(points_received),type(type)
	{
		for (int i = 0; i < max_bullets; i++)
			bullets.push_back(bullet);
	}

	~Enemy()
	{}

	bool check_collision(Player &player)
	{
		if (this->collider.getGlobalBounds().intersects(player.getCollider().getGlobalBounds()) && this->exists&&player.exists)
			return true;
		else return false;
	}
	int return_damage()
	{
		return this->damage;
	}

	int return_hp()
	{
		return this->hp;
	}

	void set_damage(int value)
	{
		this->damage = value;
	}

	void set_hp(int value)
	{
		this->hp = value;
	}

	int return_money_received()
	{
		return this->money_received;
	}

	void set_money_received(int value)
	{
		this->money_received = value;
	}

	void get_damage(int value,Points &points)
	{
		this->hp -= value;
		if (this->hp <= 0)
		{
			exists = false;
			died = true;
			points.increment_killed_enemies();
			points.increase_cash(money_received);
			points.increase_points(points_received);
		}
	}


	void move_around(float x_speed, float y_speed, Player &player)
	{
		float angleX = cos(atan2f(this->getPosition().x - player.getPosition().x, this->getPosition().y - player.getPosition().y));
		float angleY = sin(atan2f(this->getPosition().x - player.getPosition().x, this->getPosition().y - player.getPosition().y));


		this->move(-x_speed * angleX, y_speed * angleY);


	}

	void move_to_player(float x_speed, float y_speed, Player &player)
	{

		this->move(x_speed*(player.getPosition().x - this->getPosition().x)*0.002, y_speed*(player.getPosition().y - this->getPosition().y)*0.002);

	}





	void shoot(int delay,Player &player,float distance_to_shoot)
	{
		sf::Vector2f distance = player.getPosition()- this->getPosition();
		float distance_from_player = sqrtf(distance.x*distance.x + distance.y*distance.y);

		if (distance_from_player < distance_to_shoot+200)
		{

			if (timer1.Basic_spawner(delay)&&this->exists)
			{
				bullets[curr_bullet].shoot( this->getPosition(), this->getRotation(), 5);

				curr_bullet++;
				if (curr_bullet == max_bullets)
					curr_bullet = 0;

			}

		}


	}

	void draw_bullets(sf::RenderWindow &window)
	{
		for (int i = 0; i < max_bullets; i++)
		{
			if (bullets[i].exists)
			{
				bullets[i].draw(window);
			}
		}

	}
	void move_bullets(float speed,sf::RenderWindow &window)
	{
		float angle = ((this->getRotation()-90) * M_PI) / 180;

		for (int i = 0; i < max_bullets; i++)
		{
			if (bullets[i].exists)
				bullets[i].move(speed,window);
		}
	}

	void check_bullet_collsion(Player &player, int damage)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].collision_with_player(player,damage);
		}
	}

};




