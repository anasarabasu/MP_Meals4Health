typedef char string[30];

struct ingredientStruct {
    char item[21];
    int quantity;
    char unit[16];
    int calories;
};
typedef struct ingredientStruct ingredient;

struct recipeStruct {
    char name[21];
    char * classification;

    ingredient ingredients[20];
    int ingredientCount;

    char steps[15][71];
    int stepCount;

    int servings;
};
typedef struct recipeStruct recipe;

#define sleep(seconds) Sleep((seconds)*1000)

#define INPUT_ENTER (input == '\r')
#define INPUT_EXIT (input == 'x' || input == 'X')


enum calInfoOptions {
    ADD_CAL,
    VIEW_CAL,
    SAVE_CAL,
    LOAD_CAL,

    ADD_REC,
    MOD_REC,
    DEL_REC,
    LIST_REC,
    SCAN_REC,
    SEARCH_REC,
    EXPORT_REC,
    IMPORT_REC
};


// Resets the selection when it exceeds the range
//
// @param SELCTED - the current option index selected
// @param MAX - the total number of options
//
// @RETURN the in-range selection index
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
// CLeans up trailing whitespaces
// Also moves the cursor to last position to prevent the empty newline with enter keys
//
// @param STRING - address where string input is stored
// @param IDENTIFIER - specified length of string termination + string scanset
// @param POS - cursor offset
//
// @RETURN true if input contains atleast a non-whitespace character
int getStringInput(char * STRING, char * IDENTIFIER, char * POS) {
    int isValid = 0;

    strcpy(STRING, ""); // resets input
    scanf(IDENTIFIER, STRING);

    int length = strlen(STRING);
    if(length > 0) {
        // remove left-hand spaces
        int index = 0;
        while(STRING[index] == ' ') index++;

        int offset = 0;
        while(STRING[offset + index] != '\0') {
            STRING[offset] = STRING[offset + index];
            offset++;
        }
        STRING[offset] = '\0';

        // remove right-hand spaces
        index = length - 1;
        while(STRING[index] == ' ') index--;
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

    return isValid;
}

// Handles all integer input
// Validates input as integer
//
// @param INTEGER - address where int input is stored
// @param POS - cursor offset
//
// @RETURN true if input is of numerical value
int getIntInput(int * INTEGER, char * POS) {
    int isValid = 1;

    char ch = getchar();
    while(ch == '\n' || ch == ' ') {
        // moves cursor back to previous position using escape characters
        if(ch == '\n') printf("\e[1F%s", POS);
        if(ch == ' ') printf(POS); 
        ch = getchar();
    }
    ungetc(ch, stdin); // puts back the char to the input stream

    *INTEGER = 0;
    char *garbage;

    isValid = (scanf("%d%[^\n]s", INTEGER, garbage));

    int index = 0;
    int max = strlen(garbage);
    while(max && index < max) {
        if(garbage[index] != ' ') isValid = 0;
        index++;
    }

    if(!isValid) { // checks for valid int input
        clearBuffer();

        printf("\e[1F\e[0J\e[20G\t\t" RED "[!] Please enter only numerical values%s" RESET, POS);
        isValid = getIntInput(INTEGER, POS);
    }
    printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment

    return isValid;
}