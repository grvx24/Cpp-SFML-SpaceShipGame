#pragma once



class Points
{
private:
	int killed_enemies;
	int cash;
	int points;



public:
	
	bool enemies_ready_for_boost = false;

	Points() :killed_enemies(0), cash(0),points(0)
	{

	}

	void set_enemies_ready_for_boost(int x)
	{
		if (this->killed_enemies % x ==0&&killed_enemies>0 )
		{

			enemies_ready_for_boost = true;
		}
	}

	void reset_points()
	{
		killed_enemies = 0;
		cash = 0;
		points = 0;
	}

	void increase_cash(int value)
	{
		this->cash += value;
	}

	void increase_points(int value)
	{
		this->points += value;
	}

	void increment_killed_enemies()
	{
		killed_enemies++;
	}

	int get_killed_enemies()
	{
		return this->killed_enemies;
	}


	int get_cash()
	{
		return this->cash;
	}

	int get_points()
	{
		return this->points;
	}

	void consume_cash(int value)
	{
		if (cash >= value);
		this->cash -= value;
	}
};