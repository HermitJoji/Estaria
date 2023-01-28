#include "Mobs.h"
#include "GameSystem.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;

using namespace this_thread;
using namespace chrono_literals;
using std::chrono::system_clock;

string Mobs::name;
int Mobs::level{1}, Mobs::baseMaxhp{0}, Mobs::baseAttack{0}, Mobs::baseDefence{0}, Mobs::baseExp{0}, Mobs::baseMoney{0};

Mobs::Mobs(string assign, int maxLife, int strength, int def, int xp, int cash){
    name = assign;
    baseAttack = strength; attack = strength;
    baseDefence = def; defence = def;
    baseMaxhp = maxLife; maxHP = maxLife; health = maxLife;
    baseExp = xp; exp = xp; baseMoney = cash; money = baseMoney;
}

int Mobs::health{baseMaxhp}, Mobs::maxHP{baseMaxhp}, Mobs::attack{baseAttack}, Mobs::defence{baseDefence},
Mobs::exp{baseExp}, Mobs::money{baseMoney};


void Mobs::mobLevel(int lv){

    double mobBonus{0.25};
    level = round(lv);
    if (level == 0){level = 1;}

    maxHP = baseMaxhp; attack = baseAttack; defence = baseDefence, exp = baseExp; money = baseMoney;

    if (level > 1){

        for (size_t i = 1; i < lv; i++){
            maxHP += ceil(baseMaxhp * mobBonus); attack += ceil(baseAttack * mobBonus);
            defence += ceil(baseDefence * mobBonus); exp += ceil(baseExp * 1.5); money += ceil(baseMoney * 1.2);
        }
    }
        
    health = maxHP;
}

int Mobs::status(){

    int row1, row2, row3, row4, nameLen, healthLen, maxhpLen, attacklen, defenceLen, levelRow, levelLen, section1Longest, section2Longest;

    nameLen = size(name); healthLen = numberLen(health); maxhpLen = numberLen(maxHP); attacklen = numberLen(attack);
    defenceLen = numberLen(defence); levelLen = numberLen(level);


    section1Longest = 13 + nameLen;
    section2Longest = 16 + defenceLen;
    row1 = section2Longest - (9 + nameLen); row2 = section2Longest - (8 + healthLen + maxhpLen); row3 = section2Longest - (11 + attacklen);
    row4 = section2Longest - (12 + defenceLen); levelRow = (section1Longest - (10 + levelLen));

    cout << "╔"; for (size_t i(0); i < (section1Longest - 3); i++){cout << "═";} cout << "╗" << endl;
    cout << setw(0) << "║ [Level]: "  << level << setw(levelRow) <<" ║" << endl;
    cout << setw(0) << "║ [Name]: "  << name << setw(0) <<" ║" << endl;
    cout << "╚"; for (size_t i(0); i < (section1Longest - 3); i++){cout << "═";} cout << "╝" << endl;

    cout << "╔"; for (size_t i(0); i < (section2Longest - 3); i++){cout << "═";} cout << "╗" << endl;
    cout << "║ [Hp]: " << health << "/" << maxHP << setw(row2) << " ║" << endl;
    cout << "║ [Attack]: " << attack << setw(row3) << " ║" << endl;
    cout << "║ [Defence]: " << defence << setw(row4) << " ║" << endl;
    cout << "╚"; for (size_t i(0); i < (section2Longest - 3); i++){cout << "═";} cout << "╝" << endl;
    cout << endl;

    return 0;
}

Mobs goblin("goblin", 150, 7, 11, 100, 50);