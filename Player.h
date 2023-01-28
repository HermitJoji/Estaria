#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ios> 

using namespace std;

class Player
{
public:
    static string name, debuff;

    static int Level, experience, maxExp, dexterity, dodge, money, debuffBuildUp, deaths;

    static double health, maxHp, attack, defence;

    int status();

    static int potion;
    static int greaterPotion;
    static int antidote;

    int inventory(string type);

    void exp(int expGained, int moneyGained);

    void die();
};

extern Player player;

#endif