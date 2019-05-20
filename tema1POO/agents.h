#pragma once
#include <iostream>
#include "theMap.h"
using namespace std;

class agent
{
	
protected:
	int lin, col;//theMap placement
	int evasion;//0-95 evade rate
	int health;
	int dmg;//attack damage
	char *type;
	bool dead;
	int ID;//unique identification number for each agent

public:
	static int numberOfAgents;//counter of all registered agents either dead/alive
	void move(int, int);
	int getID();
	int getLin();
	int getCol();
	int getEvasion();
	int getHealth();
	int getDmg();
	char* getType();
	bool getDead();
	
	void setStatic(int);
	void setID(int);
	void setLin(int);
	void setCol(int);
	void setEvasion(int);
	void setHealth(int);
	void setDmg(int);
	void setType(char*);
	void setDead(bool);



	friend ostream& operator<< (ostream&, agent);

};

class spy :public agent
{
public:
	spy();
	~spy() {  };
};


class brawler:public agent
{
public:
	brawler();
	~brawler() { };
};

class soldier :public agent
{
public:
	soldier();
	~soldier() { };
};

class mage :public agent
{
public:
	mage();
	~mage() {  };

};

//this agent has a unique mechanic, when it gets in a "fight" with another blob, the bigger(greaterHP) one consumes
//the smaller one and receives 50% of it's damage and health stats and 5 evasion points
class blob :public agent
{
public:
	blob();
	~blob() { };
};