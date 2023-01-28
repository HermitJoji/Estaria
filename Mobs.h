#ifndef MOBS_H
#define MOBS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ios> 

using namespace std;

class Mobs{

public:
    static string name;
    static int level, baseMaxhp, baseAttack, baseDefence, baseExp, baseMoney;

    Mobs(string assign, int maxLife, int strength, int def, int xp, int cash);

    static int health, maxHP, attack, defence, exp, money;

    void mobLevel(int lv);

    int status();
    

};

extern Mobs goblin;


#endif