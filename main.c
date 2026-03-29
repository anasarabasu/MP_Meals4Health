/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I have
constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and

debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons, nor did I employ the use of AI in any part of the deliverable.

                Ashana Rivera Monsanto, DLSU ID# 12505951
*********************************************************************************************************/




#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>


#define TOP printf("\e[H");
#define CURSOR_POS printf("\e[999;0H");
#define CLEAN printf("\e[0J");

#define RESET "\e[0m"
#define BLINK "\e[5m"
#define GRY "\e[1;30m"
#define RED "\e[31m"
#define GRN "\e[32m"
#define YLW "\e[33m"
#define PRP "\e[35m"

#define LINE "==========================================================================================================================\n"
#define LINE2 " ------------------------------------------------------------------------------------------------------------------------\n"
#define LINE3 " --------------------------------------------------------------------------\n"




struct ingredientStruct {
    char item[21];
    float quantity;
    char unit[16];
    float calories;
};
typedef struct ingredientStruct ingredient;

struct recipeStruct {
    char name[21];
    char classification[8];

    ingredient ingredients[20];
    int ingredientCount;

    char steps[15][71];
    int stepCount;

    int servings;
};
typedef struct recipeStruct recipe;




// HELPERS -----------------------------------------------------------------------------------------

typedef char string[90];

#define INPUT_ENTER (input == '\r')
#define INPUT_EXIT (input == 'x' || input == 'X')


// Resets the selection when it exceeds the range
//
// @param SELCTED - the current option index selected
// @param MAX - the total number of options
//
// @RETURN the in-range selection index
//
int selectionLooper(int SELECTED, int MAX) {
    int selected = SELECTED;
    if(SELECTED < 0) selected = MAX;
    if(SELECTED > MAX) selected = 0;

    return selected;
}




// Increments the selected index according only to the arrow key input type
//
// @param INPUT - the character returned from the input call
// @param *SELECTED - pointer to the selected index
// @param DIRECTION - determines if navigation goes vertically or horizontally
//
void navigation(char INPUT, int *SELECTED, char DIRECTION) {
    switch(INPUT) {
        case 72: // up
            if(DIRECTION == 'y') (*SELECTED)--;
            break;
        case 80: // down
            if(DIRECTION == 'y') (*SELECTED)++;
            break;
        case 77: // right
            if(DIRECTION == 'x') (*SELECTED)++;
            break;
        case 75: // left
            if(DIRECTION == 'x') (*SELECTED)--;
            break;
    }
}




// Consumes excess characters to avoid overflow error or input buffer leaking to the next scanf
void clearBuffer() {
    scanf("%*[^\n]"); 
    getchar();
}

// Handles all scanf events for strings
// Ensures that the string input contains atleast 1 character that's not a whitespace
// TOPs up trailing whitespaces
// Also moves the cursor to last position to prevent the empty newline with enter keys
//
// @param STRING - address where string input is stored
// @param IDENTIFIER - specified length of string termination + string scanset
// @param POS - cursor offset
//
// @RETURN true if input contains atleast a non-whitespace character
//
int getStringInput(char * STRING, char * IDENTIFIER, char * POS) {
    int isValid = 0;

    strcpy(STRING, ""); // resets input
    scanf(IDENTIFIER, STRING);

    int length = strlen(STRING);
    if(length > 0) {
        // remove left-hand spaces
        int index;
        for(index = 0; STRING[index] == ' '; index++);

        int offset;
        for(offset = 0; STRING[offset + index] != '\0'; offset++) 
            STRING[offset] = STRING[offset + index];

        STRING[offset] = '\0';

        // remove right-hand spaces
        for(index = length-1; STRING[index] == ' '; index--);
        STRING[index + 1] = '\0';
        
        // validate not empty
        length = strlen(STRING);
        if(length) isValid = 1;
    }

    if(!isValid) {
        clearBuffer();

        printf(POS); // moves cursor back to previous position using escape characters
        isValid = getStringInput(STRING, IDENTIFIER, POS);
    }
    scanf("%*[^\n]"); 

    return isValid;
}




// Handles all numerical input
// Validates input as integer or float
//
// @param NUM - address where int input is stored
// @param POS - cursor offset
// @param ZERO_INC - determines whether zero inclusive or exclusive
// @param IS_INT - determines if int data type
//
// @RETURN true if input is of valid numerical value
//
int getNumInput(float *NUM, char *POS, int ZERO_INC, int IS_INT) {
    int isValid = 1;

    char ch = getchar();
    while(ch == '\n' || ch == ' ') {
        // moves cursor back to previous position using escape characters
        if(ch == '\n') printf("\e[1F%s", POS);
        if(ch == ' ') printf(POS); 

        ch = getchar();
    }
    ungetc(ch, stdin); // puts back the char to the input stream

    *NUM = 0;
    char garbage[1] = {'\0'};

    if(IS_INT) {
        int integer;
        isValid = scanf("%d%1[^\n]s", &integer, garbage) && (garbage[0] == '\0' || garbage[0] == '\r');
        *NUM = integer;

        if(!isValid) { // checks for valid int input
            clearBuffer();

            printf("\e[1F\e[0J\e[20G\t\t" RED "[!] Please enter only whole numbers%s" RESET, POS);
            isValid = getNumInput(NUM, POS, ZERO_INC, IS_INT);
        }
    }
    else {
        isValid = scanf("%f%1[^\n]s", NUM, garbage) && (garbage[0] == '\0' || garbage[0] == '\r');

        if(!isValid) { // checks for valid float input
            clearBuffer();

            printf("\e[1F\e[0J\e[20G\t\t" RED "[!] Please enter only valid numerical values%s" RESET, POS);
            isValid = getNumInput(NUM, POS, ZERO_INC, IS_INT);
        }
    }

    if((!ZERO_INC && *NUM <= 0) || *NUM < 0) {
        clearBuffer();

        printf("\e[1F\e[0J\e[20G\t\t" RED "[!] Please enter a valid amount%s" RESET, POS);
        isValid = getNumInput(NUM, POS, ZERO_INC, IS_INT);
    }

    printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment

    return isValid;
}

// Converts to proper data type
void getIntInput(int *NUM, char *POS, int ZERO_INC, int IS_INT) {
        float temp;
        getNumInput(&temp, "\e[5G" RESET, ZERO_INC, IS_INT);
        *NUM = (int)temp;
}




// Checks if file exists
//
// @PARAM FILENAME - where the file name input is store
// @PARAM SAVE - guard for the load / save function
// 
// RETURN 0 file doesnt exist // RETURN 1 file exists then proceed  // RETURN -1 file exists but cancel
// 
int checkFileExists(char FILENAME[21], int SAVE) { // 0 load // 1 save
    printf(YLW"    File Name: \n    " RESET);
    getStringInput(FILENAME, "%17[^\n]s", "\e[1F\e[5G");
    strcat(FILENAME, ".txt");
    clearBuffer();

    int proceed = 1;
    char input;

    FILE *file;
    if((file = fopen(FILENAME, "r"))) { // checks if file exists
        printf("\n    File exists, continue?" GRY "  [ Y / N ]\n" RESET);
        
        input = getch();
        input = toupper(input);
        while(input != 'N' && input != 'Y') {
            input = getch();
            input = toupper(input);
        }

        if(input == 'N') {
            printf(GRY "    * Action cancelled\n\n" RESET);
            proceed = 0;
        }

        fclose(file);
    }
    else {
        if(!SAVE) {
            printf(
                RED "\n    File doesn't exist, exit?" GRY "  [ Y / N ]\n" RESET
            );
            
            input = getch();
            input = toupper(input);
            while(input != 'N' && input != 'Y') {
                input = getch();
                input = toupper(input);
            }
            
            if(input == 'Y') {
                printf(GRY "    * Action cancelled\n\n" RESET);
                proceed = 0;
            }
            else {
                printf("\e[1F\e[0J");
                proceed = checkFileExists(FILENAME, SAVE);
            }
        }
    }


    return proceed;
}




// Finds the ratio between the base and new values and applies it to a given number
// 
// @PARAM QUANTITY - amount to be recalculated
// @PARAM ORIGINAL - base unit
// @PARAM NEW - specified unit
// 
// RETURN the new amount // RETURN 0 if ORIGINAL is 0
//
double calculateNewAmount(float QUANTITY, float ORIGINAL, float NEW) {
    float new = 0;

    if(ORIGINAL) new = round(QUANTITY * (NEW / ORIGINAL) * 100) / 100;

    return new;
}

// Adds all recalculated calorie amount together
//
// @PARAM RECIPE - item to parse info from
// @PARAM CALORIE - calorie info guide
// @PARAM C_ELEM - total elements in CALORIE
//
// RETURN the total calories
//
float addCalories(recipe *RECIPE, ingredient CALORIE[], int C_ELEM) {
    float calories = 0;

    int ingredientIndex;
    for(ingredientIndex = 0; ingredientIndex < RECIPE->ingredientCount; ingredientIndex++) {
        RECIPE->ingredients[ingredientIndex].calories = 0;

        int calorieIndex;
        for(calorieIndex = 0; calorieIndex < C_ELEM; calorieIndex++) {

            if(!strcmp(CALORIE[calorieIndex].item, RECIPE->ingredients[ingredientIndex].item))
                RECIPE->ingredients[ingredientIndex].calories = calculateNewAmount(CALORIE[calorieIndex].calories, CALORIE[calorieIndex].quantity, RECIPE->ingredients[ingredientIndex].quantity);
        }

        calories += RECIPE->ingredients[ingredientIndex].calories;
    }
    
    return calories;
}




// DISPLAY -----------------------------------------------------------------------------------------


// Handles the rotating menu options display
//
// @param SELECTED - index of currently selected option
// @param MAX - total total number of options to choose from
// @param OPTIONS - string array of options to be displayed
void selectionCarousel(int SELECTED, int MAX, string OPTIONS[], char * COLOUR) {
    int selectionDisplayIndex;

    for(selectionDisplayIndex = 0; selectionDisplayIndex != MAX; selectionDisplayIndex++) {
        if(SELECTED == selectionDisplayIndex) {
            if(SELECTED == MAX - 1) printf(RED " >>> " BLINK);
            else printf("%s >>> " BLINK, COLOUR);
        }
        else printf("    ");

        printf("%s\n" RESET, OPTIONS[selectionDisplayIndex]);
    }
}

// Refocuses display
void moveDisplay() {
    CURSOR_POS
    printf(" ");

    int space; 
    for(space = 0; space <= 64; space++) printf("\n");

    TOP
    CLEAN
}

void confirmBack() {
    CURSOR_POS
    char input = getch();
    while(!INPUT_EXIT) 
        input = getch();
}

// Random number generator
//
// @PARAM RANGE - determines the range of numbers to pick from
//
// RETURN a random int within a given range
int rng(int RANGE) {
    int random = rand() % RANGE;
    return random;
}

#include "recipes.c"
#include "cal.c"
#include "access.c"
#include "menus.c"

int main() {
	srand(time(NULL)); // fixes persistent rand and makes it random for each session
    system("cls");
    menuSwitch();
    printf(" >>> Program terminated\n");

    return 0;
}