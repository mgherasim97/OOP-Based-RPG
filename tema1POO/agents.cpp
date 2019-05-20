#include "agents.h"
#pragma warning (disable:4996)
#include< cstring>
int agent::numberOfAgents = 0;

spy::spy()
{
	type = new char[10];
	++numberOfAgents;
	evasion = 55;
	health = 1000;
	dmg = 120;
	dead = 0;
	strcpy(type,"Spy");
	ID = numberOfAgents;
}

brawler::brawler()
{
	type = new char[10];
	++numberOfAgents;
	evasion = 20;
	health = 3200;
	dmg = 46;
	dead = 0;
	strcpy(type, "Brawler");
	ID = numberOfAgents;
}

soldier::soldier()
{
	type = new char[10];
	++numberOfAgents;
	evasion = 35;
	health = 2200;
	dmg = 60;
	dead = 0;
	strcpy(type, "Soldier");
	ID = numberOfAgents;
}

mage::mage()
{
	type = new char[10];
	++numberOfAgents;
	evasion = 20;
	health = 1050;
	dmg = 200;
	dead = 0;
	strcpy(type, "Mage");
	ID = numberOfAgents;
}

blob::blob()
{
	type = new char[10];
	++numberOfAgents;
	evasion = 16;
	health = 2000;
	dmg = 35;
	dead = 0;
	strcpy(type, "Blob");
	ID = numberOfAgents;
}



void agent::setStatic(int x)
{
	numberOfAgents = x;
}

int agent::getID()
{
	return ID;
}
void agent::setID(int x)
{
	ID = x;
}


int agent::getLin()
{
	return lin;
}
void agent::setLin(int x)
{
	lin = x;
}


int agent::getCol()
{
	return col;
}
void agent::setCol(int x)
{
	col = x;
}


int agent::getEvasion()
{
	return evasion;
}
void agent::setEvasion(int x)
{
	evasion = x;
	if (evasion > 95)evasion = 95;
	if (evasion < 0)evasion = 0;
}


int agent::getHealth()
{
	return health;
}
void agent::setHealth(int x)
{
	health = x;
}


int agent::getDmg()
{
	return dmg;
}
void agent::setDmg(int x)
{
	dmg = x;
}


char* agent::getType()
{
	return type;
}

void agent::setType(char* x)
{
	strcpy(type, x);
}


bool agent::getDead()
{
	return dead;
}
void agent::setDead(bool x)
{
	dead = x;
}

ostream& operator<<(ostream& stream, agent x)
{
	cout << "\nAgent number " << x.getID() << " "<<x.getType()<<" type has the following stats:\n";
	cout << "Placement: Line " << x.getLin() << "   Column: " << x.getCol() << endl;
	cout << "Health: " << x.getHealth()<<endl;
	cout << "Evasion: " << x.getEvasion()<<endl;
	cout << "Damage: " << x.getDmg() << endl;

	return stream;
}

