#pragma once
#include <iostream>
#include <map>
#include <time.h>
#include "agents.h"
#include "item.h"
#include "theMap.h"

using namespace std;

class game
{
	int randomKey;//used for generating stating places and the moves of each agent
	theMap battleGround;
	map<int, agent> agentsValues;//where we keep each agent's current stats agentsValues[3] has an agent with its current stats
	map<int, item> itemsValues;//where we keep each item types stats, itemsValues[4] has item number 4's stats (shield)
	int aliveNumberOfAgents;
	int totalNumberOfAgents;

public:

	game() { };
	~game() {};

	friend istream& operator>>(istream&, game &g);

	template<class itemType>
	void deployItems(int itemNumber);

	template<class agentType>
	void deployAgents(int agentNumber);

	int  fight(agent&, agent&);
	void powerUp(item, agent&);
	void printTheMap();
	void buildTheMap(int height,int width);
	void moveAgent(agent&);
	void startRound();
	void startGame();
};

