
#include "item.h"

poisonousBerries::poisonousBerries()
{
	evasion = -15;
	health = -100;
	dmg = -10;
	type = -1;
}

bandages::bandages()
{
	evasion = 0;
	health = +500;
	dmg = 0;
	type = -2;
}

longSword::longSword()
{
	evasion = -20;
	health = 0;
	dmg = +60;
	type = -3;
}

shield::shield()
{
	evasion = +15;
	health = 300;
	dmg = -10;
	type = -4;
}

int item::getDmg() {
	return dmg;
}

int item::getEvasion() {
	return evasion;
}

int item::getHealth() {
	return health;
}

int item::getType() {
	return type;
}

void item::setEvasion(int x)
{
	evasion = x;
}

void item::setHealth(int x)
{
	health = x;
}

void item::setDmg(int x)
{
	dmg = x;
}

void item::setType(int x)
{
	type = x;
}