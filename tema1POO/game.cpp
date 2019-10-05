#include "game.h"

template<class itemType>
void game::deployItems(int itemNumber)
{//all items are the same, thier stats can't change so we only need *typesOfItems* entries
	itemType t;
	itemsValues[-t.getType()] = t;

	for (int i = 0; i < itemNumber; ++i)
	{
		int col = rand() % battleGround.getWidth(),  lin=rand()%battleGround.getHeight();

		while ( battleGround.getValue(lin,col) !=0  )
		{
			 lin = rand() % battleGround.getHeight();
			 col = rand() % battleGround.getWidth();
	    }
       
		battleGround.setThing(lin, col, t.getType());

	}
	
}


template<class agentType>
void game::deployAgents(int agentNumber)
{
	
	for (int i = 0; i < agentNumber; ++i)
	{
		int col = rand() % battleGround.getWidth(), lin = rand() % battleGround.getHeight();

		while (battleGround.getValue(lin, col) != 0)
		{
			lin = rand() % battleGround.getHeight();
			col = rand() % battleGround.getWidth();
		}

		//we need an entry for each agent since they all will be different in the end
		agentType t;
		t.setLin(lin);
		t.setCol(col);
		agentsValues[t.getID()] = t;
		battleGround.setThing(lin, col, t.getID());

	}

	
}



istream& operator>>(istream& input, game& g)
{
	g.aliveNumberOfAgents = 0;
	cout << "Legend of commands:\n";
	cout << "1)Type an integer to specify how many rounds you want to be played now.\n";
	cout << "2)Type END to specify that you want the game to end now, without a decided winner.\n";
	cout << "3)Type WINNER if you want to go straight to the winner.\n";
	cout << "After each integer introduced you will be produced with the map and battle/findings log.\n";
	cout << "\n\n MAP LEGEND OF SYMBOLS:\n";
	cout << "A-poisonous Berries;\n";
	cout << "B-bandages;\n";
	cout << "C-longswords;\n";
	cout << "D-shields;\n";
	cout << "0-empty spot;\n";
	cout << "Any positive integer = unique ID of an agent;\n";
	cout << "All characters can move 1 box in any direction, including diagonally.\n";
	cout << "Last one standing gets your woman\n";

	mage m;
	cout << "\nMage class has HUGE damage but very low survivability:" << m << "\n";
	spy s;
	cout << "Spy class has good damage and very good evasion skills but low health:" << s << "\n";
	brawler b;
	cout << "Brawler class has sub-mediocre evasion and low damage but a huge health pool:" << b << "\n";
	soldier so;
	cout << "Soldier class has mediocre all over the board stats, good all-rounder:" << so << "\n";
	blob bl;
	cout << "Blob class has low stats all over the board but has the advantage of merging while fighting. The bigger blob gets 50% of the smaller blob's health and dmg and 25% of its evasion. Careful or he'll snowball the lategame:" << bl << "\n";
	m.setStatic(0);

	cout << endl;
	cout << "HAVE FUN ^^\n\n\n";



	cout << "Introduce the Random key used to uniquify the game: "; 
	cin >> g.randomKey;
	srand(g.randomKey);//initialize rand using the user's key

	cout << "\nIntroduce the Height, respectively the Width of the map: ";
	int height, width,nr;
	cin >> height >> width;
	g.buildTheMap(height, width);


	cout << "\nIntroduce the number of poisonousBerries, bandages, longSwords and shields in that order: ";
	//initialize itemsValues and deploy items on map
	cin >> nr;
	g.deployItems<poisonousBerries>(nr); 
	cin >> nr;
	g.deployItems<bandages>(nr);
	cin >> nr;
	g.deployItems<longSword>(nr);
	cin >> nr;
	g.deployItems<shield>(nr);

	

	cout << "\nIntroduce the number of spies, brawlers, soldiers, mages and blobs in that order: ";
	//initialize agentsValues and deploy agents on map
	cin >> nr; g.aliveNumberOfAgents += nr;
	g.deployAgents<spy>(nr);
	cin >> nr; g.aliveNumberOfAgents += nr;
	g.deployAgents<brawler>(nr);
	cin >> nr; g.aliveNumberOfAgents += nr;
	g.deployAgents<soldier>(nr);
	cin >> nr; g.aliveNumberOfAgents += nr;
	g.deployAgents<mage>(nr);
	cin >> nr; g.aliveNumberOfAgents += nr;
	g.deployAgents<blob>(nr);
	g.totalNumberOfAgents = g.aliveNumberOfAgents;

	cout << "A-poisonous Berries\n";
	cout << "B-bandages\n";
	cout << "C-longswords\n";
	cout << "D-shield\n";
	cout << endl;


	return input;

}

void game::powerUp(item it, agent& ag)
{
	ag.setDmg(ag.getDmg() + it.getDmg());
	ag.setEvasion(ag.getEvasion() + it.getEvasion());
	ag.setHealth(ag.getHealth() + it.getHealth());
	
	if (ag.getDmg() < 0) ag.setDmg(0);
	if (ag.getEvasion() < 0) ag.setEvasion(0);
	if (ag.getEvasion() > 95) ag.setEvasion(95);
	if (ag.getHealth() < 0) ag.setHealth(0), ag.setDead(1);
	cout << "The agent " << ag.getID() <<" "<<ag.getType()<<" type obtained: ";
	if (it.getType() == -1)cout << "poisonous Berries.";
	else if (it.getType() == -2)cout << "bandages.";
	else if (it.getType() == -3)cout << "longsword.";
	else if (it.getType() == -4)cout << "shield.";

	cout << ag << endl;
	
	
}

//0    draw
//-1   x wins
//1    y wins
int game::fight(agent& x, agent& y)
{
	if (strcmp(x.getType(), y.getType()) == 0 && strcmp(x.getType(), "Blob") == 0)

		if (x.getHealth() > y.getHealth())
		{

			x.setHealth(x.getHealth() + y.getHealth() / 2);
			x.setDmg(x.getDmg() + y.getDmg() / 2);
			x.setEvasion(x.getEvasion()+y.getEvasion()/4);
			y.setDead(1);
			cout << "Blobul " << x.getID() << " a fuzionat cu blobul " << y.getID() << "\nBacteria!\nDe la una ne inmultim,\nBacteria!\nSi-apoi doua devenim \nBacteria!\nInca doua cate doua\nBacteria!\nPan' la nouazeci si noua\nBacteria!\nN-avem timp de asteptat!\nBacteria!\nNe-nmultim neincetat\nBacteria!\nPlanul vom dezvalui\nBacteria!\nLumea o vom cuceri!!!!!";
			cout << x<<endl;
			--aliveNumberOfAgents;
			return -1;

		}

		else
		{
			y.setHealth(y.getHealth() + x.getHealth() / 2);
			y.setDmg(y.getDmg() + x.getDmg() / 2);
			y.setEvasion(y.getEvasion() + 5);
			x.setDead(1);
			cout << "Blobul " << x.getID() << " a fuzionat cu blobul " << y.getID() << "\nBacteria!\nDe la una ne inmultim,\nBacteria!\nSi-apoi doua devenim \nBacteria!\nInca doua cate doua\nBacteria!\nPan' la nouazeci si noua\nBacteria!\nN-avem timp de asteptat!\nBacteria!\nNe-nmultim neincetat\nBacteria!\nPlanul vom dezvalui\nBacteria!\nLumea o vom cuceri!!!!!";
			cout << y<<endl;
			--aliveNumberOfAgents;
			return 1;
		}

	



	int hit1, hit2;
	while (x.getDead() == 0 && y.getDead() == 0)
	{
		hit1 = rand() % 101;
		hit2 = rand() % 101;

		if (hit1 > x.getEvasion())
		{
			x.setHealth(x.getHealth() - y.getDmg());
			if (x.getHealth() <= 0)
				x.setDead(1);
		}

		if (hit2 > y.getEvasion())
		{
			y.setHealth(y.getHealth() - x.getDmg());
			if (y.getHealth() <= 0)
				y.setDead(1);
		}

	}

	if (x.getDead() && y.getDead())
	{
		cout << "Agent number " << x.getID() << " type " << x.getType() << " stupidly died together with agent " << y.getID() << " type " << y.getType() << endl<<endl;
		aliveNumberOfAgents -= 2;

		return 0;
	}

	else if (y.getDead())
	{
		cout << "Agent number " << x.getID() << " type " << x.getType() << " has killed agent number " << y.getID() << " type " << y.getType()<<x<<endl;
		--aliveNumberOfAgents;
		return -1;
	}

	else if (x.getDead())
	{
		cout << "Agent number " << y.getID() << " type " << y.getType() << " has killed agent number" << x.getID() << " type " << x.getType()<<y<<endl;
		--aliveNumberOfAgents;
		return 1;
	}

}

void game::moveAgent(agent& x)
{
	pair<int, int>v[8] = { make_pair(-1, -1),make_pair(-1, 0),make_pair(-1, 1),make_pair(0, -1),make_pair(0, 1),make_pair(1, -1),make_pair(1, 0),make_pair(1, 1) };

	int lin, col, ct;

	do {
		ct = rand() % 8;
		lin = x.getLin() + v[ct].first;
		col = x.getCol() + v[ct].second;

	} while ((lin >= 0 && lin < battleGround.getHeight() && col >= 0 && col < battleGround.getWidth()) == 0);

	/*  for a deterministical aproach, the players move to the center of the map instead of randomly moving around it
	the code above shall be erased and the code in this comment shall replace it
	int lin, col;
	lin = x.getLin();
	col = x.getCol();
	if (lin < battleGround.getHeight() / 2)++lin;
	else if (lin > battleGround.getHeight() / 2)--lin;

	if (col < battleGround.getWidth() / 2)++col;
	else if (col > battleGround.getWidth() / 2)--col;
	*/

	if (lin == x.getLin() && col == x.getCol())return;//an agent that arrived at the map center can't fight with himself... that'd be dumb


	if (battleGround.getValue(lin, col) <= -1)
	{
		powerUp(itemsValues[-battleGround.getValue(lin, col)], x);
		battleGround.setThing(x.getLin(), x.getCol(), 0);
		battleGround.setThing(lin, col, x.getID());
		x.setCol(col);
		x.setLin(lin);
		
	}

	else if (battleGround.getValue(lin, col) > 0)
	    { 

		int result = fight(  x,  agentsValues[battleGround.getValue(lin, col)]   );

		if (result == 0)
		{
			battleGround.setThing(x.getLin(), x.getCol(), 0);
			x.setDead(1);
			agentsValues[battleGround.getValue(lin, col)].setDead(1);
			battleGround.setThing(lin, col, 0);
		}

		if (result == 1)
		{
			battleGround.setThing(x.getLin(), x.getCol(), 0);
			x.setDead(1);
		}
		if (result == -1)
		{
			agentsValues[battleGround.getValue(lin, col)].setDead(1);
			battleGround.setThing(x.getLin(), x.getCol(), 0);
			battleGround.setThing(lin, col, x.getID());
			x.setLin(lin);
			x.setCol(col);

		}
		

	    }

	else
	{
		battleGround.setThing(x.getLin(), x.getCol(), 0);
		battleGround.setThing(lin, col, x.getID());
		x.setCol(col);
		x.setLin(lin);
	}

}



void game::startRound()
{
	
		for (int i=1; i<=totalNumberOfAgents; ++i)
			if (agentsValues[i].getDead() == 0)
				moveAgent(agentsValues[i]);


}

void game::startGame()
{
	bool gameON = 1;

	char* line;
	line = new char[100];
	while (gameON)
	{   
		cout << "ENTER YOUR COMMAND, DUNGEON MASTER!:";
		cin.getline(line, 99);
		if (strstr(line, "END"))
		{
			cout << "\nYou ended the game before its time... such a pity.\n\n";
			gameON = 0;
			break;
		}
		if (strstr(line, "WINNER"))
		{
			while (aliveNumberOfAgents>1)
				startRound();

			cout << endl;
			battleGround.printTheMap();
			cout << endl;
			for (auto i : agentsValues)
				if (i.second.getDead() == 0)
					cout << "Aaaaand the WINNER is agent number " << i.second.getID() << " " << i.second.getType() << "Class.\n\n";

			gameON = 0;
     		break;
		}

		int number=0;
		for (int i = 0; line[i]; ++i)
		  
			if (line[i] >= '0' && line[i] <= '9')
			{
				number = number * 10;
				number += line[i] - '0';
			}

		while (number)
		{
			startRound();
			if (aliveNumberOfAgents <= 1)break;
			--number;

		}

		cout << endl;
		battleGround.printTheMap();
		cout << endl; 
		cout << "At the moment there are: " << aliveNumberOfAgents << " alive agents in the map's wilderness\n\n";

		if (aliveNumberOfAgents == 1)
			for (auto i : agentsValues)
				if (i.second.getDead() == 0)
					cout << "Aaaaand the WINNER is agent number " << i.second.getID() << " " << i.second.getType() << "Class.\n\n"<<i.second;

		if (aliveNumberOfAgents == 0)
					cout << "They are all dead... guess i'll die too X0\n\n\n";

		if (aliveNumberOfAgents <= 1)gameON = 0;
	}

}

void game::printTheMap() {
	battleGround.printTheMap();
}

void game::buildTheMap(int height, int width) {
	battleGround.buildTheMap(height,width);
}