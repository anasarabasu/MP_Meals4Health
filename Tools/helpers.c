typedef char string[30];


struct ingredientStruct {
    char item[20];
    float quantity;
    char unit[15];
    float calories;
};
typedef struct ingredientStruct ingredient;


struct recipeStruct {
    char name[20];
    enum classification {
        Starter,
        Main,
        Dessert
    }

    ingredients[20];
    char instructions[15][70];
    int servings;
};
typedef struct recipeStruct recipe;


#if !defined(_WIN32) || !defined(_WIN64)
    // linux replacement for the windows function of getch()
    char getch() { 
        system("stty -icanon -echo");
        char key = getchar();
        system("stty icanon echo");

        return key;
    }
#endif


void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64) 
        system("cls");
    #else 
        system("clear");
    #endif
}


int selectionLooper(int SELECTED, int MAX) {
    int selected = SELECTED;

    if(SELECTED < 0) 
        selected = MAX;
    if(SELECTED > MAX) 
        selected = 0;

    return selected;
}

void navigation(char INPUT, int *SELECTED) {
    if(INPUT == '\e') {
        getch(); // removes the ^[[

        switch(getch()) { // retrieves only the unique identifiers of each arrow direction
            case 'A': // up
                (*SELECTED)--;
                break;
            case 'B': // down
                (*SELECTED)++;
                break;
            case 'C':// right
                break;
            case 'D': // left
                break;
        }
    }
}


// Checks if input string is empty "\n" or contains only spaces
// @RETURN 0 if found empty or pure spaces & RETURN 1 if contains alphanumerical characters
int validateString(char * STRING) {
    int isValid = 0;

    if(strlen(STRING) > 0) {
        int index = 0;
        while(index != strlen(STRING) && !isValid) {
            if(STRING[index] != ' ')
                isValid = 1;
            
            index++;
        }
    }

    if(!isValid) {
        getch(); // consumes the \n to prevent an infinite loop
        strcpy(STRING, "\0");
    }

    return isValid;
}

// Handles all scanf events for strings
// Also moves the cursor to last position to prevent the ugly newline that scanf results in with empty inputs
// @param STRING - address where string input is stored
// @param IDENTIFIER - specified length of string termination + string scanset
// @param POS
void getStringInput(char * STRING, char * IDENTIFIER, char * POS) {
    scanf(IDENTIFIER, STRING);

    while(!validateString(STRING)) {
        printf(POS); // moves cursor back to previous position using escape characters
        scanf(IDENTIFIER, STRING);
    }

    char ch = getch();
    while(ch != '\n') // Consumes excess characters to avoid possible overflow error
        ch = getch();
}


// void getFloatInput(float *FLOAT) {}