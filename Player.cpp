#include "Player.h"
#include "GameSystem.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;

using namespace this_thread;
using namespace chrono_literals;
using std::chrono::system_clock;

int Player::Level{1};
string Player::name {"player"};
int Player::experience{0};
int Player::maxExp{100};
double Player::health{100};
double Player::maxHp {100};
double Player::attack {10};
double Player::defence {10};
int Player::dexterity {1};
int Player::dodge {1};
int Player::money{1000};
string Player::debuff{"none"};
int Player::debuffBuildUp{0};
int Player::deaths {0};

int Player::status(){

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

int Player::potion {1};
int Player::greaterPotion {0};
int Player::antidote{0};

int Player::inventory(string type){
            
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
        
void Player::exp(int expGained, int moneyGained){

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

void Player::die(){
    if (Level > 1){
    Level -= 1; maxHp -= 5; attack -= 5; defence -=5; dodge -= 1; dexterity -= 1; deaths += 1; experience = 0;
    }
    else{deaths += 1;}
}

Player player;