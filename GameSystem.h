#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H


#include <iostream>
#include <string>
#include <iomanip>
#include <ios>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

extern string textSpeed;
extern string autosave;

void writing(string text, bool endline, bool skip);
int numberLen(int number);

namespace checkpoints{
    extern int save, prolouge, moneySpent,
        kukuriUnlocked, kukuriForest,
        goblinCaveUnlocked, goblinCave,
        goblinBossUnlocked, goblinBoss;
};

namespace saveSystem{
    void gameSave(); void gameContinue(); void hideSaveFile();
}

namespace estariaSystem{
    void errorMessage(); void notUnlockedMessage(); void LoadingMessage();
    string bossWarning(string bosstype); void settingsDoneMessage();
    void tips();
}

namespace consoleAction{
    void storyMode(); void battle(); void settingsInterface();void shop(); int shopBuying(string itemName, int itemPrice);
}

namespace story{
    void prolouge(); void kukuriForest();
}

#endif

