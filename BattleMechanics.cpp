#include <thread>
#include <fstream>
#include <chrono>
#include <cmath>
#include <ctime>
#include "GameSystem.h"
#include "Player.h"
#include "Mobs.h"
#include "Dungeon.h"
#include "Boss.h"


using namespace std;

using namespace this_thread;
using namespace chrono_literals;
using std::chrono::system_clock;


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

string fight(string mob, string type){
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
        try{userInput =  stoi(stringInput);} catch(const std::exception& e){estariaSystem::errorMessage(); cout << '\n';error = true;}
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

            else{estariaSystem::errorMessage(); rounds--; result = "idle";}

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

        if (boss == "goblin"){goblinBoss.completed++; checkpoints::goblinBoss == 1; 
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

            if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = fight("goblin", "dungeon");}
        }
        else if (waves > 4 && waves <= 6){
            rngVariance = 9;
            srand(time(nullptr));
            mobLevel = rand() % rngVariance + 1;
            if (mobLevel <= 6){mobLevel = 6;}

            if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = fight("goblin", "dungeon");}
        }
        else if (waves > 6 && waves <= 8){
            rngVariance = 14;
            srand(time(nullptr));
            mobLevel = rand() % rngVariance + 1;
            if (mobLevel <= 10){mobLevel = 10;}

            if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = fight("goblin", "dungeon");}
        }
        else if (waves > 8 ){
            rngVariance = 20;
            srand(time(nullptr));
            mobLevel = rand() % rngVariance + 1;
            if (mobLevel <= 15){mobLevel = 15;}

            if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = fight("goblin", "dungeon");}
        }
        else{
            rngVariance = 2;
            srand(time(nullptr));
            mobLevel = rand() % rngVariance + 1;
            if (mobLevel < 1){mobLevel = 1;}

            if (dungeonName == "goblin"){goblin.mobLevel(mobLevel);result = fight("goblin", "dungeon");}
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
        if (mobname == "goblin"){goblinDungeon.completed += 1; checkpoints::goblinBossUnlocked = 1;
            checkpoints::goblinCave = 1; if (goblinDungeon.progress < 10){goblinDungeon.progress = waves;}
            if (checkpoints::goblinBossUnlocked == 1){writing("You have unlocked the Goblin Boss Area!",1,1); cout << endl;}
        }
    }
    else if (result == "death"){
        if (mobname == "goblin"){goblinDungeon.deaths++; if (goblinDungeon.progress < 10){goblinDungeon.progress = waves;}}

    }
    else if (result == "flee"){
        if (mobname == "goblin"){if (goblinDungeon.progress < 10){goblinDungeon.progress = waves;}}
    }
    


}

