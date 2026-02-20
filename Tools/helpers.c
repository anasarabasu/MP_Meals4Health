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
    char * classification;

    ingredient ingredients[20];
    char steps[15][70];
    int servings;
};
typedef struct recipeStruct recipe;

#define sleep(seconds) Sleep((seconds)*1000)

#define INPUT_EXIT (input == 'x' || input == 'X')
#define INPUT_ENTER (input == '\r')


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
// Also moves the cursor to last position to prevent the empty newline with enter keys
//
// @param STRING - address where string input is stored
// @param IDENTIFIER - specified length of string termination + string scanset
// @param POS
void getStringInput(char * STRING, char * IDENTIFIER, char * POS) {
    scanf(IDENTIFIER, STRING);

    int isValid = 0;
    while(!isValid) {
        int length = strlen(STRING);
        if(length > 0) {
            int index;
            for(index = length; index != 0; index--) {
                if(STRING[index] != ' ') isValid = 1;
                else STRING[index] = '\0';
            }

        }

        if(!isValid) {
            clearBuffer();

            printf(POS); // moves cursor back to previous position using escape characters
            scanf(IDENTIFIER, STRING);
        }
    }
    clearBuffer();
}