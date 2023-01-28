#ifndef BATTLEMACHANICS_H
#define BATTLEMECHANICS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ios>
#include <thread>
#include <chrono>
#include <fstream>


using namespace std;

double damageCalculator(string mob, string turn);

int playerAttack(int playerDamage, string mobName, bool mobmorale, int CriticalPercent);

int normalMobAttack(string mobName, int mobDamage, bool mobmorale, int missChance);

int defendedMobAttack(string mobName, int mobDamage, bool mobmorale, int missChance);

int bossSpecialAttack1(string mobName, string playerAction, int mobDamage);

int bossSpecialAttack2(string mobName, string playerAction, int mobDamage);

string fight(string mob, string type);

void dungeon(string dungeonName);

#endif