/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I have
constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and

debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons, nor did I employ the use of AI in any part of the deliverable.

                Ashana Rivera Monsanto, DLSU ID# 12505951
*********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//this is here for cross compatibility testing because i'm on linux :)
#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>

    #include <windows.h>
    #define sleep(seconds) Sleep((seconds)*1000)

#else 

    #include <unistd.h>
    #define sleep(seconds) sleep(seconds)

#endif

#include "Tools/helpers.c"
#include "Tools/display.c"

#include "Sections/mainMenu.c"

#include "Sections/update/ingredientFunctions.c"
#include "Sections/update/calInfoFunctions.c"
#include "Sections/update/recipeFunctions.c"
#include "Sections/update/updateMenu.c"

int main() {
    recipe recipes[50];
    ingredient food[50];
    // int state = -1;
    int state = 0;

    while(state != -2) { // program loop
        switch(state) { 
            case -1: 
                state = mainMenu();
                break;
            case 0: {
                state = logIn();

                int func;
                if(state == 0)
                    func = updateMenu(&state);

                func = 0;
                updateFuncSwitch(func, food,  recipes);
                break;
            }
            
            case 1:
                printf("Access recipe unimplemented\n");
                state = 0;
                break;
            default: 
                printf(" >>> Program stuck in a loop");
                getch();
            break;
        }
        
        clearScreen();
    }

    printf(" >>> Program terminated\n");
    sleep(1);

    return 0;
}

/*
MISC

[ ] ascii text art
[ ] split view - view a pic? and brief description of each option
[ ] add button noises

*/