#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <math.h>

#include "GameObjects.h"
#include "Timer.h"






class Enemy_spawner
{
private:
	int number_of_objects;
	int curr_object;


	std::vector<Enemy> objects;
	

	Timer timer;
public:

	Enemy_spawner(Enemy enemy,int number_of_objects):number_of_objects(number_of_objects),curr_object(0)
	{
		srand(time(0));
		for (int i = 0; i < number_of_objects; i++)
		{
			objects.push_back(enemy);
		}

		for (int i = 0; i < number_of_objects; i++)
		{
			objects[i].setPosition(rand() % 1440,0); 
		}

	}




	void draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i].exists)
			{
				objects[i].draw(window);
			}
		}
	}

	bool all_died()
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (!objects[i].died)
				return false;
		}

		return true;

	}


	void spawn(int delay)
	{


		if (curr_object < number_of_objects)
		{
			if (timer.Basic_spawner(delay))
			{
				objects[curr_object].exists = true;

				curr_object++;
			}
		}

	}


	void shoot(sf::RenderWindow &window,int delay_in_miliseconds,Player &player, float distance_to_shoot)
	{

		for (int i = 0; i < this->objects.size(); i++)
		{
			objects[i].shoot(delay_in_miliseconds,player,distance_to_shoot);
		}
	}

	void AI_move_with_surround(float x, float y,Player &player,int distance_to_attack)
	{

		for (int i = 0; i < objects.size();i++)
			if (objects[i].exists)
			{
				//te 3 linijki zeby ustawial sie przodem do gracza ;)
				float radian = atan2(player.getPosition().x-objects[i].getPosition().x, player.getPosition().y - objects[i].getPosition().y);
				float angle = 180 * radian / M_PI;
				objects[i].setRotation(-angle+180);

				sf::Vector2f distance = player.getPosition() - objects[i].getPosition();
				float distance_from_player = sqrtf(distance.x*distance.x + distance.y*distance.y);

			switch(objects[i].type)
				
				if (distance_from_player > distance_to_attack)
				{
					objects[i].too_close = false;
					objects[i].move_to_player(x, y, player);
				}

				else if(distance_from_player<=distance_to_attack&&distance_from_player>200&&objects[i].too_close==false)
				{
					if (i % 2 == 0)
					{
						objects[i].move_around(x, y, player);
					}
				else
					{
						objects[i].move_around(-x, -y, player);
					}
				}

				else
				{
					objects[i].too_close = true;
					objects[i].move_to_player(-x*4, -y*4, player);
				}


			}
	}


	void collision_with_player(Player &player,int damage)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i].check_collision(player)&&timer.Basic_spawner(1000))
			{

				player.get_damage(damage);
			}
		}
	}

	void move_all_bullets(float speed,sf::RenderWindow &window)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i].move_bullets(speed, window);
		}
	}

	void draw_all_bullets(sf::RenderWindow &window)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i].draw_bullets(window);
		}
	}

	int get_number_of_objects()
	{
		return this->number_of_objects;
	}

	std::vector<Enemy>& return_objects()
	{

		return this->objects;
	}

	void change_objects(std::vector<Enemy> new_vector)
	{
		this->curr_object = 0;
		this->objects.clear();
		this->objects.insert(this->objects.end(), new_vector.begin(), new_vector.end());
	}


	
	//powyzsze funkcje upchane w jedna zeby bylo mniej petli for

	void play(Player &player,int distance_to_attack,float speed,float bullet_speed, sf::RenderWindow &window, int delay_in_miliseconds)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			switch (objects[i].type)

			{
			case enemy_type::Shooting_enemy:
			{


					if (objects[i].exists)
					{
						//te 3 linijki zeby ustawial sie przodem do gracza ;)
						float radian = atan2(player.getPosition().x - objects[i].getPosition().x, player.getPosition().y - objects[i].getPosition().y);
						float angle = 180 * radian / M_PI;
						objects[i].setRotation(-angle + 180);

						sf::Vector2f distance = player.getPosition() - objects[i].getPosition();
						float distance_from_player = sqrtf(distance.x*distance.x + distance.y*distance.y);



						if (distance_from_player > distance_to_attack)
						{
							objects[i].too_close = false;
							objects[i].move_to_player(speed, speed, player);
						}

						else if (distance_from_player <= distance_to_attack&&distance_from_player > 200 && objects[i].too_close == false)
						{
							if (i % 2 == 0)
							{
								objects[i].move_around(speed, speed, player);
							}
							else
							{
								objects[i].move_around(-speed, -speed, player);
							}
						}

						else
						{
							objects[i].too_close = true;
							objects[i].move_to_player(-speed * 3, -speed * 3, player);
						}


					}


					objects[i].shoot(delay_in_miliseconds-200, player, distance_to_attack);
					objects[i].move_bullets(bullet_speed, window);
					objects[i].draw_bullets(window);

					if (objects[i].exists)
					{
						objects[i].draw(window);
					}

					if (objects[i].check_collision(player) && timer.Basic_spawner(1000))
					{
						player.get_damage(objects[i].return_damage());
					}

					objects[i].check_bullet_collsion(player, objects[i].return_damage());
				
				}break;

			case enemy_type::Suicide_enemy:
			{
				if (objects[i].exists)
				{
					//te 3 linijki zeby ustawial sie przodem do gracza ;)
					float radian = atan2(player.getPosition().x - objects[i].getPosition().x, player.getPosition().y - objects[i].getPosition().y);
					float angle = 180 * radian / M_PI;
					objects[i].setRotation(-angle + 180);

					sf::Vector2f distance = player.getPosition() - objects[i].getPosition();
					float distance_from_player = sqrtf(distance.x*distance.x + distance.y*distance.y);



					if (distance_from_player > distance_to_attack)
					{
						objects[i].move_to_player(speed, speed, player);
					}

					else if (distance_from_player <= distance_to_attack)
					{
						objects[i].move_to_player(10*speed, 10*speed, player);
					}




					if (objects[i].exists)
					{
						objects[i].draw(window);
					}

					if (objects[i].check_collision(player))
					{
						objects[i].exists = false;
						objects[i].died = true;
						player.get_damage(objects[i].return_damage());
					}

					objects[i].check_bullet_collsion(player, objects[i].return_damage());

				}break;


			case enemy_type::Big_enemy:
			{
				if (objects[i].exists)
				{
					//te 3 linijki zeby ustawial sie przodem do gracza ;)
					float radian = atan2(player.getPosition().x - objects[i].getPosition().x, player.getPosition().y - objects[i].getPosition().y);
					float angle = 180 * radian / M_PI;
					objects[i].setRotation(-angle + 180);

					sf::Vector2f distance = player.getPosition() - objects[i].getPosition();
					float distance_from_player = sqrtf(distance.x*distance.x + distance.y*distance.y);



					if (distance_from_player > distance_to_attack)
					{
						objects[i].too_close = false;
						objects[i].move_to_player(speed*0.5, speed*0.5, player);
					}

					else if (distance_from_player <= distance_to_attack&&distance_from_player > 200 && objects[i].too_close == false)
					{
						if (i % 2 == 0)
						{
							objects[i].move_around(speed*0.5, speed*0.5, player);
						}
						else
						{
							objects[i].move_around(-speed, -speed, player);
						}
					}

					else
					{
						objects[i].too_close = true;
						objects[i].move_to_player(-speed * 2, -speed * 2, player);
					}


				}


				objects[i].shoot(delay_in_miliseconds, player, distance_to_attack+300);
				objects[i].move_bullets(bullet_speed, window);
				objects[i].draw_bullets(window);

				if (objects[i].exists)
				{
					objects[i].draw(window);
				}

				if (objects[i].check_collision(player) && timer.Basic_spawner(1000))
				{
					player.get_damage(objects[i].return_damage());
				}

				objects[i].check_bullet_collsion(player,objects[i].return_damage());

			}break;



			}

			}

		}

	}



	~Enemy_spawner()
	{
		objects.clear();
	}







};




enum class type_of_supply{hp,energy,cash};


class Supplies : public GameObject
{
private:
	int points_received;
	int power;
	type_of_supply type;

public:
	Supplies(sf::Texture &texture,sf::Vector2f position,float collider_radius,int power,int points_received,type_of_supply type):GameObject(texture,position,collider_radius),power(power), points_received(points_received),type(type)
	{

	}



	void check_collision(Player &player,Points &points)
	{
		if (player.getCollider().getGlobalBounds().intersects(this->getCollider().getGlobalBounds())&&this->exists)
		{
			this->exists = false;
			
			switch (type)
			{
			case type_of_supply::hp:
			{
				player.heal_up(power);
				points.increase_points(points_received);
			}break;
			case type_of_supply::energy:
			{
				player.energy_up(power);
				points.increase_points(points_received);
			}break;

			case type_of_supply::cash:
			{
				points.increase_cash(power);
				points.increase_points(points_received);
			}break;
			}


		}
	}

	void set_rand_position_and_spawn(sf::RenderWindow &window)
	{
		srand(time(0));
		int x_pos = (rand() % 10+2)*100;
		int y_pos = (rand() % 6+2)*100;
		if (!exists)
		{
			this->setPosition(x_pos,y_pos);
			this->collider.setPosition(x_pos, y_pos);
			this->exists = true;
		}
	}

	int get_power()
	{
		return this->power;
	}

	void set_power(int value)
	{
		this->power = value;
	}
	
	


};


class Supplies_spawner
{
private:
	Timer t1;
	std::vector<Supplies> supplies_vector;
	float spawn_chance;
public:

	Supplies_spawner(Supplies s1, Supplies s2, Supplies s3, float spawn_chance):spawn_chance(spawn_chance)
	{
		for (int i = 0; i < 4;i++)
		{
			supplies_vector.push_back(s1);
		}

		for (int i = 0; i < 4; i++)
		{
			supplies_vector.push_back(s2);
		}

		for (int i = 0; i < 4; i++)
		{
			supplies_vector.push_back(s3);
		}
	}
	


	void spawn_rand_supply(sf::RenderWindow &window)
	{
			srand(time(0));
			supplies_vector[rand() % supplies_vector.size()].set_rand_position_and_spawn(window);

	}

	void draw_and_check_collision(sf::RenderWindow &window,Player &player,Points &points)
	{

		for (int i = 0; i < supplies_vector.size();i++)
		{
			supplies_vector[i].draw(window);
			supplies_vector[i].check_collision(player, points);
		}

	}


	void increase_power(int multiply)
	{
		for (int i = 0; i < supplies_vector.size(); i++)
		{
			supplies_vector[i].set_power(supplies_vector[i].get_power()*multiply);
		}
	}


};
