#include <iostream>
#include <string>

class Warrior
{
	int life;
	std::string names;
	Warrior(int lifes, std::string name);
	Warrior(const Warrior &A);
public:
	friend class Command;
};
class Command
{
private:
	int numberWarrior[5];                              //numberDragon,numberNinja,numberIceman,numberLion,numberWolf;
	std::string headName;                              //the command's name
	int *switchWarrior;                                //now using warrior
	int *order;                                        //next warrior
	int warriorNumber;                                 //how warrior is born
	bool stoped;                                       //is born stoped?
	int life;                                          //command's life, if life is 0.return stoped true.

	Warrior dragon, ninja, iceman, lion, wolf;             //all warrior's 
	Warrior *warri[5];                                 //the points to all warrior.
	void bornjudge(int i, int time);

public:
	int nexti;                                           // the next warrior is ?
	Command(std::string headName, int life, int lifeDragon, int lifeNinjia, int lifeIceman, int lifeLion, int lifeWolf);
	int bornwarrior(int i, int time);                     //use bornjudge  and return is stoped.
};
Warrior::Warrior(int lifes, std::string name) :life(lifes), names(name)
{
}
Warrior::Warrior(const Warrior &A) : life(A.life)
{
}
Command::Command(std::string headName_, int life_, int lifeDragon, int lifeNinjia, int lifeIceman, int lifeLion, int lifeWolf) :
headName(headName_), life(life_), dragon(lifeDragon, "dragon"), ninja(lifeNinjia, "ninja"),
iceman(lifeIceman, "iceman"), lion(lifeLion, "lion"), wolf(lifeWolf, "wolf"), numberWarrior()
{
	warri[0] = &dragon;
	warri[1] = &ninja;
	warri[2] = &iceman;
	warri[3] = &lion;
	warri[4] = &wolf;
	warriorNumber = 0;
	stoped = false;
	nexti = 0;

}
void Command::bornjudge(int i, int time)
{
	int s1[] = { 2, 3, 4, 1, 0 };
	int s2[] = { 3, 0, 1, 2, 4 };
	int searchTimes = 0;
	if (headName == "red")
	{
		order = s1;
	}
	else if (headName == "blue")
	{
		order = s2;
	}

	switch (order[i])
	{
	case 0: switchWarrior = &numberWarrior[0]; break;
	case 1: switchWarrior = &numberWarrior[1]; break;
	case 2: switchWarrior = &numberWarrior[2]; break;
	case 3: switchWarrior = &numberWarrior[3]; break;
	case 4: switchWarrior = &numberWarrior[4]; break;
	}

	while (searchTimes <= 5)
	{
		if ((*warri[order[i]]).life <= life)
		{
			life = life - (*warri[order[i]]).life;
			warriorNumber++;
			(*switchWarrior)++;

			std::cout << time << ' ' << headName << ' ' << (*warri[order[i]]).names << ' ' << warriorNumber << " born with strength " <<
				(*warri[order[i]]).life << ',' << *switchWarrior << ' ' << (*warri[order[i]]).names << " in " << headName << " headquarter" << std::endl;
			i++;
			i = i % 5;
			break;
		}
		else
		{
			i++;
			i = i % 5;
			searchTimes++;
			if (searchTimes == 5)
			{
				stoped = true;
			}
		}
	}
	nexti = i;
	if (stoped)
	{
		std::cout << time << ' ' << headName << " headquarter stops making warriors " << std::endl;
	}

}
int Command::bornwarrior(int i, int time)
{
	if (stoped)
	{
		return stoped;
	}
	else
	{
		bornjudge(i, time);
		return stoped;
	}
}

int main()
{
	int how;
	std::cin >> how;
	for (int i = 0; i < how; i++)
	{
		int life;
		std::cin >> life;
		int s[5];
		for (int i = 0; i < 5; i++)
		{
			std::cin >> s[i];
		}
		std::cout << "case:" << how << std::endl;
		int times = 0;
		int i = 0;
		int r = 0, b = 0;
		Command red("red", life, s[0], s[1], s[2], s[3], s[4]);
		Command blue("blue", life, s[0], s[1], s[2], s[3], s[4]);
		while (1)
		{
			r = red.bornwarrior(red.nexti, times);
			b = blue.bornwarrior(blue.nexti, times);
			times++;
			if (r && b)
			{
				break;
			}

		}
	}
	return 0;
}