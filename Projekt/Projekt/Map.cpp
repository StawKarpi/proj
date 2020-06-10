#include "Map.h"

Map::Map(const int, const int)
{

}

void Map::setsoldiers()
{
	UnitFactory* factory;
	factory = new SoldierFactory;
	int n;
	cout << "Set number of soldiers: " << endl;
	cin >> n;
	factory->makeFirst_type((n / 2), soldiers);
	factory->makeSecond_type((ceil((double)n / 2)), soldiers);
}

void Map::setmonsters()
{
	UnitFactory* factory;
	factory = new MonsterFactory;
	int n;
	cout << "Set number of monsters: " << endl;
	cin >> n;
	factory->makeFirst_type((n / 2), monsters);
	factory->makeSecond_type((ceil((double)n / 2)), monsters);
}

void Map::place(int x, int y, int xpos, int ypos)
{
	for (int i = 0;i < y;i++)
	{
		for (int j = 0;j < x;j++)
		{
			map[i][j] = '-';
			cout << map[i][j];
		}
		cout << endl;
	}
	for (unsigned int i = 0; i < soldiers.size(); i++)
	{
		soldiers[i]->setFirstX(x);
		//cout << "soldier x: " << soldiers[i].getxpos() + 1 << endl;
		soldiers[i]->setFirstY(y);
		//cout << "soldier y: " << y - soldiers[i].getypos() << endl;	
		map[soldiers[i]->getYpos()][soldiers[i]->getXpos()] = soldiers[i]->getPoint();
	}
	for (int i = 0; i < monsters.size(); i++)
	{
		monsters[i]->setFirstX(x);
		//cout << "monster x: " << monsters[i].getxpos() + 1 << endl;
		monsters[i]->setFirstY(y);
		//cout << "monster y: " << y - monsters[i].getypos() << endl;
		for (int j = 0;j < soldiers.size();j++)
		{
			if ((monsters[i]->getXpos() == soldiers[j]->getXpos()) && (monsters[i]->getYpos() == soldiers[j]->getYpos()))
			{
				monsters[i]->setFirstX(x);
				monsters[i]->setFirstX(y);
			}
		}
		map[monsters[i]->getYpos()][monsters[i]->getXpos()] = monsters[i]->getPoint();

	}
}
		
void Map::draw()
	{
	
	for (int i = 0;i < y;i++)
	{
		for (int j = 0;j < x;j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

void Map::moveunits(int x, int y, int xpos, int ypos)
{
	for (int i = 0;i < soldiers.size();i++)
	{
		int dist=100, idmonster;
		for (int j = 0;j < monsters.size();j++)
		{
			int dist_temp = sqrt(pow((soldiers[i]->getXpos() - monsters[j]->getXpos()), 2) + pow((soldiers[i]->getYpos() - monsters[j]->getYpos()), 2));
			if (dist_temp < dist)
			{
				dist = dist_temp;
				idmonster = j;
			}
			
		}
		if ((dist == 1) && (soldiers[i]->getXpos() == monsters[idmonster]->getXpos() || soldiers[i]->getYpos() == monsters[i]->getYpos()))
		{
			soldiers[i]->attack(monsters[idmonster]);
			cout << monsters[idmonster]->getPoint() << ": " << monsters[idmonster]->getHealth() << endl;
		}
		else
		{
			map[soldiers[i]->getYpos()][soldiers[i]->getXpos()] = '-';

			if (soldiers[i]->getXpos() < monsters[idmonster]->getXpos()) soldiers[i]->setXpos(soldiers[i]->getXpos() + 1);
			else if (soldiers[i]->getXpos() > monsters[idmonster]->getXpos()) soldiers[i]->setXpos(soldiers[i]->getXpos() - 1);
			else if (soldiers[i]->getYpos() < monsters[idmonster]->getYpos()) soldiers[i]->setYpos(soldiers[i]->getYpos() + 1);
			else  soldiers[i]->setYpos(soldiers[i]->getYpos() - 1);

			map[soldiers[i]->getYpos()][soldiers[i]->getXpos()] = soldiers[i]->getPoint();
		}
	}
	for (int i = 0;i < monsters.size();i++)
	{
		int distm = 100, idsoldier=0;
		for (int j = 0;j < soldiers.size();j++)
		{
			int distm_temp = sqrt(pow((monsters[i]->getXpos() - soldiers[j]->getXpos()), 2) + pow((monsters[i]->getYpos() - soldiers[j]->getYpos()), 2));
			if (distm_temp < distm)
			{
				distm = distm_temp;
				idsoldier = j;
			}

		}
		if ((distm == 1) && (monsters[i]->getXpos() == soldiers[idsoldier]->getXpos() || monsters[i]->getYpos() == soldiers[i]->getYpos()))
		{
			monsters[i]->attack(soldiers[idsoldier]);
		}
		else
		{
			map[monsters[i]->getYpos()][monsters[i]->getXpos()] = '-';

			if (monsters[i]->getXpos() < soldiers[idsoldier]->getXpos()) monsters[i]->setXpos(monsters[i]->getXpos() + 1);
			else if (monsters[i]->getXpos() > soldiers[idsoldier]->getXpos()) monsters[i]->setXpos(monsters[i]->getXpos() - 1);
			else if (monsters[i]->getYpos() < soldiers[idsoldier]->getYpos()) monsters[i]->setYpos(monsters[i]->getYpos() + 1);
			else  monsters[i]->setYpos(monsters[i]->getYpos() - 1);

			map[monsters[i]->getYpos()][monsters[i]->getXpos()] = monsters[i]->getPoint();
		}
	}
	Sleep(500);
	system("cls");
	Map::draw();
	}