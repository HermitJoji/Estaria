#include "Dungeon.h"
#include "GameSystem.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

using namespace this_thread;
using namespace chrono_literals;
using std::chrono::system_clock;

string Dungeon::name;

Dungeon::Dungeon(string namae){name = namae;}

int Dungeon::attempts{0}, Dungeon::progress{0}, Dungeon::completed{0}, Dungeon::completedChecker{0}, Dungeon::deaths{0};

int Dungeon::stats (){
    int nameRow, attemptsRow, progressRow, deathsRow, completedRow, 
    nameLen, attemptsLen, progressLen, deathsLen, completedLen, 
    section1Longest, section2Longest;

        nameLen = size(name); attemptsLen = numberLen(attempts);  progressLen = numberLen(progress);
        deathsLen = numberLen(deaths); completedLen = numberLen(completed);

        section1Longest = 17 + nameLen;
        section2Longest = 21 + progressLen; 

        attemptsRow = section2Longest - (14 + attemptsLen);
        deathsRow = section2Longest - (12 + deathsLen);
        completedRow = section2Longest -(15 + completedLen);

        cout << "╔"; for (size_t i(0); i < (section1Longest - 4); i++){cout << "═";} cout << "╗" << endl;
        cout << "║ [Dungeon]: " << name << setw(0) <<" ║" << endl;
        cout << "╚"; for (size_t i(0); i < (section1Longest - 4); i++){cout << "═";} cout << "╝" << endl;

        cout << "╔"; for (size_t i(0); i < (section2Longest - 4); i++){cout << "═";} cout << "╗" << endl;
        cout << "║ [Attempts]: " << attempts << setw(attemptsRow) <<" ║" << endl;
        cout << "║ [Progress]: " << progress << "/10" << setw(0) <<" ║" << endl;
        cout << "║ [Completed]: " << completed << setw(completedRow) <<" ║" << endl;
        cout << "║ [Deaths]: " << deaths << setw(deathsRow) <<" ║" << endl;
        cout << "╚"; for (size_t i(0); i < (section2Longest - 4); i++){cout << "═";} cout << "╝" << endl;

        sleep_for(1s); cout << endl; return 0;
}

Dungeon goblinDungeon("Goblin Cave");