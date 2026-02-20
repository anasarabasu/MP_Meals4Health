/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I have
constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and

debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons, nor did I employ the use of AI in any part of the deliverable.

                Ashana Rivera Monsanto, DLSU ID# 12505951
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "Tools/helpers.c"
#include "Tools/display.c"

#include "Sections/mainMenu.c"

#include "Sections/update/ingredientFunctions.c"
#include "Sections/update/calInfoFunctions.c"
#include "Sections/update/recipeFunctions.c"
#include "Sections/update/updateMenu.c"

int main() {
    SetConsoleOutputCP(65001); // allows displaying of UNICODE characters

    ingredient food[50];
    int fElem = 0;

    recipe recipes[50];
    int rElem = 0;

    int mode = -1;
    mode = 0;
    while(mode != -2) { // program loop
        switch(mode) { 
            case -1: 
                mode = mainMenu();
                break;
            case 0: {
                // mode = logIn();

                int option;
                if(mode == 0) option = updateMenu();
                if(option == -1) mode = -1;

                updateFuncSwitch(option, food, &fElem, recipes, &rElem);
                break;
            }
            
            case 1:
                printf("Access recipe unimplemented\n");
                mode = 0;
                break;
            default: 
                printf(" >>> Program stuck in a loop");
                getch();
            break;
        }
        
        WIPE
    }

    printf(" >>> Program terminated\n");

    return 0;
}

/*
MISC

[ ] ascii text art
[ ] split view - view a pic? and brief description of each option
[ ] add button noises

*/