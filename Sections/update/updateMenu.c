// Asks and validates the log-in credentials
// @RETURNS 0 if log-in details are valid RETURNS -1 if not, matching the state indices
int logIn() {
    logInDisplay();

    char userName[7];
    printf(YLW "    Username: " RESET);
    getStringInput(userName, "%[^\n]6s", "\e[1F\e[15G");

    char pass[8];
    printf(YLW "    Password: " RESET);
    getStringInput(pass, "%[^\n]7s", "\e[1F\e[15G");

    int isValid = 0;
    if(strcmp(userName, "admin") || strcmp(pass, "ad1234")) {
        printf(
            "\n"            
            RED " [!] Invalid username or password entered\n" 
            GRY " >>> Returning back to main menu\n" 
            RESET
        );
        
        isValid = -1;
    }

    else {
        printf(
            "\n"
            GRN " [O] User validated!\n"
            GRY " >>> Proceeding to update mode\n"
            RESET
        );
    }

    delayedLoad();   

    return isValid;
}

// 
// @param *STATE - address that determines the current state and displayed screen
int updateMenu(int *STATE) {
    int selected = 0;
    char input = '\0';
    
    string options[13] = {
        /* 00 */ "Add Food-Calorie Info",
        /* 01 */ "View Food-Calorie Chart",
        /* 02 */ "Save Calorie Info",
        /* 03 */ "Load Calorie Info\n",

        /* 04 */ "Add Recipe",
        /* 05 */ "Modify Recipe",
        /* 06 */ "Delete Recipe",
        /* 07 */ "List Recipe Titles",
        /* 08 */ "Scan Recipes",
        /* 09 */ "Search Recipe by Title",
        /* 10 */ "Export Recipes",
        /* 11 */ "Import Recipes\n",
        
        /* 12 */ "Return to Main Menu"
    };
    
    while(input != '\n') {
        adminDisplay();
        
        selected = selectionLooper(selected, 12);
        if(selected < 4 ) selectionCarousel(selected, 13, options, YLW);
        else selectionCarousel(selected, 13, options, PRP);
        
        printf(
            GRY 
            "\n * [ ↑ / ↓ ] to navigate\n"
            " * [ ENTER ] to select\n\n" 
            RESET
        );

        input = getch();
        navigation(input, &selected, 'y');

        clearScreen();
    }

    if(selected == 12) *STATE = -1;

    return selected;
}

//TURN TO ARRAY
int calElements = 0;
int recElements = 0;

void updateFuncSwitch(int STATE, ingredient FOOD[], recipe RECIPES[]) {
    // clearScreen();

    switch(STATE) {
        // CAL
        case 0: 
            addCalDisplay();
            addCalInfo(FOOD, &calElements, 50, 0); 
            break;
        case 1: 
            if(!calElements) {
                addCalDisplay();
                printf(
                    RED " [!] List empty\n"
                    GRY " >>> Returning back to update menu\n" RESET
                );
                delayedLoad();
            }
            else
                viewCalInfo(FOOD, calElements); 
            break;
        // REC
        case 4:
            addRecipe(RECIPES, &recElements);
            break;
        
    }
}