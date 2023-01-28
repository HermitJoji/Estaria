#ifndef DUNGEON_DUNGEON_H
#define DUNGEON_DUNGEON_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ios> 

using namespace std;

class Dungeon{

public:
    static string name;

    Dungeon(string namae);

    static int attempts, progress, completed, completedChecker, deaths;

    int stats ();

};

extern Dungeon goblinDungeon;


#endif