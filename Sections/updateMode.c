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
int updateMode(int *STATE) {
    int selected = 0;
    char input = '\0';
    
    string options[13] = {
        "Add Food-Calorie Info",
        "View Food-Calorie Chart",
        "Save Calorie Info",
        "Load Calorie Info\n",
        "Add Recipe",
        "Modify Recipe",
        "Delete Recipe",
        "List Recipe Titles",
        "Scan Recipes",
        "Search Recipe by Title",
        "Export Recipes",
        "Import Recipes\n",
        "Return to Main Menu"
    };
    
    while(input != '\n') {
        adminDisplay();
        
        selected = selectionLooper(selected, 12);
        selectionCarousel(selected, 13, options);
        
        printf(
            GRY 
            "\n * [ ↑ / ↓ ] to navigate\n"
            " * [ ENTER ] to select\n\n" 
            RESET
        );

        input = getch();
        navigation(input, &selected);

        clearScreen();
    }

    if(selected == 12)
        *STATE = -1;

    return selected;
}

void addCal(ingredient FOOD[], int *INDEX) {
    addCalDisplay();
    printf(GRY " * Enter food item, quantity, unit, and calorie count\n\n" RESET);

    char input = '\0';
    int display = 1;

    int foodIndex = *INDEX;
    while(foodIndex < 50 && (input != 'x' && input != 'X')) {
        if(display) {
            printf(YLW "    Food Item: (%d out of 50)\n    " RESET, foodIndex + 1);
            getStringInput(FOOD[foodIndex].item, "%[^\n]20s", "\e[1F\e[5G");
            
            int isDuplicate = 0;
            do {
                int duplicateFound = 0;
                int uniqueIndex = 0;
                while((uniqueIndex != foodIndex + 1) && !duplicateFound) {
                    if(uniqueIndex != foodIndex) {
                        if(!strcmp(FOOD[foodIndex].item, FOOD[uniqueIndex].item)) 
                            duplicateFound = 1;
                    }
                
                uniqueIndex++;
                
                }
                isDuplicate = duplicateFound;
            
                if(isDuplicate) {
                    printf(RED "\e[1F\e[0J\e[20G\t\t[!] This item already exists, please enter a new one\e[5G" RESET);
                    getStringInput(FOOD[foodIndex].item, "%[^\n]20s", "\e[1F\e[5G");
                }
            }
            while(isDuplicate);
            printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment
            
            printf(YLW "\n    Quantity:\n    " RESET);
            scanf("%f", &FOOD[foodIndex].quantity);
            
            printf(YLW "\n    Unit:\n\n    " RESET);
            getStringInput(FOOD[foodIndex].unit, "%[^\n]20s", "\e[1F\e[5G");
            
            printf(YLW "\n    Calorie Count:\n    " RESET);
            scanf("%f", &FOOD[foodIndex].calories);
            
            
            getch();
            printf(
                GRY
                "\n"
                " * [ ANY KEY ] to continue\n"
                " * [ X ] to finish\n\n"
                RESET
            );
        }

        foodIndex++;
        *INDEX =  foodIndex;
        
        display = 0;

        input = getch();
        if(input == '\n') {
            printf(LINE);
            display = 1;
        }
    }

    if(foodIndex == 50) {
        printf(RED " [!] List full" RESET);
        getch();
    }
}

void viewCal(ingredient FOOD[], int TOTAL) {
    viewCalDisplay();
    
    if(!TOTAL) {
        printf(RED " [!] List empty" RESET);
        getch();
    }
    else {
        char * col[4]= {
            "FOOD ITEM",
            "QUANTITY",
            "UNIT",
            "CALORIES"
        };
        
        printf("    ");
        int colIndex = 0;
        while(colIndex != 4) {
            printf(
                "%-10s%s%10s", "|", col[colIndex], "|"
            );
            colIndex++;
        }
        printf("\n ---------------------------------------------------------------------------------------------------------------------------\n");
        
        int rows = TOTAL;

        int displayIndex = 0;
        while(displayIndex != 10) {
            printf(
                " %0.2d |    %-19s    ||    %-18.2f    ||    %-14s    ||    %-18.2f    |\n", 
                displayIndex + 1,
                FOOD[displayIndex].item,
                FOOD[displayIndex].quantity,
                FOOD[displayIndex].unit,
                FOOD[displayIndex].calories
            );
            displayIndex++;
        }

        printf(
            GRY 
            "\n"
            " * [ N ] to view next 10 items\n"
            " * [ X ] to exit\n"
            RESET
        );

        getch();
    }
}

void saveCal() {}
void loadCal() {}

void saveRec() {}
void modRec() {}
void deleteRec() {}
void listRec() {}
void scanRec() {}
void searchRec() {}
void exportRec() {}

//TURN TO ARRAY
int calElements = 0;

void updateFuncSwitch(int STATE, ingredient FOOD[]) {
    // clearScreen();

    switch(STATE) {
        case 0: addCal(FOOD, &calElements); break;
        case 1: viewCal(FOOD, calElements); break;
    }
}