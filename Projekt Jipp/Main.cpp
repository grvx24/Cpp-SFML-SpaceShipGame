#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


#include "GameObjects.h"
#include "Weapons.h"
#include "Timer.h"
#include "Spawner.h"
#include "Interface.h"
#include "Points.h"
#include "Upgrades.h"
#include "Random_waves.h"



int main()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//rozmiary okna
	const int ScreenHeight = 900;
	const int ScreenWidth = 1440;

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//okno
	sf::RenderWindow MainWindow(sf::VideoMode(ScreenWidth, ScreenHeight), "Game");
	MainWindow.setVerticalSyncEnabled(true);
	MainWindow.setFramerateLimit(60);
	MainWindow.setKeyRepeatEnabled(false);
	sf::Event event;

	

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//Tlo
	sf::Texture menu_theme_texture;
	menu_theme_texture.loadFromFile("textures/space-wallpaper.png");
	sf::Sprite menu_theme(menu_theme_texture);

	sf::Texture theme_texture;
	theme_texture.loadFromFile("textures/Theme.png");
	sf::Sprite theme_sprite(theme_texture);

	sf::Texture workshop_texture;
	workshop_texture.loadFromFile("textures/spaceship.png");
	sf::Sprite workshop_sprite(workshop_texture);



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//player
	sf::Texture stateczek;
	stateczek.loadFromFile("textures/fighter-01.png");
	Player player0(stateczek, sf::Vector2f(ScreenWidth / 2, ScreenHeight / 2), 50, 100, 100, 6, 0.5);
	Player player1 = player0;
	player1.exists = false;


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//audio


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//bron
	sf::Texture pocisk_tekstura;
	pocisk_tekstura.loadFromFile("textures/Red_laser.png");
	Bullet bullet1(pocisk_tekstura, player1.getPosition(),5, 50);//parametry
	bullet1.set_forward_deviation(50);
	Weapon wep1(bullet1, 100, 15, 3);//rodzaj broni, 2 argument oznacza ile max strzalow moze byc na ekranie, 3 argument to speed
	Weapon weapon1 = wep1;
	//ostatni argument-firerate "1" oznacza 1 strzal na sekunde itd

	sf::Texture pocisk_tekstura2;
	pocisk_tekstura2.loadFromFile("textures/energy_ball.png");
	Bullet bullet2(pocisk_tekstura2, player1.getPosition(), 60, 100);//parametry
	bullet2.set_forward_deviation(50);
	Weapon wep2(bullet2, 30, 15, 1);
	Weapon weapon2 = wep2;

	sf::Texture pocisk_tekstura3;
	pocisk_tekstura3.loadFromFile("textures/Long_laser.png");
	Bullet bullet3(pocisk_tekstura3, player1.getPosition(),30,100);
	bullet3.set_forward_deviation(100);
	Weapon wep3(bullet3, 20, 50, 5);
	Weapon weapon3 = wep3;


	//pociski enemy
	sf::Texture e_bullet_texture;
	e_bullet_texture.loadFromFile("textures/Rocket.png");
	Enemy_Bullet e_bullet1(e_bullet_texture,sf::Vector2f(0,0), 5);


	sf::Texture e_big_bullet_texture;
	e_big_bullet_texture.loadFromFile("textures/dark_beam.png");
	Enemy_Bullet e_big_bullet1(e_big_bullet_texture, sf::Vector2f(0, 0), 50);


	//interfejs
	sf::Font font1;
	font1.loadFromFile("fonts/optimus/Optimus Bold.otf");

	Interface player_interface(font1);


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//Przeciwnik
	sf::Texture Basic_enemy_texture;
	Basic_enemy_texture.loadFromFile("textures/Basic_enemy.png");
	Enemy Basic_enemy(Basic_enemy_texture, sf::Vector2f(600,-100),40, 100, 10,5,e_bullet1,20,100,enemy_type::Shooting_enemy);
	Basic_enemy.setRotation(180);


	sf::Texture Suicide_en_texture;
	Suicide_en_texture.loadFromFile("textures/suicide0.png");
	Enemy Suicide_enemy(Suicide_en_texture, sf::Vector2f(600, -100), 40, 30, 10, 1, e_bullet1, 10, 100, enemy_type::Suicide_enemy);
	Suicide_enemy.setRotation(180);

	sf::Texture Big_enemy_texture;
	Big_enemy_texture.loadFromFile("textures/dark_ship.png");
	Enemy Big_enemy(Big_enemy_texture, sf::Vector2f(0, 0), 70, 200, 50, 10, e_big_bullet1, 30, 200, enemy_type::Big_enemy);


	//punkty
	Points points;
	
	//ulepszenia
	Upgrades upgrades0;
	Upgrades upgrades;


	//dopalacze ;)
	sf::Texture hp_sign;
	hp_sign.loadFromFile("textures/red_plus.png");
	Supplies s1_hp(hp_sign, sf::Vector2f(0, 0), 10,10000, 100, type_of_supply::hp);

	sf::Texture energy_sign;
	energy_sign.loadFromFile("textures/energy_sign.png");
	Supplies s2_energy(energy_sign, sf::Vector2f(0, 0), 10,10000, 100, type_of_supply::energy);

	sf::Texture cash_sign;
	cash_sign.loadFromFile("textures/dollar.png");
	Supplies s3_cash(cash_sign, sf::Vector2f(0, 0), 10,100, 100, type_of_supply::cash);

	Supplies_spawner s_spawner0(s1_hp, s2_energy, s3_cash, 20);
	Supplies_spawner s_spawner1 = s_spawner0;


	//spawner
	Enemy_spawner spawner1(Big_enemy, 100); //wzorcowy nie do uzywania


	//fale
	Random_wave r1;
	r1.generate_random_spawner(spawner1, points, Basic_enemy, Suicide_enemy, Big_enemy,s_spawner1);




	//timer
	Timer supporting_timer;
	Timer supply_timer;
	Timer game_over_timer;
	Timer menu_timer;
	Timer wave_pause_t;

	//pomocnicze zmienne
	int last_weapon_used = 0;
	int chance_to_spawn = 20;

	bool menu = true;
	bool workshop = false;

	bool new_game = false;


	sf::Clock clk;


	srand(time(0));
	while (MainWindow.isOpen())
	{

		while (MainWindow.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
			{

				MainWindow.close();
			}

			if (event.type == sf::Event::KeyReleased&&menu==false&& event.key.code == sf::Keyboard::Escape)
			{
				if (!workshop)
					workshop = true;
				else
					workshop = false;
			}



		}


		if (menu==true)
		{
			if (!new_game)
			{

				player_interface.draw_text("Press space to start", MainWindow, 100, 100, 600, sf::Color::White);
				if (points.get_points() > 0)
				{

					player_interface.draw_game_over(MainWindow, points);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					new_game = true;
				}
			}
				if(new_game)
			{


				player1.exists = true;
				player_interface.main_Menu(MainWindow, menu, points, menu_theme);


			}

		}
		else if (workshop == true)
		{

			MainWindow.draw(workshop_sprite);
			upgrades.draw_all(MainWindow,points,player_interface,player1);
			upgrades.upgrade_on_click(MainWindow,player1,weapon1,weapon2,weapon3,points,player_interface);


			
				

		}
		else
		{



			MainWindow.draw(theme_sprite);



			player1.draw(MainWindow);
			player1.Controller(MainWindow);
			player1.hp_regen(2000);
			player1.energy_regen(500);



			//strzelanie
			weapon1.play(MainWindow, spawner1.return_objects(), true,points,100);
			weapon2.play(MainWindow, spawner1.return_objects(), false,points,0);
			weapon3.play(MainWindow, spawner1.return_objects(), false, points,0);


			if (player1.canShoot == false)
			{
				switch (last_weapon_used)
				{
				case 1:
				{
					weapon1.CheckBulletClock(player1);
				}break;
				case 2:
				{
					weapon2.CheckBulletClock(player1);
				}break;

				case 3:
				{
					weapon3.CheckBulletClock(player1);
				}break;

				}
			}



			if (player1.canShoot&&sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				weapon1.shoot(player1);
				last_weapon_used = 1;
			}

			if (player1.canShoot&&sf::Mouse::isButtonPressed(sf::Mouse::Right) && player1.get_Energy() >= 60)
			{
				weapon2.shoot_and_consume_energy(player1, 60);
				last_weapon_used = 2;
			}

			if (player1.canShoot&&sf::Mouse::isButtonPressed(sf::Mouse::Middle) && player1.get_Energy() >= 30)
			{
				weapon3.shoot_and_consume_energy(player1, 30);
				last_weapon_used = 3;
			}



			//spawner
			if (points.get_killed_enemies() > 0 && points.get_killed_enemies() % 20 == 0)
				spawner1.spawn(300);

			if (points.get_points() > 30000)
			{
				spawner1.spawn(200);
			}

			if (points.get_points() > 80000)
			{
				spawner1.spawn(100);
			}

			spawner1.spawn((rand()%30+1)*500);
			spawner1.play(player1, 300, 5,10, MainWindow, 2000);

			if (wave_pause_t.Basic_spawner(5000))
			{
				if (spawner1.all_died())
				{
					r1.generate_random_spawner(spawner1, points, Basic_enemy, Big_enemy, Suicide_enemy, s_spawner1);
				}
			}
			//dopalacze
			if (supply_timer.Basic_spawner(1000)&&rand()%100<chance_to_spawn)
				s_spawner1.spawn_rand_supply(MainWindow);



			s_spawner1.draw_and_check_collision(MainWindow,player1,points);
		

			





			//interfejs
			player_interface.draw_HP(player1, MainWindow);
			player_interface.draw_Energy(player1, MainWindow);
			player_interface.draw_cash(points, MainWindow);
			player_interface.draw_points(points, MainWindow);

		}

		if (player1.game_over())
		{
			menu = true;
			new_game = false;
			r1.generate_random_spawner(spawner1, points, Basic_enemy, Suicide_enemy, Big_enemy, s_spawner1);
			upgrades = upgrades0;
			player1 = player0;
			weapon1 = wep1;
			weapon2 = wep2;
			weapon3 = wep3;
			s_spawner1=s_spawner0;
		}

		MainWindow.display();
		MainWindow.clear();


		//co x killi ulepsza przeciwnikow
		points.set_enemies_ready_for_boost(200);

	}









	//do zrobienia

	//losowy spawn



	return 0;
}

