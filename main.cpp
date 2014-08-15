#include <iostream>
#include <string>
class Command;
class Warrior;
class Weapons
{
protected:
	int attr;
	std::string name;
public:
	void getWeaopn(int numbers)
	{
		switch (numbers)
		{
		case 0:
			name = "sword";
			break;
		case 1:
			name = "bomb";
			break;
		case 2:
			name = "arrow";
		default:
			break;
		}

	}
	Weapons(int numbers):attr(0)
	{
		getWeaopn(numbers);
	}
	std::string getName()
	{
		return name;
	}
};
class Warrior
{
protected:
	int life;
	static int number;
	std::string names;
	Command *pa;
public:
	Warrior(int life_,Command &p_);
	void printCommands(int times);
	friend class Command;
}; 
class Dragon : public Warrior
{
	Weapons weapon;
	double morale;
public:
	void getMorale();
	Dragon(int life_,Command &p):Warrior(life_,p),weapon(number)
	{
		getMorale();
		names = "dragon";
	}
	void printCommand(int times);

};
class Ninja : public Warrior
{
	Weapons weapon1;
	Weapons weapon2;
public:
	Ninja(int life_,Command &p):Warrior(life_,p),weapon1(number %3),weapon2((number + 1) % 3)
	{
		names = "Ninja";
	}
	void printCommand(int times);

};
class Iceman : public Warrior
{
	Weapons weapon;
public:
	Iceman(int life_,Command &p):Warrior(life_,p),weapon(number)
	{
		names = "iceman";
	}
	void printCommand(int times);

};
class Lion : public Warrior
{
	double loylaty;
public:
	void getLoylaty();
	Lion(int life_,Command &p):Warrior(life_,p)
	{
		getLoylaty();
		names = "Lion";
	}
	void printCommand(int times)
	{
		getLoylaty();
		Warrior::printCommands(times);
		std::cout<<"it's loylaty is "<<loylaty<<std::endl;
	}

};
class Wolf : public Warrior
{
public:
	Wolf(int life_,Command &p):Warrior(life_,p)
	{
		names = "wolf";
	}
	void printCommand(int times)
	{
		Warrior::printCommands(times);
	}

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
	int nexti;										   // the next warrior is ?
	Dragon dragon;
	Ninja ninja;
	Iceman iceman;
	Lion lion;
	Wolf wolf;
	int bornjudge(int i,int time);
	Warrior *warri[5];
public:	

	Command(std::string headName,int life,int lifeDragon,int lifeNinjia,int lifeIceman,int lifeLion,int lifeWolf);
	int bornwarrior(int time);                          //use bornjudge  and return is stoped.
	friend class Warrior;
	friend class Dragon;
	friend class Ninja;
	friend class Iceman;
	friend class Lion;
	friend class Wolf;
};
Warrior::Warrior(int lifes,Command &p_):life(lifes),pa(&p_)
{
	number = pa->warriorNumber;
}
void Warrior::printCommands(int times)
	{
		std::cout<<times<<' '<<pa->headName<<' '<<names<<' '<<pa->warriorNumber<<" born with strength "<<
			life<<','<<*(pa->switchWarrior)<<' '<<names<<" in "<<pa->headName<<" headquarter"<<std::endl;
	}
void Ninja::printCommand(int times)
	{
		weapon1.getWeaopn(pa->warriorNumber %3);
		weapon2.getWeaopn((pa->warriorNumber+1) %3);
		Warrior::printCommands(times);
		std::cout<<"it has a "<<weapon1.getName()<<" and a "<<weapon2.getName()<<std::endl;
	}
void Dragon::printCommand(int times)
	{
		weapon.getWeaopn(pa->warriorNumber);
		getMorale();
		Warrior::printCommands(times);
		std::cout<<"it has a "<<weapon.getName()<<", and it's morale is "<<morale<<std::endl;
	}
void Iceman::printCommand(int times)
	{
		weapon.getWeaopn(pa->warriorNumber);
		Warrior::printCommands(times);
		std::cout<<"it has a "<<weapon.getName()<<std::endl;
	}
void Lion::getLoylaty()
	{
		loylaty = pa->life;
	}
void Dragon::getMorale()
	{
		morale = pa->life / (double)life;
	}
Command::Command(std::string headName_,int life_,int lifeDragon,int lifeNinjia,int lifeIceman,int lifeLion,int lifeWolf):
	headName(headName_),life(life_),dragon(lifeDragon,*this),ninja(lifeNinjia,*this),
	iceman(lifeIceman,*this),lion(lifeLion,*this),wolf(lifeWolf,*this),numberWarrior(),warriorNumber(0)
{
	warri[0] = &dragon;
	warri[1] = &ninja;
	warri[2] = &iceman;
	warri[3] = &lion;
	warri[4] = &wolf;
	stoped = false;
	nexti = 0;

}
int Command::bornjudge(int i,int time)
{
	void *pwarrior[5] = {&dragon,&ninja,&iceman,&lion,&wolf };
	int s1[]={2,3,4,1,0};
	int s2[]={3,0,1,2,4};
	int searchTimes = 0;
	if(headName =="red")
	{
		order = s1;
	}
	else if(headName =="blue")
	{
		order = s2;
	}
	switch (order[i])
	{
	case 0: 
		switchWarrior = &numberWarrior[0]; 
		break;
	case 1:
		switchWarrior = &numberWarrior[1]; 
		break;
	case 2:
		switchWarrior = &numberWarrior[2]; 
		break;
	case 3:
		switchWarrior =	&numberWarrior[3]; 
		break;
	case 4: 
		switchWarrior = &numberWarrior[4]; 
		break;
	}
	while( searchTimes <= 5 )
	{
		if((*warri[order[i]]).life<=life)
		{
			life =life-(*warri[order[i]]).life;
			warriorNumber++;
			(*switchWarrior)++;
			switch (order[i])
			{
			case 0:
				dragon.printCommand(time);break;
			case 1:
				ninja.printCommand(time);break;
			case 2:
				iceman.printCommand(time);break;
			case 3:
				lion.printCommand(time);break;
			case 4:
				wolf.printCommand(time);break;
			}
			i++;
			i = i % 5;
			break;
		}
		else
		{
			i++;
			i = i % 5;
			searchTimes++;
			if(searchTimes == 5)
			{
				stoped = true;
				break;
			}
		}
	}
	if(stoped)
	{
		std::cout<<time<<' '<<headName<<" headquarter stops making warriors"<<std::endl;
	}
	return i;
}
int Command::bornwarrior(int time)
{
	if(stoped)
	{
		return stoped;
	}
	else
	{
		nexti = bornjudge(nexti, time);
		return stoped;
	}
}
int Warrior::number = 0;
int main()
{
	int how;
	std::cin>>how;
	for(int i = 0; i < how; i++)
	{
		int life;
		std::cin>>life;
		int s[5];
		for(int j = 0; j < 5; j++)
		{
			std::cin>>s[j];
		}
		std::cout<<"case:"<<i+1<<std::endl;
		int times = 0;
		int r = 0, b = 0;
		Command red("red", life, s[0], s[1], s[2], s[3], s[4]);
		Command blue("blue", life, s[0], s[1], s[2], s[3], s[4]);
		while(1)
		{
			r = red.bornwarrior(times);
			b = blue.bornwarrior(times);
			times++;
			if(r && b)
			{
				break;
			}
		
		}
	}
	return 0;
}