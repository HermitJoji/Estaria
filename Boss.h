#ifndef BOSS_H
#define BOSS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ios> 

using namespace std;

class Boss{
public:
    static string name;

    static int level, maxHp, attack, defence, experience, money;

    Boss(int lv, string namae, int health, int atk, int def, string move, int exp, int cash);

    static int attempts, progress, completed, completedChecker, deaths;

    int status();

    int logs ();

};

extern Boss goblinBoss;

#endif