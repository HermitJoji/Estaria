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
        try{userInput =  stoi(stringinput);} catch(const std::exception& e){estariaSystem::errorMessage; cout << '\n';error = true;}
        cout << endl;
        if (!error){

            if (userInput == 2){saveSystem::gameContinue();
             userInput = 1;}

            if (userInput == 1){
                if (!checkpoints::prolouge){story::prolouge(); estariaSystem::tips();}
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
                    try{userInput =  stoi(stringinput);} catch(const std::exception& e){estariaSystem::errorMessage; cout << '\n';error = true;}
                    cout << endl;
                    sleep_for(0.5s);

                    if (!error){

                        if (userInput == 1){estariaSystem::tips();consoleAction::storyMode();}

                        else if (userInput == 2){estariaSystem::tips();consoleAction::battle();}
                        
                        else if (userInput == 3){writing("Progress is still being worked on.",1,1);}

                        else if (userInput == 4){saveSystem::gameSave();estariaSystem::tips();}

                        else if (userInput == 5){consoleAction::settingsInterface(); estariaSystem::tips();}

                        else if (userInput == 0){estariaSystem::tips();break;}

                        else if (userInput == 99){ writing("Good Bye!",1,1); return 0;}

                        else {estariaSystem::errorMessage;}
                    }
                }
            }

            else if (userInput == 3){writing("credits are still being worked on",1,1);}

            else if (userInput == 99){writing("Good Bye!",1,1);return 0;}

            else{estariaSystem::errorMessage;}

        }
        
    }
    }  
} 
     return 0;

}
