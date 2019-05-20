#pragma once

class item
{
protected:
	int evasion;
	int health;
	int dmg;
	int type;

public:
	int getEvasion();
	int getHealth();
	int getDmg();
	int getType();

	void setEvasion(int);
	void setHealth(int);
	void setDmg(int);
	void setType(int);
 
};


class poisonousBerries :public item
{

public:
	poisonousBerries();
	~poisonousBerries() {};
};

class bandages :public item
{

public:
	bandages();
	~bandages() {};
};

class longSword :public item
{

public:
	longSword();
	~longSword() {};
};

class shield :public item
{

public:
	shield();
	~shield() {};
};


