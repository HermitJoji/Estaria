#include <thread>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cmath>
#include "GameSystem.h"
#include "Player.h"
#include "Mobs.h"
#include "Dungeon.h"
#include "Boss.h"
#include "BattleMechanics.h"


using namespace std;

using namespace this_thread;
using namespace chrono_literals;
using std::chrono::system_clock;


string textSpeed{"normal"};
string autosave{"off"};

void writing(string text, bool endline, bool skip){

    for (auto data : text){
        cout << data;
        if (textSpeed == "normal"){sleep_for(20ms);}
        else if (textSpeed == "fast"){sleep_for(5ms);}
    }

    if (endline){ cout << endl;}

    if (skip){
         if (textSpeed == "normal"){sleep_for(250ms);}
         else if (textSpeed == "fast"){sleep_for(100ms);}}
}

int numberLen(int number){
    int n{};

    if (number == 0){n = 1;}

    else{
        while (number != 0) { 
            number /= 10;
            n++;
        };
    }

    return n;
}




int checkpoints::save{0}, checkpoints::prolouge{0}, checkpoints::moneySpent{0},
    checkpoints::kukuriUnlocked{0}, checkpoints::kukuriForest{0},
    checkpoints::goblinCaveUnlocked{0}, checkpoints::goblinCave{0},
    checkpoints::goblinBossUnlocked{0}, checkpoints::goblinBoss{0};




void saveSystem::gameSave(){

    ofstream saveFile("init.dat");

    if(saveFile){

        writing("Saving game",0,1); writing(".",0,1); writing("..",0,1); writing("...",1,1);  
        writing("Game Saved ",1,1);

        // player info
        saveFile << 1;  saveFile << "\n";
        saveFile << player.Level; saveFile << "\n";
        saveFile << player.name; saveFile << "\n";
        saveFile << player.experience; saveFile << " ";    saveFile << player.maxExp; saveFile << "\n";
        saveFile << player.health; saveFile << " ";        saveFile << player.maxHp; saveFile << "\n";
        saveFile << player.attack; saveFile << "\n";
        saveFile << player.defence; saveFile << "\n";
        saveFile << player.dexterity; saveFile << "\n";
        saveFile << player.dodge; saveFile << "\n";
        saveFile << player.deaths; saveFile << "\n";
        saveFile << player.money; saveFile << "\n";
        saveFile << player.debuff; saveFile << "\n";
        saveFile << "\n";

        //settings
        saveFile << textSpeed; saveFile << "\n";
        saveFile << autosave; saveFile << "\n";
        saveFile << "\n";

        // items
        saveFile << player.potion; saveFile << "\n";
        saveFile << player.greaterPotion; saveFile << "\n";
        saveFile << player.antidote; saveFile << "\n";
        saveFile << "\n";

        // progress 
        saveFile << checkpoints::prolouge; saveFile << "\n";
        saveFile << checkpoints::kukuriUnlocked; saveFile << " ";        saveFile << checkpoints::kukuriForest; saveFile << "\n";
        saveFile << checkpoints::goblinCaveUnlocked; saveFile << " ";    saveFile << checkpoints::goblinCave; saveFile << "\n";
        saveFile << checkpoints::goblinBossUnlocked; saveFile << " ";    saveFile << checkpoints::goblinBoss; saveFile << "\n";
        saveFile << checkpoints::moneySpent; saveFile << "\n";
        saveFile << "\n";

        //dungeon
        saveFile << goblinDungeon.attempts; saveFile << " "; saveFile << goblinDungeon.progress; saveFile << " ";
        saveFile << goblinDungeon.completed; saveFile << " "; saveFile << goblinDungeon.deaths; saveFile << "\n";
        saveFile << "\n";

        //boss
        saveFile << goblinBoss.attempts; saveFile << " "; saveFile << goblinBoss.completed; saveFile << " ";
        saveFile << goblinBoss.deaths; saveFile << "\n";


 
        saveFile.close();
        hideSaveFile();
    }
    else{writing("Error: init.dat not found!",1,1);}
    
}

void saveSystem::gameContinue(){
    int x;
    string y;

    ifstream loadFile("init.dat");

    if(loadFile){
        // deinitializing files

        loadFile >> checkpoints::save;
        if (checkpoints::save == 1){
            writing("Loading save file ",0,1); writing(".",0,1); writing("..",0,1); writing("...",1,1);
            writing("Save file Loaded ",1,1);

            // player info
            loadFile >> player.Level;
            loadFile >> player.name;
            loadFile >> player.experience;    loadFile >> player.maxExp;
            loadFile >> player.health;        loadFile >> player.maxHp;
            loadFile >> player.attack;
            loadFile >> player.defence;
            loadFile >> player.dexterity;
            loadFile >> player.dodge;
            loadFile >> player.deaths;
            loadFile >> player.money;
            loadFile >> player.debuff;

            //settings
            loadFile >> textSpeed;
            loadFile >> autosave;

            //items
            loadFile >> player.potion;
            loadFile >> player.greaterPotion;
            loadFile >> player.antidote;

            // progress
            loadFile >> checkpoints::prolouge;
            loadFile >> checkpoints::kukuriUnlocked;        loadFile >> checkpoints::kukuriForest;
            loadFile >> checkpoints::goblinCaveUnlocked;    loadFile >> checkpoints::goblinCave;
            loadFile >> checkpoints::goblinBossUnlocked;    loadFile >> checkpoints::goblinBoss;
            loadFile >> checkpoints::moneySpent;

            //dungeon
            loadFile >> goblinDungeon.attempts;  loadFile >> goblinDungeon.progress; loadFile >> goblinDungeon.completed;
            loadFile >> goblinDungeon.deaths;

            // boss
            loadFile >> goblinBoss.attempts; loadFile >> goblinBoss.completed; loadFile >> goblinBoss.deaths;

            loadFile.close();
            hideSaveFile();
        }
        else{writing("There is no save file available",1,1);}
    }
    else{writing("Error: init.dat not found!",1,1);}
    
}

void saveSystem::hideSaveFile(){

}




void estariaSystem::errorMessage(){cout << "oi " << player.name << "!"; writing(" it seems like you entered an invalid command!",1,1);}

void estariaSystem::notUnlockedMessage(){cout << "oi " << player.name << "!"; writing(" This action is not unlocked yet!",1,1);}

void estariaSystem::LoadingMessage(){writing("Loading",0,1); writing(".",0,1); writing("..",0,1); writing("...",1,1);}

string estariaSystem::bossWarning(string bosstype){
    string userInput;
    if (bosstype == "goblin"){
        writing("You are about to face the Goblin King",1,0); writing("Recommended stats: Player lv18+",1,0);
        writing("Recommended item:  Greater Potions{20+}, antidotes{5+}",1,0);
        if (player.health < (0.5 * player.maxHp)){writing("Psst",0,1); writing(" check your hp.",1,1);}}

    writing("There is no escape once started",1,1); cout << endl;

    writing("Do you wish to face the Boss? ",1,0);
    cout << "[y] or [yes].\n";
    cout << "> ";
    getline(cin, userInput);

    return userInput;

}

void estariaSystem::settingsDoneMessage(){ writing("changes applied!",1,1); }

void estariaSystem::tips(){
    int tips, messages{14};
    srand(time(nullptr));
    tips = rand() % messages + 1;


    if (tips == 1){writing("Tips: Do not forget to replenish your health after every battle...",1,1);}
    else if (tips == 2){writing("Tips: if you are lost, try completing stories in storymode, dungeons and Bosses...",1,1);}
    else if (tips == 3){writing("Tips: The grubby merchant is a shrewd man who is proficent at making adventurers splurge...",1,1);}
    else if (tips == 4){writing("Tips: Don't forget to visit the shop...",0,1); writing(" this is not a paid sponsorship...",1,1);}
    else if (tips == 5){writing("Tips: You lose a level on death...",1,1);}
    else if (tips == 6){writing("Tips: You can change the game settings to suit your preference in Settings...",1,1);}
    else if (tips == 7){writing("Tips: Estaria was made in a week and a half with over 1500 lines of code!...",1,1);}
    else if (tips == 8){writing("Tips: If you Like the game, send a feedback to the developer!...",1,1);}
    else if (tips == 9){writing("Tips: Goblins speak in enchantment table...",1,1);}
    else if (tips == 10){writing("Tips: Debuffs stay even after a battle...",1,1);}
    else if (tips == 11){ writing("Tips: You can turn on autosave in settings...",1,1);}
    else if (tips == 12){writing("Tips: You can preassign commands by simply spamming them, but dont send too much at a time",0,1);
            writing(" you were warned..",1,1);
    }
    else if (tips == 13){writing("Tips: CTRL C terminates the program, but does not save..",1,1);}
    else if (tips == 14){writing("Tips: Bosses attack hard every 3 rounds..",1,1);}

    cout << endl;
        
}




void consoleAction::storyMode(){
    bool error;
    string stringInput;
    int userInput;

    while (true){
        error = false;

        cout << "               ╔═══════════════════════════════╗" << endl;
        cout << "               ║          [STORY MODE]         ║" << endl;
        cout << "               ╚═══════════════════════════════╝" << endl;

        cout << "╔═══════════════════════════════════════════════════════════╗" << endl;
        cout << "╠ ╔═════════════════════════╗     ╔═══════════════════════╗ ╣" << endl;
        cout << "║      [1]-Prolouge [✓]" ;if (checkpoints::kukuriForest){cout << setw(42) << "[2]-[Kukuri Forest] [✓]  ║" << endl;}
        else if (checkpoints::kukuriUnlocked && !checkpoints::kukuriForest){cout << setw(40) << "[2]-[Kukuri Forest]    ║" << endl;}
        else{cout << setw(40) << "[-]-[-----------------]  ║" << endl;}
        cout << "╠ ╚═════════════════════════╝     ╚═══════════════════════╝ ╣" << endl;
        cout << "╠ ╔═════════════════════════╗     ╔═══════════════════════╗ ╣" << endl;
        cout << "║  [-]-[-------------------]       [-]-[-----------------]  ║" << endl;
        cout << "╠ ╚═════════════════════════╝     ╚═══════════════════════╝ ╣" << endl;
        cout << "╠ ╔═════════════════════════╗     ╔═══════════════════════╗ ╣" << endl;
        cout << "║  [-]-[-------------------]       [-]-[-----------------]  ║" << endl;
        cout << "╠ ╚═════════════════════════╝     ╚═══════════════════════╝ ╣" << endl;
        cout << "╠                        ╔══════════╗                       ╣" << endl;
        cout << "║                         [0]-[Back]                        ║" << endl;
        cout << "╠                        ╚══════════╝                       ╣" << endl;
        cout << "╚═══════════════════════════════════════════════════════════╝" << endl;

        cout << "> ";
        getline(cin, stringInput);
        try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage; cout << '\n';error = true;}
        cout << endl;
        sleep_for(0.5s);
        if (!error){
            if (userInput == 0){estariaSystem::tips();break;}
            else if (userInput == 1){story::prolouge(); if (autosave == "on"){saveSystem::gameSave();} estariaSystem::tips();}
            else if (userInput == 2){story::kukuriForest(); if (autosave == "on"){saveSystem::gameSave();} estariaSystem::tips();}
            else if (userInput == 3){estariaSystem::notUnlockedMessage;}
            else if (userInput == 4){estariaSystem::notUnlockedMessage;}
            else if (userInput == 5){estariaSystem::notUnlockedMessage;}
            else if (userInput == 6){estariaSystem::notUnlockedMessage;}
            else {estariaSystem::errorMessage;}
        } 
    }
}

void consoleAction::battle(){
    bool error;
    string stringInput;
    int userInput;

    while (true){
        error = false;
        cout << "       ╔════════════════════════════╗" << endl;
        cout << "       ║          [Battle]          ║" << endl;
        cout << "       ╚════════════════════════════╝" << endl;

        cout << "╔═════════════════════════════════════════╗" << endl;
        cout << "╠ ╔═══════════════╗     ╔═══════════════╗ ╣" << endl;
        cout << "║   [1]-[Dungeon]          [2]-[BOSS]     ║" << endl;
        cout << "╠ ╚═══════════════╝     ╚═══════════════╝ ╣" << endl;
        cout << "╠ ╔═══════════════╗     ╔═══════════════╗ ╣" << endl;
        cout << "║  [3]-[Inventory]         [4]-[Status]   ║" << endl;
        cout << "╠ ╚═══════════════╝     ╚═══════════════╝ ╣" << endl;
        cout << "╠ ╔═══════════════╗     ╔═══════════════╗ ╣" << endl;
        cout << "║    [5]-[Shop]            [0]-[Back]     ║" << endl;
        cout << "╠ ╚═══════════════╝     ╚═══════════════╝ ╣" << endl;
        cout << "╚═════════════════════════════════════════╝" << endl;
        cout << "> ";
        getline(cin, stringInput);
        try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage; cout << '\n';error = true;}
        cout << endl;
        sleep_for(0.5s);

        if (!error){

            if (userInput == 0){estariaSystem::tips();break;}

            else if (userInput == 1){
                estariaSystem::tips();
                while (true){
                    error = false;

                    cout << "                  ╔════════════════════════════╗" << endl;
                    cout << "                  ║          [DUNGEON]         ║" << endl;
                    cout << "                  ╚════════════════════════════╝" << endl;
                    
                    cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
                    cout << "╠ ╔═══════════════════════════╗     ╔═════════════════════════╗ ╣" << endl;
                    if (checkpoints::goblinCave){cout << "║   [1]-[The Goblin Cave] [✓] ";} 
                    else if (checkpoints::goblinCaveUnlocked && !checkpoints::goblinCave){cout << "║     [1]-[The Goblin Cave]   ";}
                    else{cout << "║  [-]-[---------------------]";}
                    cout << setw(37) << "[-]-[-------------------]  ║" << endl;
                    cout << "╠ ╚═══════════════════════════╝     ╚═════════════════════════╝ ╣" << endl;
                    cout << "╠ ╔═══════════════════════════╗     ╔═════════════════════════╗ ╣" << endl;
                    cout << "║  [-]-[---------------------]       [-]-[-------------------]  ║" << endl;
                    cout << "╠ ╚═══════════════════════════╝     ╚═════════════════════════╝ ╣" << endl;
                    cout << "╠                          ╔══════════╗                         ╣" << endl;
                    cout << "║                           [0]-[Back]                          ║" << endl;
                    cout << "╠                          ╚══════════╝                         ╣" << endl;
                    cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;

                    cout << "> ";
                    getline(cin, stringInput);
                    try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage; cout << '\n';error = true;}
                    cout << endl;
                    sleep_for(0.5s);

                    if (!error){
                        if (userInput == 1){
                            if (checkpoints::goblinCaveUnlocked){dungeon("goblin");if (autosave == "on"){saveSystem::gameSave();} 
                            estariaSystem::tips();}
                            else{estariaSystem::notUnlockedMessage;}
                        }
                    
                        else if (userInput == 2){writing("other dungeons are still being worked on",1,1);}
                        
                        else if (userInput == 3){writing("other dungeons are still being worked on",1,1);}

                        else if (userInput == 4){writing("other dungeons are still being worked on",1,1);}

                        else if (userInput == 0){estariaSystem::tips();break;}

                        else{estariaSystem::errorMessage;}
                    }
                }
            }
        
            else if (userInput == 2){
                estariaSystem::tips();
                while (true){
                    error = false;

                    cout << "                   ╔═════════════════════════╗" << endl;
                    cout << "                   ║          [BOSS]         ║" << endl;
                    cout << "                   ╚═════════════════════════╝" << endl;

                    cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
                    cout << "╠ ╔═══════════════════════════╗     ╔═════════════════════════╗ ╣" << endl;
                    if (checkpoints::goblinBoss){cout << "║   [1]-[The Goblin King] [✓] ";} 
                    else if (checkpoints::goblinBossUnlocked && !checkpoints::goblinBoss){cout << "║     [1]-[The Goblin King]   ";}
                    else{cout << "║  [-]-[---------------------]";}
                    cout << setw(37) << "[-]-[-------------------]  ║" << endl;
                    cout << "╠ ╚═══════════════════════════╝     ╚═════════════════════════╝ ╣" << endl;
                    cout << "╠ ╔═══════════════════════════╗     ╔═════════════════════════╗ ╣" << endl;
                    cout << "║  [-]-[---------------------]       [-]-[-------------------]  ║" << endl;
                    cout << "╠ ╚═══════════════════════════╝     ╚═════════════════════════╝ ╣" << endl;
                    cout << "╠                          ╔══════════╗                         ╣" << endl;
                    cout << "║                           [0]-[Back]                          ║" << endl;
                    cout << "╠                          ╚══════════╝                         ╣" << endl;
                    cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;

                    cout << "> ";
                    getline(cin, stringInput);
                    try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage; cout << '\n';error = true;}
                    cout << endl;
                    sleep_for(0.5s);

                    if (!error){
                        if (userInput == 1){
                            if (checkpoints::goblinBossUnlocked){
                                stringInput = estariaSystem::bossWarning("goblin");
                                if (stringInput == "y" || stringInput == "yes"){fight("goblinboss", "boss");
                                if (autosave == "on"){saveSystem::gameSave();} estariaSystem::tips();}
                                else{cout << player.name; writing(" flees",1,1);}
                            }
                            else{estariaSystem::notUnlockedMessage;}
                        }
                    
                        else if (userInput == 2){writing("other bosses are still being worked on",1,1);}
                        
                        else if (userInput == 3){writing("other bosses are still being worked on",1,1);}

                        else if (userInput == 4){writing("other bosses are still being worked on",1,1);}

                        else if (userInput == 0){estariaSystem::tips();break;}

                        else{estariaSystem::errorMessage;}
                    }
                }
            }

            else if (userInput == 3){player.inventory(""); if (autosave == "on"){saveSystem::gameSave();} estariaSystem::tips();}

            else if (userInput == 4){player.status();estariaSystem::tips();}

            else if (userInput == 5){consoleAction::shop(); if (autosave == "on"){saveSystem::gameSave();} estariaSystem::tips();}

            else {estariaSystem::errorMessage;}
        }
    }
}

void consoleAction::settingsInterface(){
    string stringInput;
    int userInput;

    while(true){
        bool error{false};

        cout << "               ╔═════════════════════════════╗" << endl;
        cout << "               ║          [SETTINGS]         ║" << endl;
        cout << "               ╚═════════════════════════════╝" << endl;

        cout << "╔══════════════════════════════════════════════════════════╗" << endl;
        cout << "╠ ╔════════════════════════╗     ╔══════════════════════╗  ╣" << endl;
        cout << "║  [1]-[Text Speed]: " << textSpeed;  if (textSpeed == "normal"){cout << setw(24);} else{cout << setw(26);}
        cout << "[2]-[autosave]: "<< autosave ; if (autosave == "off"){cout <<"     ║" << endl;} else{cout <<"      ║" << endl;} 
        cout << "╠ ╚════════════════════════╝     ╚══════════════════════╝  ╣" << endl;
        cout << "╠ ╔════════════════════════╗     ╔══════════════════════╗  ╣" << endl;
        cout << "║     [3]-[Name Change]           [4]-[Delete Save File]   ║" << endl;
        cout << "╠ ╚════════════════════════╝     ╚══════════════════════╝  ╣" << endl;
        cout << "╠                       ╔══════════╗                       ╣" << endl;
        cout << "║                        [0]-[Back]                        ║" << endl;
        cout << "╠                       ╚══════════╝                       ╣" << endl;
        cout << "╚══════════════════════════════════════════════════════════╝" << endl;
        cout << endl;
        cout << "> ";
        getline(cin, stringInput);
        try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage; error = true;}
        cout << endl;

        if (!error){

            if (userInput == 1){
                while(true){
                    error = false;
                    cout << "╔═════════════════════════════╗" << endl;
                    cout << "║  [1]-[Normal]   [2]-[Fast]  ║" << endl;
                    cout << "╚═════════════════════════════╝" << endl;
                    cout << "> ";
                    getline(cin, stringInput);
                    try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage; error = true;}
                    cout << endl;

                    if (!error){
                        if (userInput == 1){textSpeed = "normal"; break;}
                        else if (userInput == 2){textSpeed = "fast"; break;}
                        else{estariaSystem::errorMessage;}
                    }
                }
                estariaSystem::settingsDoneMessage;
            }
 
            else if (userInput == 2){
                while(true){
                    error = false;
                    cout << "╔═══════════════════════╗" << endl;
                    cout << "║  [1]-[On]   [2]-[Off  ║" << endl;
                    cout << "╚═══════════════════════╝" << endl;
                    cout << "> ";
                    getline(cin, stringInput);
                    try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage; error = true;}
                    cout << endl;

                    if (!error){
                        if (userInput == 1){autosave = "on"; break;}
                        else if (userInput == 2){autosave = "off"; break;}
                        else{estariaSystem::errorMessage;}
                    }
                }
                estariaSystem::settingsDoneMessage;
            }

            else if (userInput == 3){
                string userName;
                cout << "Input name\n"
                     << "> ";
                getline(cin, stringInput);
                for(auto chara : stringInput){if (chara == ' ' ){chara = '-';} 
                    userName += chara;}
                player.name = userName;
                estariaSystem::settingsDoneMessage;
            }
 
            else if (userInput == 4){
                ofstream saveFile("init.dat");

                if(saveFile){
                    writing("Are you sure you want to delete your save file",1,1); 
                    cout << "[yes i know what i am doing] to proceed.\n";
                    cout << "> ";
                    getline(cin, stringInput);
                        if (stringInput == "yes i know what i am doing"){
                            writing("Deleting save file",0,1); writing(".",0,1); writing("..",0,1); writing("...",1,1);  
                            writing("save file deleted.",0,1); writing(" Restart game to apply changes.",1,1);
                            saveFile << 0;
                            saveFile.close();
                            saveSystem::hideSaveFile;
                            cout << endl;
                            break;
                        }
                        else{writing("Returning to settings....",1,1);}
                }
                else{writing("Error: Save.txt not found!",1,1); writing("Returning to settings....",1,1);}
            }
 
            else if (userInput == 0){saveSystem::gameSave(); break;}

            else{estariaSystem::errorMessage;}

        }
        
    }
}

void consoleAction::shop(){
    int userInput, amountBought;
    string stringInput;
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    writing("║ Grubby merchant: Hello ",0,0); cout << player.name; sleep_for(0.2s); writing(" welcome to my shop",0,0); 
    cout << "                                           ║\n"; sleep_for(0.2s);
    writing("║                  you see,",0,1); writing(" i sell some rather interesting wares that may be of use to you ║",1,1);
    writing("║                  come, come",0,1); writing(" take a look at my wares",0,0); cout << "                                      ║"<< endl;
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════╝" << endl;
    sleep_for(0.2s);

    while(true){
        bool error{false};

        cout << "╔══════════════════════════╗" << endl;
        cout << "║          [SHOP]          ║" << endl;
        cout << "╚══════════════════════════╝" << endl;
        cout << "╔══════════════════════════╗" << endl;
        if (checkpoints::kukuriForest) {cout << "║ [1]-Potion $200\n";}
        if (checkpoints::goblinCave) {cout << "║ [2]-Greater Potion $860\n";}
        if (checkpoints::goblinBossUnlocked) {cout << "║ [3]-Antidote $1200\n";}
        cout << "║ [0]-Back\n";
        cout << "╚══════════════════════════╝" << endl;
        cout << endl;
        cout << "╔══════════════════════════╗" << endl;
        cout << "║ [Balance]:" << player.money << endl;
        cout << "╚══════════════════════════╝" << endl;

        cout << "> ";
        getline(cin, stringInput);
        try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage();error = true;}
        cout << endl;

        if (!error){
            if (userInput == 0){
                cout << "╔══════════════════════════════╗" << endl;
                writing("║ Grubby merchant: come again. ║",1,1); 
                cout << "╚══════════════════════════════╝" << endl;
                cout << endl;
                break;
            }
            

            else if (userInput == 1){
                if (checkpoints::kukuriForest){ amountBought = shopBuying("Potion", 200); player.potion += amountBought;}
                else{estariaSystem::notUnlockedMessage();}  
            }
            else if (userInput == 2){
                if (checkpoints::kukuriForest){ amountBought = shopBuying("Greater Potion", 860); player.greaterPotion += amountBought;}
                else{estariaSystem::notUnlockedMessage();}  
            }
            else if (userInput == 3){
                if (checkpoints::goblinBossUnlocked){ amountBought = shopBuying("Antidote", 1200); player.antidote += amountBought;}
                else{estariaSystem::notUnlockedMessage();}  
            }
            else{cout << "invalid command!, try again.\n";}
            
            
            
            
        }
        
    }
sleep_for(0.3s);
}

int consoleAction::shopBuying(string itemName, int itemPrice){

    string stringInput;
    int userInput, price{0};
    while(true){
        bool error{false};
        cout << "╔═══════════════════════════════════════════════════════╗" << endl;
        writing("║ Grubby merchant: How much ",0,0); cout << itemName << "(s) does " << player.name;writing(" want?",1,1);
        cout << "╚═══════════════════════════════════════════════════════╝" << endl;

        cout << "> ";
        getline(cin, stringInput);
        try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage();error = true;}
        cout << endl;

        if (!error){
            for (int i(0); i < userInput; i++){price += itemPrice;}
            if (userInput == 0){
                cout << "╔═══════════════════════════════════════════════════════════╗" << endl;
                writing("║ Grubby merchant: That's fine",0,0); cout << "                              ║\n";
                writing("║                  come, come",0,1); writing(" take a look at my other wares ║",1,1);
                cout << "╚═══════════════════════════════════════════════════════════╝" << endl;
                return 0;
            }
            else{
                if (player.money > price){
                    cout << "╔═══════════════════════════════════════════════╗" << endl;
                    writing("║Grubby merchant: The price would be $",0,0); cout << price << endl; sleep_for(0.2s);
                    writing("║                 is that okay with you?",1,1);
                    cout << "╚═══════════════════════════════════════════════╝" << endl;
                    cout << "╔══════════════════════════╗" << endl;
                    cout << "║ [Balance]:" << player.money << endl;
                    cout << "╚══════════════════════════╝" << endl;
                    cout << "[y] or [yes]\n";
                    cout << "> ";
                    getline(cin, stringInput);
                    if (stringInput == "y" || stringInput == "yes"){
                        cout << "╔════════════════════════════════════════════════╗" << endl;
                        writing("║ Grubby merchant: Ho ho! ",0,1); cout << userInput << " " << itemName; writing("(s) coming up!",1,1);
                        cout << "╚════════════════════════════════════════════════╝" << endl;
                        player.money -= price; checkpoints::moneySpent += price; userInput; return userInput;
                    }
                    else{cout << "╔═══════════════════════════════════════════════════════════╗" << endl;
                            writing("║ Grubby merchant: That's fine",0,0); cout << "                              ║\n";
                            writing("║                  come, come",0,1); writing(" take a look at my other wares ║",1,1);
                            cout << "╚═══════════════════════════════════════════════════════════╝" << endl;
                        return 0;}
                }
                else{
                    cout << "╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
                    writing("║ Grubby merchant: ou",0,1); writing(" it seems that adventurer ",0,0); cout << player.name;
                    writing(" does not have enough money to buy this ",0,0); cout << itemName << endl;
                    cout << "╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;
                    return 0;
                }
            }
        }
    }
}




void story::prolouge(){
    string userInput;

    if (checkpoints::prolouge){
        writing("Do you want to skip? ",1,1);
        cout << "[y] or [yes] to skip.\n";
        cout << "> ";
        getline(cin, userInput);
            if (userInput == "yes" || userInput == "y"){return; cout << endl;}}

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║"; writing(" In the days of the old,",0,1); writing(" there was confilct, war and bloodshed which spewed equally among every race.",0,0);cout << " ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" Each race,",0,1); writing(" in search for power resulted in summoning heroes from different dimensions.",0,0);cout << "               ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" The heroes were said to have immense power and wisdom, they were the deciding factors in every war.",0,1); ;cout << ". ║\n"; sleep_for(0.3s);
    cout << "║                                                                                                      ║\n";
    cout << "║"; writing(" After everything had been destroyed by war and many lives had been lost,",0,0); cout << "                             ║\n";
    cout << "║"; writing(" the remaining races decided to settle their differences, and create a peace pact.",0,0); cout << "                    ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" A pact that resulted in the current Estaria,",0,1); writing(" a world where every race lives equally and peacefully.",0,0);cout << "  ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" a world with diverse people and culture.",0,1); cout << "                                                             ║\n"; sleep_for(0.3s);
    cout << "║                                                                                                      ║\n"; 
    cout << "║"; writing(" But the damages from the past war had not been healed,",0,1); writing(" something was broken.",0,0);cout << "                         ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" The barrier keeping worlds apart was broken.",0,1) ;cout << "                                                         ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" The worlds began to combine and as a result,",0,1); writing(" people kept appearing from different worlds.",0,0);cout << "            ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" They were called,",0,1); writing(" THE WANDERERS.",0,0);cout << "                                                                     ║\n"; sleep_for(0.3s);
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
    cout << endl;
    checkpoints::prolouge = 1; checkpoints::kukuriUnlocked += 1;
    if (checkpoints::kukuriUnlocked == 1){writing("You have unlocked the next story",1,1); cout << endl;}

    return;
}

void story::kukuriForest(){
    int playerDeathOrigin = player.deaths, playerDeath{0};
    writing("Kukuri Forest",1,1);
    cout << endl;

    string userInput, result;

    if (checkpoints::kukuriForest){
        writing("Do you want to skip? ",1,1);
        cout << "[y] or [yes] to skip.\n";
        cout << "> ";
        getline(cin, userInput);
            if (userInput == "yes" || userInput == "y"){return; cout << endl;}}

    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║"; writing(" ****: It's been days since i've been lost in this forest.",0,0); ;cout << "                                            ║\n"; sleep_for(0.3s);
    cout << "║"; writing("       The last thing i remember was jumping into bed after pulling an all nighter to complete *****.",0,1); ;cout << " ║\n"; sleep_for(0.3s);
    cout << "║"; writing("       did i die?,",0,1); writing(" did i get abducted?",0,0);cout << "                                                                ║\n"; sleep_for(0.3s);
    cout << "║"; writing("       it's quiet, too quiet.",0,1); writing(" This is like those troupes right?",0,0);cout << "                                       ║\n";
    cout << "║"; writing("       where a monster attacks from the bushes or something.",0,0); ;cout << "                                          ║\n"; sleep_for(0.3s);
    cout << "║"; writing("       But this is Earth i think.",0,1); writing(" I'm more worried of encountering bears or coyotes.",0,0);cout << "                  ║\n"; sleep_for(0.3s);
    cout << "║"; writing("       Not like anything's gonna happen,",0,1); writing(" i should probably just keep walking till i find civilization",0,0);cout << " ║\n";
    cout << "║"; writing("       or something.",0,1); ;cout << "                                                                                  ║\n"; sleep_for(0.3s);
    cout << "║"; writing("       Someone's there,",0,1); writing(" finally, i can get directions to a town at least.",0,0);cout << "                             ║\n"; sleep_for(0.3s);
    cout << "║"; writing("       um hello, could i....",0,0); ;cout << "                                                                          ║\n";
    cout << "║                                                                                                      ║\n";
    cout << "║"; writing(" As you approach the voices you hear, you see small figures running around kicking something",0,0); ;cout << "          ║\n";
    cout << "║"; writing(" Probably a ball you think.",0,0); ;cout << "                                                                           ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" You take a closer look to find short, green goblin like creatures running around,",0,0); ;cout << "                    ║\n";
    cout << "║"; writing(" kicking a dead person's head around like a ball.",0,0); ;cout << "                                                     ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" They notice you and violently grab their bloody weapons and begin their chase for you.",0,0); ;cout << "               ║\n"; sleep_for(0.3s);
    cout << "║                                                                                                      ║\n";
    cout << "║"; writing(" You run with all your might, knowing what fate awaits you if you happen to be caught.",0,0); ;cout << "                ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" After being chased for what seemed to be hours, you encounter a lone goblin blocking your path.",0,0); ;cout << "      ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" Knowing the remaining goblins would catch up if you stall,",0,0); writing(" you muster enough courage to fight.",0,0);cout << "       ║\n"; sleep_for(0.3s);
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
    cout << endl;
    goblin.mobLevel(1);
    result = fight("goblin", "story");
    playerDeath = player.deaths;
    if (result == "flee"){return;}
    if (playerDeath > playerDeathOrigin){return;}

    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║"; writing(" You win. but the victory was short lived, the goblins caught up",0,0); ;cout << "                                      ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" You are surrounded with no way to escape.",0,0); ;cout << "                                                            ║\n"; sleep_for(0.3s);
    cout << "║                                                                                                      ║\n"; sleep_for(0.5s);
    cout << "║"; writing(" Suddenly, you hear a battle cry, people appear one by one to attack the goblins.",0,0); ;cout << "                     ║\n"; sleep_for(0.3s);
    cout << "║                                                                                                      ║\n";
    cout << "║"; writing(" [Grumpy Man]: which cunt decided it was a good idea to go around rifling all the goblins?!",0,0); ;cout << "           ║\n"; sleep_for(0.3s);
    cout << "║"; writing("               i only came here to farm a bit for some wine money and now we got work to do?!.",0,0); ;cout << "        ║\n"; sleep_for(0.3s);
    cout << "║"; writing("               oi kahn, emily,",0,0); writing(" let's get this over with quickly!.",0,0);cout << "                                     ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" [Kahn]:       Alright, alright gustave. you know you don't always have to be grumpy right emi?",0,0); ;cout << "       ║\n"; sleep_for(0.3s);
    cout << "║"; writing(" [Emily]:      Exactly!, that's why he's sooo bald :P.",0,0); ;cout << "                                                ║\n"; sleep_for(0.3s);
    cout << "║"; writing("               oh, someones there, you still alive? whats your name?.",0,0); ;cout << "                                 ║\n"; sleep_for(0.3s);
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
    cout << endl;
    if (player.name == "player"){
        string userInput, userName;
        cout << "Input name\n"
                << "> ";
        getline(cin, userInput);
        for(auto chara : userInput){if (chara == ' ' ){chara = '-';} 
            userName += chara;}
        player.name = userName;}

    checkpoints::kukuriForest = 1; checkpoints::goblinCaveUnlocked += 1;
    if (checkpoints::goblinCaveUnlocked == 1){writing("You have unlocked the goblin dungeon",1,1);}
}
