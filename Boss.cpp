
#include "Boss.h"
#include "GameSystem.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;

using namespace this_thread;
using namespace chrono_literals;
using std::chrono::system_clock;

string Boss::name;
int Boss::level{0}, Boss::maxHp{0}, Boss::attack{0}, Boss::defence{0}, Boss::experience{0}, Boss::money{0};

Boss::Boss(int lv, string namae, int health, int atk, int def, string move, int exp, int cash){level = lv;name = namae;
    maxHp = health; attack = atk; defence = def; experience = exp; money = cash;}

int Boss::attempts, Boss::progress{0}, Boss::completed{0}, Boss::completedChecker{0}, Boss::deaths{0};

int Boss::status(){

    int row1, row2, row3, row4, nameLen, maxhpLen, attacklen, defenceLen, levelRow, levelLen, section1Longest, section2Longest;

    nameLen = size(name); maxhpLen = numberLen(maxHp); attacklen = numberLen(attack);
    defenceLen = numberLen(defence); levelLen = numberLen(level);


    section1Longest = 13 + nameLen;
    section2Longest = 12 + (maxhpLen * 2);
    row1 = section2Longest - (9 + nameLen); row2 = section2Longest - (8 + maxhpLen + maxhpLen); row3 = section2Longest - (11 + attacklen);
    row4 = section2Longest - (12 + defenceLen); levelRow = (section1Longest - (10 + levelLen));

    cout << "╔"; for (size_t i(0); i < (section1Longest - 3); i++){cout << "═";} cout << "╗" << endl;
    cout << setw(0) << "║ [Level]: "  << level << setw(levelRow) <<" ║" << endl;
    cout << setw(0) << "║ [Name]: "  << name << setw(0) <<" ║" << endl;
    cout << "╚"; for (size_t i(0); i < (section1Longest - 3); i++){cout << "═";} cout << "╝" << endl;

    cout << "╔"; for (size_t i(0); i < (section2Longest - 3); i++){cout << "═";} cout << "╗" << endl;
    cout << "║ [Hp]: " << maxHp << "/" << maxHp << setw(0) << " ║" << endl;
    cout << "║ [Attack]: " << attack << setw(row3) << " ║" << endl;
    cout << "║ [Defence]: " << defence << setw(row4) << " ║" << endl;
    cout << "╚"; for (size_t i(0); i < (section2Longest - 3); i++){cout << "═";} cout << "╝" << endl;
    cout << endl;

    return 0;
}

int Boss::logs (){
    int nameRow, attemptsRow, progressRow, deathsRow, completedRow, 
    nameLen, attemptsLen, progressLen, deathsLen, completedLen, 
    section1Longest, section2Longest;

        nameLen = size(name); attemptsLen = numberLen(attempts);  progressLen = numberLen(progress);
        deathsLen = numberLen(deaths); completedLen = numberLen(completed);

        section1Longest = 17 + nameLen;
        section2Longest = 19 + completedLen; 

        attemptsRow = section2Longest - (14 + attemptsLen);
        deathsRow = section2Longest - (12 + deathsLen);

        cout << "╔"; for (size_t i(0); i < (section1Longest - 4); i++){cout << "═";} cout << "╗" << endl;
        cout << "║ [Dungeon]: " << name << setw(0) <<" ║" << endl;
        cout << "╚"; for (size_t i(0); i < (section1Longest - 4); i++){cout << "═";} cout << "╝" << endl;

        cout << "╔"; for (size_t i(0); i < (section2Longest - 4); i++){cout << "═";} cout << "╗" << endl;
        cout << "║ [Attempts]: " << attempts << setw(attemptsRow) <<" ║" << endl;
        cout << "║ [Completed]: " << completed << setw(0) <<" ║" << endl;
        cout << "║ [Deaths]: " << deaths << setw(deathsRow) <<" ║" << endl;
        cout << "╚"; for (size_t i(0); i < (section2Longest - 4); i++){cout << "═";} cout << "╝" << endl;

        sleep_for(1s); cout << endl; return 0;
}


Boss goblinBoss(30,"Goblin King", 2500, 50, 35, "Goblin Bash", 20000, 15000);