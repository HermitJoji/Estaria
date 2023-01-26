#include <iostream>
#include <string>
#include <iomanip>
#include <ios>
#include <array>
#include <tuple>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <cmath>
#include <windows.h>
#include <fstream>


using namespace std;

using namespace this_thread;
using namespace chrono_literals;
using std::chrono::system_clock;



class Settings{
    public:
        string textSpeed {"normal"};
        string autosave {"off"};

        
};

Settings settings;

int writing(string text, bool endline, bool skip){

    for (auto data : text){
        cout << data;
        if (settings.textSpeed == "normal"){sleep_for(20ms);}
        else if (settings.textSpeed == "fast"){sleep_for(5ms);}
        
    }
    if (endline){ cout << endl;}
    if (skip){
         if (settings.textSpeed == "normal"){sleep_for(400ms);}
         else if (settings.textSpeed == "fast"){sleep_for(100ms);}}
    return 0;
}


void hideSaveFile(){
    
}

int numberLen(int number){
    int n{};
    if (number == 0){n = 1;}
    else{
    while (number != 0) {
        number /= 10;
        n++;
    };}
    

    return n;
}



class Player{

    public:
        int Level{1};
        string name {"player"};
        int experience{0};
        int maxExp{100};
        double health{100};
        double maxHp {100};
        double attack {10};
        double defence {10};
        int dexterity {1};
        int dodge {1};
        int money{1000};
        string debuff{"none"};
        int debuffBuildUp{0};
        int deaths {0};

        string weapon;
        string armor;

        int status(){

            int row1, row2, row3, row4, row5, row6, row7, debuffRow, moneyRow,nameLen, healthLen, maxhpLen, attacklen, defenceLen, dexLen, deathsLen,
            dodgelen, moneyLen, section1Longest, section2Longest,section3Longest, section4Longest, levelrow, levelLen, expLen, maxExpLen, debuffLen;

            nameLen = size(name); healthLen = numberLen(health); maxhpLen = numberLen(maxHp); attacklen = numberLen(attack);
            defenceLen = numberLen(defence); dexLen = numberLen(dexterity); deathsLen = numberLen(deaths); dodgelen = numberLen(dodge),
            levelLen = numberLen(Level), expLen = numberLen(experience), maxExpLen = numberLen(maxExp); debuffLen = size(debuff);
            moneyLen = numberLen(money);
        
            section1Longest = 13 + nameLen;
            levelrow = section1Longest - (10 + levelLen);
            
            section2Longest = 18 + dexLen;
            row1 = section2Longest - (11 + nameLen); row2 = section2Longest - (8 + healthLen + maxhpLen); row3 = section2Longest - (11 + attacklen);
            row4 = section2Longest - (12 + defenceLen); row6 = section2Longest - (10 + dodgelen); row7 = section2Longest - (11 + deathsLen);  

            section3Longest =  20 + (expLen + maxExpLen);
            moneyRow = section3Longest - (11 + moneyLen);

            section4Longest = 14 + debuffLen;

            cout << "╔"; for (size_t i(0); i < (section1Longest - 3); i++){cout << "═";} cout << "╗" << endl;
            cout << "║ [Level]: " << Level << setw(levelrow) <<" ║" << endl;
            cout << "║ [Name]: " << name << setw(0) <<" ║" << endl;
            cout << "╚"; for (size_t i(0); i < (section1Longest - 3); i++){cout << "═";} cout << "╝" << endl;


            cout << "╔"; for (size_t i(0); i < (section2Longest - 3); i++){cout << "═";} cout << "╗" << endl;
            cout << "║ [Hp]: " << health <<"/" << maxHp << setw(row2)<< " ║" << endl;
            cout << "║ [Attack]: " << attack << setw(row3) << " ║" << endl;
            cout << "║ [Defence]: " << defence << setw(row4) << " ║" << endl;
            cout << "║ [Dexterity]: " << dexterity << setw(0) << " ║" << endl;
            cout << "║ [Dodge]: " << dodge << setw(row6) << " ║" << endl;
            cout << "║ [Deaths]: " << deaths << setw(row7) << " ║" << endl;
            cout << "╚"; for (size_t i(0); i < (section2Longest - 3); i++){cout << "═";} cout << "╝" << endl;

            cout << "╔"; for (size_t i(0); i < (section3Longest - 3); i++){cout << "═";}cout << "╗" << endl;
            cout << "║ [Money]: $" << money << setw(moneyRow) << " ║" << endl;
            cout << "║ [Experience]: " << experience <<"/" << maxExp << setw(0)<< " ║" << endl;
            cout << "╚"; for (size_t i(0); i < (section3Longest - 3); i++){cout << "═";} cout << "╝" << endl;

            if (debuff != "none"){
            cout << "╔"; for (size_t i(0); i < (section4Longest - 3); i++){cout << "═";}cout << "╗" << endl;
            cout << "║ [Debuf]: " << debuff << setw(0)<< " ║" << endl;
            cout << "╚"; for (size_t i(0); i < (section4Longest - 3); i++){cout << "═";} cout << "╝" << endl;
            }



            sleep_for(1s);
            
            cout << endl;
            return 0;
        }

        int potion {1};
        int greaterPotion {0};
        int antidote{0};

        int inventory(string type){
            
            int numberLimit{0}, page{1}, itemUsed{0}, userInput;
            string stringInput;
            bool antidoteUsed{false};
            

            while(true){
                bool error{false};
                cout << "╔══════════════════════════╗" << endl;
                cout << "║        [INVENTORY]       ║" << endl;
                cout << "╚══════════════════════════╝" << endl;
                
                
                cout << "╔══════════════════════════╗" << endl;
                if (potion > 0) {cout << "║ [1]-Potion [" << potion << "]\n";}
                if (greaterPotion > 0) {cout << "║ [2]-Greater Potion [" << greaterPotion << "]\n";;}
                if (antidote > 0) {cout << "║ [3]-Antidote [" << antidote << "]\n";;}
                cout << "║ [0]-Back\n";
                cout << "╚══════════════════════════╝" << endl;
                cout << endl;

                cout << "> ";
                getline(cin, stringInput);
                try{userInput =  stoi(stringInput);} catch(const std::exception& e){cout << "invalid command!, try again.\n";error = true;}
                cout << endl;

                if (!error){
                     if (userInput == 0){break;}
                    

                    else if (userInput == 1){
                        if (potion > 0){
                            if (health == maxHp){writing("your health is already full!",1,1); cout << endl; }
                            else{health += 50;
                                cout << name; writing(" uses a potion, ",0,1); cout << name; writing(" feels refreshed.",1,1);
                                cout << name <<"'s hp gets restored by 50 points!" << endl;
                                if (health > maxHp){health = maxHp;}
                                cout << "Hp: " << health << "/" << maxHp << endl; cout << endl;
                                potion -= 1;
                                if (type == "battle"){itemUsed = 1; break;}
                            }
                        }
                        else{writing("You do not have any potions.",1,1);}
                    }
                    
                    else if (userInput == 2){
                        if (greaterPotion > 0){
                            if (health == maxHp){writing("your health is already full!",1,1); cout << endl; }
                            else{health += 120;
                                cout << name; writing(" uses a Greater potion, ",0,1); cout << name; writing(" feels refreshed.",1,1);
                                cout << name <<"'s hp gets restored by 120 points!" << endl;
                                if (health > maxHp){health = maxHp;}
                                cout << "Hp: " << health << "/" << maxHp << endl; cout << endl;
                                greaterPotion -= 1;
                                if (type == "battle"){itemUsed = 1; break;}
                            }
                        }
                        else{writing("You do not have any potions.",1,1);}
                    }
   
                    else if (userInput == 3){
                        if (antidote > 0){
                            if (debuff == "poisoned" || debuff == "Badly poisoned"){debuff = "none";
                                cout << name; writing(" uses an antidote, ",0,1); cout << name; writing(" feels better.",1,1);
                                cout << name <<" is no longer poisoned." << endl;
                                antidote -= 1; antidoteUsed = true;
                                if (type == "battle"){itemUsed = 1; break;}
                            else if (!antidoteUsed){writing("you are not poisoned!",1,1); cout << endl;}
                            }
                        }
                        else{writing("You do not have any antidotes.",1,1);}
                    }
  
                    else{cout << "invalid command!, try again.\n";};
                    
                }
                
            }
        sleep_for(0.3s);
        return itemUsed;
        }
        
        void exp(int expGained, int moneyGained){

            int levelGained{0}, oldAttack = attack, oldDefence = defence, oldMaxhp = maxHp, oldDex = dexterity,
            oldDodge = dodge, oldLevel = Level;

            int attackBonus{5}, hpBonus{10}, defenceBonus{5}, dexBonus{1}, dodgeBonus{1};


            cout << name << " gained " << expGained << " Xp and $" << moneyGained << endl;
            money += moneyGained;

            cout << endl;
            sleep_for(0.5s);

            experience += expGained;
           
            

            for (size_t i = 0; i < 100; i++)
            {
                maxExp = (pow(Level, 2)/ 0.01);
                 if ((experience - maxExp) >= 0){
                experience -= maxExp;
                levelGained++; Level++;
                 }
            }
            if (Level > 100){dexBonus = 0; dodgeBonus = 0;}
            
            if (levelGained == 1){
                attack += attackBonus; defence += defenceBonus; maxHp += hpBonus;
                dexterity += dexBonus; dodge += dodgeBonus;

                cout << name << " levelled up!!" << endl;
                cout << endl;

                cout << "----------------------------" << endl;
                cout << "Level: " << oldLevel << " ---> " << Level << endl;
                cout << "Max Health: " << oldMaxhp << " ---> " << maxHp << endl;
                cout << "Attack: " << oldAttack << " ---> " << attack << endl;
                cout << "Defence: " << oldDefence << " ---> " << defence << endl;
                cout << "Dexterity: " << oldDex << " ---> " << dexterity << endl;
                cout << "Dodge: " << oldDodge << " ---> " << dodge << endl;
                cout << "----------------------------" << endl;
                cout << endl;
                sleep_for(0.5s);

            }
            else if (levelGained > 1){
                for (size_t i = 0; i < levelGained; i++)
                {
                    attack += attackBonus; defence += defenceBonus; maxHp += hpBonus;
                    dexterity += dexBonus; dodge += dodgeBonus;
                }

                cout << name << " levelled up " << levelGained << " times!!!" << endl;
                cout << endl;

                cout << "----------------------------" << endl;
                cout << "Level: " << oldLevel << " ---> " << Level << endl;
                cout << "Max Health: " << oldMaxhp << " ---> " << maxHp << endl;
                cout << "Attack: " << oldAttack << " ---> " << attack << endl;
                cout << "Defence: " << oldDefence << " ---> " << defence << endl;
                cout << "Dexterity: " << oldDex << " ---> " << dexterity << endl;
                cout << "Dodge: " << oldDodge << " ---> " << dodge << endl;
                cout << "----------------------------" << endl;
                cout << endl;
                sleep_for(0.5s);
                }
        
        }

        void die(){
            if (Level > 1){
            Level -= 1; maxHp -= 5; attack -= 5; defence -=5; dodge -= 1; dexterity -= 1; deaths += 1; experience = 0;
            }
            else{deaths += 1;}
        }


};

class Mobs{

    public:
        string name;
        int level{1};

        int baseMaxhp, baseAttack, baseDefence, baseExp, baseMoney;

        Mobs(string assign, int maxLife, int strength, int def, int xp, int cash){
            name = assign;
            baseAttack = strength; attack = strength;
            baseDefence = def; defence = def;
            baseMaxhp = maxLife; maxHP = maxLife; health = maxLife;
            baseExp = xp; exp = xp; baseMoney = cash; money = baseMoney;
        }

        int health{baseMaxhp};
        int maxHP{baseMaxhp};
        int attack{baseAttack};
        int defence{baseDefence};
        int exp{baseExp};
        int money{baseMoney};


        void mobLevel(int lv){

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

        int status(){

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
};

class Dungeon{

    public:
        string name;
        
        Dungeon(string namae){name = namae;}

        int attempts{0};
        int progress{0};
        int completed{0};
        int completedChecker{0};
        int deaths{0};

        int stats (){
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
        



};

Player player;

class Boss{

    public:
        int level{};
        string name;
        int maxHp{};
        int attack{};
        int defence{};
        int experience{};
        int money{};
        Boss(int lv, string namae, int health, int atk, int def, string move, int exp, int cash){level = lv;name = namae;
            maxHp = health; attack = atk; defence = def; experience = exp; money = cash;}

        int attempts{0};
        int progress{0};
        int completed{0};
        int completedChecker{0};
        int deaths{0};

        int status(){

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

        int logs (){
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

};

class CheckPoints{
    public:
        int save{0}, prolouge{0}, moneySpent{0},
        kukuriUnlocked{0}, kukuriForest{0},
        goblinCaveUnlocked{0}, goblinCave{0},
        goblinBossUnlocked{0}, goblinBoss{0};

};

CheckPoints checkpoints;

Mobs goblin("goblin", 150, 7, 11, 100, 50);
Dungeon goblinDungeon("Goblin Cave");
Boss goblinBoss(30,"Goblin King", 2500, 50, 35, "Goblin Bash", 20000, 15000);


void gameContinue(){
    int x;
    string y;

    ifstream loadFile("save.txt");

    if(loadFile){
        // deinitializing files

        loadFile >> checkpoints.save;
        if (checkpoints.save == 1){
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
            loadFile >> settings.textSpeed;
            loadFile >> settings.autosave;

            //items
            loadFile >> player.potion;
            loadFile >> player.greaterPotion;
            loadFile >> player.antidote;

            // progress
            loadFile >> checkpoints.prolouge;
            loadFile >> checkpoints.kukuriUnlocked;        loadFile >> checkpoints.kukuriForest;
            loadFile >> checkpoints.goblinCaveUnlocked;    loadFile >> checkpoints.goblinCave;
            loadFile >> checkpoints.goblinBossUnlocked;    loadFile >> checkpoints.goblinBoss;
            loadFile >> checkpoints.moneySpent;

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
    else{writing("Error: Save.txt not found!",1,1);}
    
}

void gameSave(){

    ofstream saveFile("save.txt");

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
        saveFile << settings.textSpeed; saveFile << "\n";
        saveFile << settings.autosave; saveFile << "\n";
        saveFile << "\n";

        // items
        saveFile << player.potion; saveFile << "\n";
        saveFile << player.greaterPotion; saveFile << "\n";
        saveFile << player.antidote; saveFile << "\n";
        saveFile << "\n";

        // progress 
        saveFile << checkpoints.prolouge; saveFile << "\n";
        saveFile << checkpoints.kukuriUnlocked; saveFile << " ";        saveFile << checkpoints.kukuriForest; saveFile << "\n";
        saveFile << checkpoints.goblinCaveUnlocked; saveFile << " ";    saveFile << checkpoints.goblinCave; saveFile << "\n";
        saveFile << checkpoints.goblinBossUnlocked; saveFile << " ";    saveFile << checkpoints.goblinBoss; saveFile << "\n";
        saveFile << checkpoints.moneySpent; saveFile << "\n";
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
    else{writing("Error: Save.txt not found!",1,1);}
    
}


class Console{


    public:
        double damageCalculator(string mob, string turn){

            double damage, mobAttack, mobDefence, mobmaxHp;

            if (mob == "goblin"){mobAttack = goblin.attack; mobDefence = goblin.defence; mobmaxHp = goblin.maxHP;}
            else if (mob == "goblinboss"){mobAttack = goblinBoss.attack; mobDefence = goblinBoss.defence; mobmaxHp = goblinBoss.maxHp;}

            if (turn == "player"){damage = (4 * player.attack) - ( 2 * mobDefence);}
            else if (turn == "mob"){damage = (4 * mobAttack) - (2 * player.defence);} 

            if (damage < 0){ damage = 0;}
            
            return damage;
            }

        int playerAttack(int playerDamage, string mobName, bool mobmorale, int CriticalPercent){
            int damageVariance, criticalChance;
            srand(time(nullptr));
            damageVariance = rand() % 10;
            criticalChance = rand() % CriticalPercent;
            
            if (playerDamage != 0){
                if (damageVariance <= 3 && criticalChance > player.dexterity){
                    playerDamage -= ceil(player.attack * 0.25);
                    cout << player.name; writing(" attacks!",0,1); cout << " the " << mobName; writing(" blocks the attack, ",0,1);
                    cout << player.name; writing(" deals ",0,0); cout << playerDamage;
                    writing(" points of damage!",1,1);
                    cout << endl;
                }
                else if (criticalChance <= player.dexterity){
                    playerDamage *= 2.5;
                    writing("WwWhHhOoOaAa! ",0,1); cout << player.name; writing(" hits right where it hurts! ",1,1);
                    cout << player.name; writing(" deals ",0,0); cout << playerDamage; writing(" points of damage!",1,1);
                    cout << endl;
                }
                else{
                    cout << player.name; writing(" attacks!",0,1); writing(" They deal ",0,0); cout << playerDamage;
                    writing(" points of damage!",1,1);
                    cout << endl;
                }
            }
            
            else{
                cout << player.name; writing(" attacks!",0,1); writing(" They deal no damage ",1,1);
                mobmorale = true;
                cout << endl;
            }
        return playerDamage;
        }

        int normalMobAttack(string mobName, int mobDamage, bool mobmorale, int missChance){
            srand(time(nullptr));
            int dodgeChance;
            dodgeChance = rand() % missChance;

            if (dodgeChance <= player.dexterity){
                if (mobmorale){
                    cout << "The "<< mobName; writing(" notices how weak ",0,0); cout << player.name << " is. ";
                    sleep_for(0.5s);
                    cout << "The "<< mobName; writing(" chuckles",1,1);
                }
                cout << "The "<< mobName; writing(" attacks!",1,1);
                writing("Is this ultra instinct?!!?! ",0,1);
                cout << player.name; writing(" dodges elegantly",1,1);
                mobDamage = 0;
                cout << endl;
            }
            else{
                if (mobmorale){
                    mobDamage *= 2;
                    cout << "The "<< mobName; writing(" notices how weak ",0,0); cout << player.name << " is. ";
                    sleep_for(0.5s);
                    cout << "The "<< mobName; writing(" chuckles",1,1);
                }
                cout << "The "<< mobName; writing(" attacks!",0,1); writing(" They deal ",0,0); cout << mobDamage;
                writing(" points of damage!",1,1);
                cout << endl;
                
            }
        return mobDamage;
        }
 
        int defendedMobAttack(string mobName, int mobDamage, bool mobmorale, int missChance){
            mobDamage *= 0.5;
            if (mobDamage < 0) {mobDamage = 0;}

            srand(time(nullptr));
            int dodgeChance;
            dodgeChance = rand() % missChance;

            if (dodgeChance <= player.dexterity){
                cout << "The "<< mobName; writing(" attacks!",1,1);
                writing("Is this ultra instinct?!!?! ",0,1);
                cout << player.name; writing(" dodges elegantly",1,1);
                mobDamage = 0;
                cout << endl;
            }
            else{
            cout << "The "<< mobName; writing(" attacks!",0,1); cout << " but " << player.name << " blocks!." << endl;
            sleep_for(0.25s);
            cout << "The "<< mobName; writing(" deals ",0,0); cout << mobDamage; writing(" points of damage!",1,1);
            cout << endl;  

            
            }
        return mobDamage;
        }

        int bossSpecialAttack1(string mobName, string playerAction, int mobDamage){
            int debuffChance, debuffChancePercent{10}, 
            srand(time(nullptr)); debuffChance = rand() % debuffChancePercent + 1; if (debuffChance < 1){debuffChance = 1;}
             round(debuffChance); player.debuffBuildUp++;
            if (playerAction != "idle" && playerAction != "status"){

                if (mobName == goblinBoss.name){
                    mobDamage *= 2;
                    if (playerAction == "defend"){mobDamage *= 0.6; debuffChancePercent = 20;
                        cout << "The " << mobName; writing(" attacks using a Rusty Dagger!!",0,1); cout << " but " << player.name; writing(" was prepared to receieve the attack ",1,1);
                        cout << "The " << mobName << " deals " << mobDamage; writing(" points of damage!",1,1); cout << endl;}
                    else{
                        cout << "The " << mobName; writing(" attacks using a Rusty Dagger!!",0,1); writing(" They deal ",0,0); cout << mobDamage; writing(" points of damage!",1,1);
                        cout << endl;}
                    
                    if (player.debuffBuildUp >= debuffChance){if (player.debuff == "poisoned"){player.debuff = "Badly poisoned";}
                         else if (player.debuff != "Badly poisoned" && player.debuff == "none"){player.debuff = "poisoned";}; player.debuffBuildUp = 0;}
                }
           
            } 
        return mobDamage;
        }

        int bossSpecialAttack2(string mobName, string playerAction, int mobDamage){
            int debuffChance, debuffChancePercent;
            int ally, allyDamage(0.5 * mobDamage);
            srand(time(nullptr)); ally = rand() % 5 + 1; round(ally); if (ally < 3){ally = 3;}

            if (playerAction != "idle" && playerAction != "status"){

                if (mobName == goblinBoss.name){
                    mobDamage *= 2;debuffChancePercent = 10; 
                    if (playerAction == "defend"){mobDamage *= 0.6; debuffChancePercent = 20; allyDamage = (0.25 * mobDamage);
                     cout << player.name; writing(" prepares for the oncoming onslaught ",1,1); cout << endl;}

                    cout << "The " << mobName; writing(" is enraged!!!!",1,1);
                    cout << "The " << mobName; writing(" calls for allies ",0,1); cout << ally; writing(" Hob Goblins appear!.",1,1);
                    writing("the Hob goblins attack with a rusty dagger and deal ",0,0); cout << allyDamage; writing(" points of damage each!",1,1); cout << endl;

                    for(int i; i < ally; i++){++player.debuffBuildUp; 
                        srand(time(nullptr)); debuffChance = rand() % debuffChancePercent + 1; if (debuffChance < 1){debuffChance = 1;} round(debuffChance); 
                        if (player.debuffBuildUp >= debuffChance){if (player.debuff == "poisoned"){player.debuff = "Badly poisoned";}
                        else if (player.debuff != "Badly poisoned" && player.debuff == "none"){player.debuff = "poisoned";}; player.debuffBuildUp = 0;}
                    }

                    cout << "The " << mobName; writing(" also attacks using a Rusty Dagger!!",0,1); writing(" They deal ",0,0); cout << mobDamage; writing(" points of damage!",1,1);
                    cout << endl; player.debuffBuildUp++; mobDamage += (allyDamage * ally);
                    srand(time(nullptr)); debuffChance = rand() % debuffChancePercent + 1; if (debuffChance < 1){debuffChance = 1;} round(debuffChance);
                    if (player.debuffBuildUp >= debuffChance){if (player.debuff == "poisoned"){player.debuff = "Badly poisoned";}
                        else if (player.debuff != "Badly poisoned" && player.debuff == "none"){player.debuff = "poisoned";}; player.debuffBuildUp = 0;}
                }
            }
           
            
            return mobDamage;
        } 

        string battle(string mob, string type)
        { 
            string playerInput, result, boss, debuffMessage, stringInput;
            double playerDamage; 
            player.debuffBuildUp = 0;
    
            string mobName;
            double mobHp, mobMaxHp, mobDamage, mobExp, mobMoney;

            int rounds{1}, userInput, damageVariance, criticalChance, dodgeChance, escapeChance, extraMobDamage, debuffDamage;


            if (mob == "goblin"){mobName = goblin.name; mobHp = goblin.health; mobMaxHp = goblin.maxHP; mobExp = goblin.exp; mobMoney = goblin.money;
                goblin.status();}

            else if (mob == "goblinboss"){mobName = goblinBoss.name; mobHp = goblinBoss.maxHp;mobMaxHp = goblinBoss.maxHp; mobExp = goblinBoss.experience;
                type = "boss"; boss = "goblin"; goblinBoss.attempts++; mobMoney = goblinBoss.money; goblinBoss.logs(); sleep_for(0.2s); goblinBoss.status();}


            if (player.health <= 1 && type != boss){
                writing("You are low on hp. do you wish to continue?",1,1);
                cout << "[y] or [yes] to continue.\n";
                getline(cin, playerInput);
                if (playerInput != "y" && playerInput != "yes" ){cout << player.name; writing(" flees the battle.",1,1);
                 result = "flee"; return result;}
            }


            cout << player.name; writing(" has encountered a ",0,0); cout << mobName << "!" << endl;
            sleep_for(0.2s);
            writing("The Battle Begins!",1,1);
            cout << endl;

            while (player.health > 0 || mobHp > 0)
            {   

                bool mobmorale {false}, error{false};
                

                cout << "╔══════════════════════════════════╗" << endl;
                cout << "║        [Round]: [" << rounds << "]              ║" << endl;
                cout << "╚══════════════════════════════════╝" << endl;

                cout << "╔══════════════════════════════════╗" << endl;
                cout << "╠ ╔═══════════╗     ╔════════════╗ ╣" << endl;
                cout << "║  [1]-[Fight]       [2]-[Defend]  ║" << endl;
                cout << "╠ ╚═══════════╝     ╚════════════╝ ╣" << endl;
                cout << "╠ ╔═══════════╗     ╔════════════╗ ╣" << endl;
                cout << "║  [3]-[Items]       [4]-[status]  ║" << endl;
                cout << "╠ ╚═══════════╝     ╚════════════╝ ╣" << endl;
                cout << "╠           ╔═════════╗            ╣" << endl;
                cout << "║            [0]-[Run]             ║" << endl;
                cout << "╠           ╚═════════╝            ╣" << endl;
                cout << "╚══════════════════════════════════╝" << endl;

                cout << "> ";
                getline(cin, stringInput);
                try{userInput =  stoi(stringInput);} catch(const std::exception& e){errorMessage(); cout << '\n';error = true;}
                cout << endl;

                playerDamage = ceil(damageCalculator(mob, "player"));
                mobDamage = ceil(damageCalculator(mob, "mob"));

                if (!error){
                    if (userInput == 1){
                        result = "fight";

                        if (player.debuff != "none"){
                            if (player.debuff == "poisoned"){playerDamage *= 0.9;}
                            else if (player.debuff == "Badly poisoned"){playerDamage *= 0.8;}
                        }
                        

                        playerDamage = playerAttack(playerDamage, mobName, mobmorale, 400);

                    mobHp -= playerDamage;
                    if (mobHp <= 0) {break;}
                    }

                    else if (userInput == 2){

                        cout << player.name; writing(" readys their guard",1,1);
                        result = "defend";
                        cout << endl;
                    }

                    else if (userInput == 4){
                        rounds--; result = "status"; 
                        player.status();
                    }

                    else if (userInput == 3){
                        if (type == "dungeon"){cout << player.name; writing(" tries to open their bag ",1,1);
                            cout << "but the "<< mobName; writing(" does not give ",0,0); cout << player.name; writing(" a chance",1,1);
                            rounds--; result = "idle";
                            }

                        else{
                        int inventoryChecker{0};
                        inventoryChecker = player.inventory("battle");
                        if (inventoryChecker == 1){result = "heal";}
                        else{rounds--; result = "idle";}
                        }
                    }

                    else if (userInput == 0){
                        if (type == "story" || type == "boss"){writing("You can't escape!.",1,1); cout << endl; rounds--; result = "idle";}
                        else if (type == "dungeon"){
                            result = "flee";
                            cout << player.name; writing(" tries to flee, ",0,1); cout << player.name; writing(" flees the dungeon..",1,1); 
                                break;}
                        else{
                            result = "flee";
                            if (playerDamage > mobDamage){
                                cout << player.name; writing(" tries to flee, ",0,1); cout << player.name; writing(" got away",1,1);
                                break;
                            }
                            else{
                                srand(time(nullptr));
                                escapeChance = rand() % 10;
                                if (escapeChance > 3){
                                cout << player.name; writing(" tries to flee, ",0,1); cout << player.name; writing(" got away.",1,1);
                                break;
                                }
                                else{
                                cout << player.name; writing(" tries to flee, ",0,1); cout << player.name; writing(" couldnt escape",1,1);
                                
                                }
                            }
                        }
                    }

                    else{errorMessage(); rounds--; result = "idle";}

                    if (type == "boss"){

                        if ((rounds % 3) == 0 && mobHp > (0.4 * mobMaxHp)){
                            if (boss == "goblin"){mobDamage = bossSpecialAttack1(mobName, result, mobDamage);}
                        }
                        else if ((rounds % 3) == 0 && mobHp <= (0.4 * mobMaxHp)){
                            if (boss == "goblin"){mobDamage = bossSpecialAttack2(mobName, result, mobDamage);}
                        } 
                        else{
                            if (result == "fight" || result == "heal" || result == "flee"){mobDamage = normalMobAttack(mobName, mobDamage, mobmorale, 400);}

                            else if (result == "defend"){mobDamage = defendedMobAttack(mobName, mobDamage, mobmorale, 400);}
                        }
                        if (result != "idle" && result != "status"){
                            player.health -= mobDamage;
                            if (player.health <= 0) { player.health = 0; break;}
                        }
                    }

                    else{
                        if (result == "fight" || result == "heal" || result == "flee"){
                            mobDamage = normalMobAttack(mobName, mobDamage, mobmorale, 400);;
                            player.health -= mobDamage;
                            if (player.health <= 0) { player.health = 0; break;}
                        }

                        else if (result == "defend"){

                            mobDamage = defendedMobAttack(mobName,mobDamage, mobmorale, 400);
                            player.health -= mobDamage;
                            if (player.health <= 0) { player.health = 0; break;}
                        }
                    }

                    

                    if (player.debuff != "none" && player.health > 0){
                        
                        if (player.debuff == "poisoned"){debuffDamage = (0.025 * player.maxHp);
                            if (debuffMessage != "poison"){cout << player.name; writing(" has been poisoned!!!",1,1);}
                            cout << player.name; writing(" is poisoned!. ",0,1); cout << player.name << " loses " << debuffDamage; writing(" hp!.",1,1); 
                            cout << endl; debuffMessage = "poison";}

                        else if (player.debuff == "Badly poisoned"){debuffDamage = (0.04 * player.maxHp);
                            if (debuffMessage != "Badly poisoned"){cout << player.name; writing(" has been Badly poisoned!!!",1,1);}
                            cout << player.name; writing(" is Badly poisoned!. ",0,1); cout << player.name << " loses " << debuffDamage; writing(" hp!.",1,1); 
                            cout << endl; debuffMessage = "Badly poisoned";}
                        
                        player.health -= debuffDamage;
                        if (player.health <= 0) { player.health = 0; break;}
                        }
                                    

                    cout << player.name << endl;
                    cout << setw(6) << "[Hp]: " << player.health << "/" << player.maxHp << endl;
                    cout << endl;

                    cout << mobName << endl;
                    cout << setw(6) << "[Hp]: " << mobHp << "/" << mobMaxHp << endl;
                    cout << endl;

                rounds++;
                }

            }

            cout << endl;
            if (player.health > 0 && result != "flee"){
                if (type != "boss"){
                cout << player.name << " wins the battle!" << endl; cout << endl;
                cout << player.name << " has "<< player.health << "/" << player.maxHp << " hp left" << endl; sleep_for(0.5s);
                player.exp(mobExp, mobMoney);}
                else{
                cout << player.name << " has defeated the " << mobName << "!!!" << endl; cout << endl;
                cout << player.name << " has "<< player.health << "/" << player.maxHp << " hp left" << endl; sleep_for(0.5s);
                player.exp(mobExp, mobMoney);

                if (boss == "goblin"){goblinBoss.completed++; checkpoints.goblinBoss == 1; 
                    if (goblinBoss.completed == 1){writing("You have defeated the Goblin Boss for the first time!",1,1);} }
                cout << endl;
                
                }
            }   
            
            else if (player.health <= 0 && result != "flee"){

                result = "death";
                cout << player.name; writing(" died! ",0,1); cout << player.name; cout << " became " << mobName << " foood! " << endl;
                if(type != "story"){cout << player.name; writing(" lost a level!",1,1);
                    player.die(); cout << endl; player.health = 1;
                    if (type == "boss"){
                        if (boss == "goblin"){goblinBoss.deaths++;}
                    }
                }
                
            }
            return result;

        }

        void dungeon(string dungeonName){
            string result, mobname, userInput;

            if (dungeonName == "goblin"){goblinDungeon.stats(); goblinDungeon.attempts++; mobname = goblin.name;}
            cout << player.name; writing(" has entered the dungeon... ",1,1);
            cout << endl;

            bool flee{false};
            int waves{1}, mobLevel, rngVariance{10};
            while (waves < 11){

                cout << "╔══════════════════════════════════╗" << endl;
                cout << "║        [Wave]: " << waves << "/10              ║" << endl;
                cout << "╚══════════════════════════════════╝" << endl;
                sleep_for(0.2s);
                cout << endl;

                if (waves > 2 && waves <= 4){
                    rngVariance = 5;
                    srand(time(nullptr));
                    mobLevel = rand() % rngVariance + 1;
                    if (mobLevel <= 2){mobLevel = 3;}

                    if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = battle("goblin", "dungeon");}
                }
                else if (waves > 4 && waves <= 6){
                    rngVariance = 9;
                    srand(time(nullptr));
                    mobLevel = rand() % rngVariance + 1;
                    if (mobLevel <= 6){mobLevel = 6;}

                    if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = battle("goblin", "dungeon");}
                }
                else if (waves > 6 && waves <= 8){
                    rngVariance = 14;
                    srand(time(nullptr));
                    mobLevel = rand() % rngVariance + 1;
                    if (mobLevel <= 10){mobLevel = 10;}

                    if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = battle("goblin", "dungeon");}
                }
                else if (waves > 8 ){
                    rngVariance = 20;
                    srand(time(nullptr));
                    mobLevel = rand() % rngVariance + 1;
                    if (mobLevel <= 15){mobLevel = 15;}

                    if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = battle("goblin", "dungeon");}
                }
                else{
                    rngVariance = 2;
                    srand(time(nullptr));
                    mobLevel = rand() % rngVariance + 1;
                    if (mobLevel < 1){mobLevel = 1;}

                    if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = battle("goblin", "dungeon");}
                }

                if (result == "flee"){
                    break;
                    }
                if (result == "death"){
                    if (mobname == "goblin"){goblinDungeon.deaths += 1; break;}
                    }

                sleep_for(0.2s);
                
                if (waves < 10){
                    cout << "Wave " << (waves); writing(" completed",1,1);
                    writing("Do you want to leave the dungeon? ",1,0);
                    cout << "[y] or [Yes] to leave." << endl;
                    cout << "> ";
                    getline(cin, userInput);
                    if (userInput == "yes" || userInput == "y"){result = "flee"; break;}

                    writing("Preparing the next wave....",1,1);
                
                waves++;
                }
                else{break;}
            }

            if (result != "flee" && result != "death"){
                writing("You have completed the dungeon",1,1);
                if (mobname == "goblin"){goblinDungeon.completed += 1; checkpoints.goblinBossUnlocked = 1;
                    checkpoints.goblinCave = 1; if (goblinDungeon.progress < 10){goblinDungeon.progress = waves;}
                    if (checkpoints.goblinBossUnlocked == 1){writing("You have unlocked the Goblin Boss Area!",1,1); cout << endl;}
                }
            }
            else if (result == "death"){
                if (mobname == "goblin"){goblinDungeon.deaths++; if (goblinDungeon.progress < 10){goblinDungeon.progress = waves;}}

            }
            else if (result == "flee"){
                if (mobname == "goblin"){if (goblinDungeon.progress < 10){goblinDungeon.progress = waves;}}
            }
            


    }

        void shop(){
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
                if (checkpoints.kukuriForest) {cout << "║ [1]-Potion $200\n";}
                if (checkpoints.goblinCave) {cout << "║ [2]-Greater Potion $860\n";}
                if (checkpoints.goblinBossUnlocked) {cout << "║ [3]-Antidote $1200\n";}
                cout << "║ [0]-Back\n";
                cout << "╚══════════════════════════╝" << endl;
                cout << endl;
                cout << "╔══════════════════════════╗" << endl;
                cout << "║ [Balance]:" << player.money << endl;
                cout << "╚══════════════════════════╝" << endl;

                cout << "> ";
                getline(cin, stringInput);
                try{userInput =  stoi(stringInput);} catch(const std::exception& e){errorMessage();error = true;}
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
                        if (checkpoints.kukuriForest){ amountBought = shopBuying("Potion", 200); player.potion += amountBought;}
                        else{notUnlockedMessage();}  
                    }
                    else if (userInput == 2){
                        if (checkpoints.kukuriForest){ amountBought = shopBuying("Greater Potion", 860); player.greaterPotion += amountBought;}
                        else{notUnlockedMessage();}  
                    }
                    else if (userInput == 3){
                        if (checkpoints.goblinBossUnlocked){ amountBought = shopBuying("Antidote", 1200); player.antidote += amountBought;}
                        else{notUnlockedMessage();}  
                    }
                    else{cout << "invalid command!, try again.\n";}
                    
                    
                    
                    
                }
                
            }
        sleep_for(0.3s);
        }

        int shopBuying(string itemName, int itemPrice){

            string stringInput;
            int userInput, price{0};
            while(true){
                bool error{false};
                cout << "╔═══════════════════════════════════════════════════════╗" << endl;
                writing("║ Grubby merchant: How much ",0,0); cout << itemName << "(s) does " << player.name;writing(" want?",1,1);
                cout << "╚═══════════════════════════════════════════════════════╝" << endl;

                cout << "> ";
                getline(cin, stringInput);
                try{userInput =  stoi(stringInput);} catch(const std::exception& e){errorMessage();error = true;}
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
                                player.money -= price; checkpoints.moneySpent += price; userInput; return userInput;
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

        void errorMessage(){cout << "oi " << player.name << "!"; writing(" it seems like you entered an invalid command!",1,1);}

        void notUnlockedMessage(){cout << "oi " << player.name << "!"; writing(" This action is not unlocked yet!",1,1);}

        void LoadingMessage(){writing("Loading",0,1); writing(".",0,1); writing("..",0,1); writing("...",1,1);}

        string bossWarning(string bosstype){
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

        void settingsDoneMessage(){ writing("changes applied!",1,1); }

        void tips(){
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

};

Console GameSystem;

class World{
    private:
        string name {"estaria"};


    public:
        void prolouge(){
            string userInput;

            if (checkpoints.prolouge){
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
            checkpoints.prolouge = 1; checkpoints.kukuriUnlocked += 1;
            if (checkpoints.kukuriUnlocked == 1){writing("You have unlocked the next story",1,1); cout << endl;}

            return;
        }

        void kukuriForest(){
            int playerDeathOrigin = player.deaths, playerDeath{0};
            writing("Kukuri Forest",1,1);
            cout << endl;

            string userInput, result;

            if (checkpoints.kukuriForest){
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
            result = GameSystem.battle("goblin", "story");
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

            checkpoints.kukuriForest = 1; checkpoints.goblinCaveUnlocked += 1;
            if (checkpoints.goblinCaveUnlocked == 1){writing("You have unlocked the goblin dungeon",1,1);}
        }

};

World estaria;

void settingsInterface(){
    string stringInput;
    int userInput;

    while(true){
        bool error{false};

        cout << "               ╔═════════════════════════════╗" << endl;
        cout << "               ║          [SETTINGS]         ║" << endl;
        cout << "               ╚═════════════════════════════╝" << endl;

        cout << "╔══════════════════════════════════════════════════════════╗" << endl;
        cout << "╠ ╔════════════════════════╗     ╔══════════════════════╗  ╣" << endl;
        cout << "║  [1]-[Text Speed]: " << settings.textSpeed;  if (settings.textSpeed == "normal"){cout << setw(24);} else{cout << setw(26);}
        cout << "[2]-[AutoSave]: "<< settings.autosave ; if (settings.autosave == "off"){cout <<"     ║" << endl;} else{cout <<"      ║" << endl;} 
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
        try{userInput =  stoi(stringInput);} catch(const std::exception& e){GameSystem.errorMessage(); error = true;}
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
                    try{userInput =  stoi(stringInput);} catch(const std::exception& e){GameSystem.errorMessage(); error = true;}
                    cout << endl;

                    if (!error){
                        if (userInput == 1){settings.textSpeed = "normal"; break;}
                        else if (userInput == 2){settings.textSpeed = "fast"; break;}
                        else{GameSystem.errorMessage();}
                    }
                }
                GameSystem.settingsDoneMessage();
            }
 
            else if (userInput == 2){
                while(true){
                    error = false;
                    cout << "╔═══════════════════════╗" << endl;
                    cout << "║  [1]-[On]   [2]-[Off  ║" << endl;
                    cout << "╚═══════════════════════╝" << endl;
                    cout << "> ";
                    getline(cin, stringInput);
                    try{userInput =  stoi(stringInput);} catch(const std::exception& e){GameSystem.errorMessage(); error = true;}
                    cout << endl;

                    if (!error){
                        if (userInput == 1){settings.autosave = "on"; break;}
                        else if (userInput == 2){settings.autosave = "off"; break;}
                        else{GameSystem.errorMessage();}
                    }
                }
                GameSystem.settingsDoneMessage();
            }

            else if (userInput == 3){
                string userName;
                cout << "Input name\n"
                     << "> ";
                getline(cin, stringInput);
                for(auto chara : stringInput){if (chara == ' ' ){chara = '-';} 
                    userName += chara;}
                player.name = userName;
                GameSystem.settingsDoneMessage();
            }
 
            else if (userInput == 4){
                ofstream saveFile("save.txt");

                if(saveFile){
                    writing("Are you sure you want to delete your save file",0,1); 
                    cout << "[yes i know what i am doing] to proceed.\n";
                    cout << "> ";
                    getline(cin, stringInput);
                        if (stringInput == "yes i know what i am doing"){
                            writing("Deleting save file",0,1); writing(".",0,1); writing("..",0,1); writing("...",1,1);  
                            writing("save file deleted.",0,1); writing("return to [Main Menu] to apply changes.",1,1);
                            saveFile << 0;  saveFile << "\n";
                            saveFile.close();
                            hideSaveFile();
                        }
                        else{writing("Returning to settings....",1,1);}
                }
                else{writing("Error: Save.txt not found!",1,1); writing("Returning to settings....",1,1);}
            }
 
            else if (userInput == 0){gameSave(); break;}

            else{GameSystem.errorMessage();}

        }
        
    }
}

void storyMode(){
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
        cout << "║      [1]-Prolouge [✓]" ;if (checkpoints.kukuriForest){cout << setw(42) << "[2]-[Kukuri Forest] [✓]  ║" << endl;}
        else if (checkpoints.kukuriUnlocked && !checkpoints.kukuriForest){cout << setw(40) << "[2]-[Kukuri Forest]    ║" << endl;}
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
        try{userInput =  stoi(stringInput);} catch(const std::exception& e){GameSystem.errorMessage(); cout << '\n';error = true;}
        cout << endl;
        sleep_for(0.5s);
        if (!error){
            if (userInput == 0){GameSystem.tips();break;}
            else if (userInput == 1){estaria.prolouge(); if (settings.autosave == "on"){gameSave();} GameSystem.tips();}
            else if (userInput == 2){estaria.kukuriForest(); if (settings.autosave == "on"){gameSave();} GameSystem.tips();}
            else if (userInput == 3){GameSystem.notUnlockedMessage();}
            else if (userInput == 4){GameSystem.notUnlockedMessage();}
            else if (userInput == 5){GameSystem.notUnlockedMessage();}
            else if (userInput == 6){GameSystem.notUnlockedMessage();}
            else {GameSystem.errorMessage();}
        } 
    }
}

void battle(){
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
        try{userInput =  stoi(stringInput);} catch(const std::exception& e){GameSystem.errorMessage(); cout << '\n';error = true;}
        cout << endl;
        sleep_for(0.5s);

        if (!error){

            if (userInput == 0){GameSystem.tips();break;}

            else if (userInput == 1){
                GameSystem.tips();
                while (true){
                    error = false;

                    cout << "                  ╔════════════════════════════╗" << endl;
                    cout << "                  ║          [DUNGEON]         ║" << endl;
                    cout << "                  ╚════════════════════════════╝" << endl;
                    
                    cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
                    cout << "╠ ╔═══════════════════════════╗     ╔═════════════════════════╗ ╣" << endl;
                    if (checkpoints.goblinCave){cout << "║   [1]-[The Goblin Cave] [✓] ";} 
                    else if (checkpoints.goblinCaveUnlocked && !checkpoints.goblinCave){cout << "║     [1]-[The Goblin Cave]   ";}
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
                    try{userInput =  stoi(stringInput);} catch(const std::exception& e){GameSystem.errorMessage(); cout << '\n';error = true;}
                    cout << endl;
                    sleep_for(0.5s);

                    if (!error){
                        if (userInput == 1){
                            if (checkpoints.goblinCaveUnlocked){GameSystem.dungeon("goblin");if (settings.autosave == "on"){gameSave();} 
                            GameSystem.tips();}
                            else{GameSystem.notUnlockedMessage();}
                        }
                    
                        else if (userInput == 2){writing("other dungeons are still being worked on",1,1);}
                        
                        else if (userInput == 3){writing("other dungeons are still being worked on",1,1);}

                        else if (userInput == 4){writing("other dungeons are still being worked on",1,1);}

                        else if (userInput == 0){GameSystem.tips();break;}

                        else{GameSystem.errorMessage();}
                    }
                }
            }
        
            else if (userInput == 2){
                GameSystem.tips();
                while (true){
                    error = false;

                    cout << "                   ╔═════════════════════════╗" << endl;
                    cout << "                   ║          [BOSS]         ║" << endl;
                    cout << "                   ╚═════════════════════════╝" << endl;

                    cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
                    cout << "╠ ╔═══════════════════════════╗     ╔═════════════════════════╗ ╣" << endl;
                    if (checkpoints.goblinBoss){cout << "║   [1]-[The Goblin King] [✓] ";} 
                    else if (checkpoints.goblinBossUnlocked && !checkpoints.goblinBoss){cout << "║     [1]-[The Goblin King]   ";}
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
                    try{userInput =  stoi(stringInput);} catch(const std::exception& e){GameSystem.errorMessage(); cout << '\n';error = true;}
                    cout << endl;
                    sleep_for(0.5s);

                    if (!error){
                        if (userInput == 1){
                            if (checkpoints.goblinBossUnlocked){
                                stringInput = GameSystem.bossWarning("goblin");
                                if (stringInput == "y" || stringInput == "yes"){GameSystem.battle("goblinboss", "boss");
                                if (settings.autosave == "on"){gameSave();} GameSystem.tips();}
                                else{cout << player.name; writing(" flees",1,1);}
                            }
                            else{GameSystem.notUnlockedMessage();}
                        }
                    
                        else if (userInput == 2){writing("other bosses are still being worked on",1,1);}
                        
                        else if (userInput == 3){writing("other bosses are still being worked on",1,1);}

                        else if (userInput == 4){writing("other bosses are still being worked on",1,1);}

                        else if (userInput == 0){GameSystem.tips();break;}

                        else{GameSystem.errorMessage();}
                    }
                }
            }

            else if (userInput == 3){player.inventory(""); if (settings.autosave == "on"){gameSave();} GameSystem.tips();}

            else if (userInput == 4){player.status();GameSystem.tips();}

            else if (userInput == 5){GameSystem.shop(); if (settings.autosave == "on"){gameSave();} GameSystem.tips();}

            else {GameSystem.errorMessage();}
        }
    }
}


int main (){ 
    SetConsoleOutputCP(CP_UTF8);
    {

 {
    cout << endl;
    writing("Booting up.....",1,1);
    cout << endl;

    string stringinput;
    int userInput;
    bool error{false};
    

    while (true){
        error = false;

        cout << "╔═══════════════════════════════════════╗" << endl;
        cout << "╠              ╔═════════╗              ╣" << endl;
        cout << "║               [Estaria]               ║" << endl;
        cout << "╠              ╚═════════╝              ╣" << endl;
        cout << "╚═══════════════════════════════════════╝" << endl;


        cout << "╔═══════════════════════════════════════╗" << endl;
        cout << "╠ ╔══════════════╗     ╔══════════════╗ ╣" << endl;
        cout << "║  [1]-[New Game]       [2]-[Continue]  ║" << endl;
        cout << "╠ ╚══════════════╝     ╚══════════════╝ ╣" << endl;
        cout << "╠ ╔══════════════╗     ╔══════════════╗ ╣" << endl;
        cout << "║  [3]-[Credits]         [99]-[Quit]    ║" << endl;
        cout << "╠ ╚══════════════╝     ╚══════════════╝ ╣" << endl;
        cout << "╚═══════════════════════════════════════╝" << endl;
        cout << "> ";
        getline(cin, stringinput);
        try{userInput =  stoi(stringinput);} catch(const std::exception& e){GameSystem.errorMessage(); cout << '\n';error = true;}
        cout << endl;
        if (!error){

            if (userInput == 2){gameContinue();
             userInput = 1;}

            if (userInput == 1){
                if (!checkpoints.prolouge){estaria.prolouge(); GameSystem.tips();}
            sleep_for(0.5s);

                while(true){
                    error = false;

                    cout << "        ╔══════════════════════════╗" << endl;
                    cout << "        ║          [HOME]          ║" << endl;
                    cout << "        ╚══════════════════════════╝" << endl;

                    cout << "╔═══════════════════════════════════════════╗" << endl;
                    cout << "╠ ╔════════════════╗     ╔════════════════╗ ╣" << endl;
                    cout << "║  [1]-[Story Mode]         [2]-[Battle]    ║" << endl;
                    cout << "╠ ╚════════════════╝     ╚════════════════╝ ╣" << endl;
                    cout << "╠ ╔════════════════╗     ╔════════════════╗ ╣" << endl;
                    cout << "║   [3]-[Progress]           [4]-[Save]     ║" << endl;
                    cout << "╠ ╚════════════════╝     ╚════════════════╝ ╣" << endl;
                    cout << "╠ ╔════════════════╗     ╔════════════════╗ ╣" << endl;
                    cout << "║   [5]-[Settings]        [0]-[Main Menu]   ║" << endl;
                    cout << "╠ ╚════════════════╝     ╚════════════════╝ ╣" << endl;
                    cout << "╠             ╔════════════════╗            ╣" << endl;
                    cout << "║                [99]-[Quit]                ║" << endl;
                    cout << "╠             ╚════════════════╝            ╣" << endl;
                    cout << "╚═══════════════════════════════════════════╝" << endl;

                    cout << "> ";
                    getline(cin, stringinput);
                    try{userInput =  stoi(stringinput);} catch(const std::exception& e){GameSystem.errorMessage(); cout << '\n';error = true;}
                    cout << endl;
                    sleep_for(0.5s);

                    if (!error){

                        if (userInput == 1){GameSystem.tips();storyMode();}

                        else if (userInput == 2){GameSystem.tips();battle();}
                        
                        else if (userInput == 3){writing("Progress is still being worked on.",1,1);}

                        else if (userInput == 4){gameSave();GameSystem.tips();}

                        else if (userInput == 5){settingsInterface(); GameSystem.tips();}

                        else if (userInput == 0){GameSystem.tips();break;}

                        else if (userInput == 99){ writing("Good Bye!",1,1); return 0;}

                        else {GameSystem.errorMessage();}
                    }
                }
            }

            else if (userInput == 3){writing("credits are still being worked on",1,1);}

            else if (userInput == 99){writing("Good Bye!",1,1);return 0;}

            else{GameSystem.errorMessage();}

        }
        
    }

    }  
} 
   
        // cout << "╔══════════════════════════════════╗" << endl;
        // cout << "╠ ╔═══════════╗     ╔════════════╗ ╣" << endl;
        // cout << "║  [1]-[Fight]       [2]-[Defend]  ║" << endl;
        // cout << "╠ ╚═══════════╝     ╚════════════╝ ╣" << endl;
        // cout << "╠ ╔═══════════╗     ╔════════════╗ ╣" << endl;
        // cout << "║  [3]-[Items]       [4]-[status]  ║" << endl;
        // cout << "╠ ╚═══════════╝     ╚════════════╝ ╣" << endl;
        // cout << "╠           ╔═════════╗            ╣" << endl;
        // cout << "║            [0]-[Run]             ║" << endl;
        // cout << "╠           ╚═════════╝            ╣" << endl;
        // cout << "╚══════════════════════════════════╝" << endl;


        // cout << "                   ╔═════════════════════════╗" << endl;
        // cout << "                   ║          [BOSS]         ║" << endl;
        // cout << "                   ╚═════════════════════════╝" << endl;

        // cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
        // cout << "╠ ╔═══════════════════════════╗     ╔═════════════════════════╗ ╣" << endl;
        // if (checkpoints.goblinBoss){cout << "║   [1]-[The Goblin King] [✓] ";} 
        // else if (checkpoints.goblinBossUnlocked && !checkpoints.goblinBoss){cout << "║     [1]-[The Goblin King]   ";}
        // else{cout << "║  [-]-[---------------------]";}
        // cout << setw(37) << "[-]-[-------------------]  ║" << endl;
        // cout << "╠ ╚═══════════════════════════╝     ╚═════════════════════════╝ ╣" << endl;
        // cout << "╠ ╔═══════════════════════════╗     ╔═════════════════════════╗ ╣" << endl;
        // cout << "║  [-]-[---------------------]       [-]-[-------------------]  ║" << endl;
        // cout << "╠ ╚═══════════════════════════╝     ╚═════════════════════════╝ ╣" << endl;
        // cout << "╠                          ╔══════════╗                         ╣" << endl;
        // cout << "║                           [0]-[Back]                          ║" << endl;
        // cout << "╠                          ╚══════════╝                         ╣" << endl;
        // cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;

    // cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    // cout << "║"; writing(" You win. but the victory was short lived, the goblins caught up",0,0); ;cout << "                                      ║\n"; sleep_for(0.3s);
    // cout << "║"; writing(" You are surrounded with no way to escape.",0,0); ;cout << "                                                            ║\n"; sleep_for(0.3s);
    // cout << "║                                                                                                      ║\n"; sleep_for(0.5s);
    // cout << "║"; writing(" Suddenly, you hear a battle cry, people appear one by one to attack the goblins.",0,0); ;cout << "                     ║\n"; sleep_for(0.3s);
    // cout << "║                                                                                                      ║\n";
    // cout << "║"; writing(" [Grumpy Man]: which cunt decided it was a good idea to go around rifling all the goblins?!",0,0); ;cout << "           ║\n"; sleep_for(0.3s);
    // cout << "║"; writing("               i only came here to farm a bit for some wine money and now we got work to do?!.",0,0); ;cout << "        ║\n"; sleep_for(0.3s);
    // cout << "║"; writing("               oi kahn, emily,",0,0); writing(" let's get this over with quickly!.",0,0);cout << "                                     ║\n"; sleep_for(0.3s);
    // cout << "║"; writing(" [Kahn]:       Alright, alright gustave. you know you don't always have to be grumpy right emi?",0,0); ;cout << "       ║\n"; sleep_for(0.3s);
    // cout << "║"; writing(" [Emily]:      Exactly!, that's why he's sooo bald :P.",0,0); ;cout << "                                                ║\n"; sleep_for(0.3s);
    // cout << "║"; writing("               oh, someones there, you still alive? whats your name?.",0,0); ;cout << "                                 ║\n"; sleep_for(0.3s);
    // cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";


    // goblinBoss.status();
    // estaria.boss("goblin");

    // GameSystem.battle("goblinboss", "boss");
    // goblinDungeon.stats();
    // player.inventory("");
    

     return 0;

}
