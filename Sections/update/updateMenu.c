// Asks and validates the log-in credentials
//
// @RETURNS 0 if log-in details are valid RETURNS -1 if not, matching the mode indices
int logIn() {
    printf(
        "\n"
        "ADMIN LOG IN SCREEN\n"
        "\n"
    );

    char userName[7];
    printf(YLW "    Username: " RESET);
    getStringInput(userName, "%6[^\n]s", "\e[1F\e[15G");

    char pass[8];
    printf(YLW "    Password: " RESET);
    getStringInput(pass, "%7[^\n]s", "\e[1F\e[15G");

    int canProceed = 0;
    if(strcmp(userName, "admin") || strcmp(pass, "ad1234")) {
        printf(          
            RED "\n [!] Invalid username or password entered\n" 
            GRY " >>> Returning back to main menu\n" 
            RESET
        );
        
        canProceed = -1;
    }
    else {
        printf(
            GRN "\n [O] User validated!\n"
            GRY " >>> Proceeding to update mode\n"
            RESET
        );
    }

    delayedLoad();   

    return canProceed;
}

// 
int updateMenu() {
    int option = 0;
    char input = '\0';
    
    string options[13] = {
        /* 00 */ "Add Food-Calorie Info",
        /* 01 */ "View Food-Calorie Chart",
        /* 02 */ GRY "Save Calorie Info",
        /* 03 */ GRY "Load Calorie Info\n",

        /* 04 */ "Add Recipe",
        /* 05 */ GRY "Modify Recipe",
        /* 06 */ GRY "Delete Recipe",
        /* 07 */ "List Recipe Titles",
        /* 08 */ GRY "Scan Recipes",
        /* 09 */ GRY "Search Recipe by Title",
        /* 10 */ GRY "Export Recipes",
        /* 11 */ GRY "Import Recipes\n",
        
        /* 12 */ "Return to Main Menu"
    };
    
    while(!INPUT_ENTER) {
        printf(
            "\n"
            "    UPDATE MODE\n"
            "\n"
        );
        
        option = selectionLooper(option, 12);
        if(option < 4 ) selectionCarousel(option, 13, options, YLW);
        else selectionCarousel(option, 13, options, PRP);
        
        printf(
            GRY 
            "\n * [ ↑ / ↓ ] to navigate\n"
            " * [ ENTER ] to select\n\n" 
            RESET
        );

        input = getch();
        navigation(input, &option, 'y');

        WIPE
    }

    if(option == 12) option = -1;

    return option;
}

// //TURN TO LOCAL VARIABLES

void updateFuncSwitch(int OPTION, ingredient FOOD[], int *F_ELEM, recipe RECIPES[], int *R_ELEM) {
    
    WIPE

    enum calInfoOptions option = OPTION;
    switch(option) {
        // CAL-INFO
        case ADD_CAL: 
            addCalInfo(FOOD, F_ELEM); 
            break;
        case VIEW_CAL: 
            if(!(*F_ELEM)) {
                // addCalDisplay();
                printf(
                    RED " [!] List empty\n"
                    GRY " >>> Returning back to update menu\n" RESET
                );
                delayedLoad();
            }
            else
                viewCalInfo(FOOD, *F_ELEM); 
            break;
        case SAVE_CAL: break;
        case LOAD_CAL: break;
        case ADD_REC: break;
        case MOD_REC: break;
        case DEL_REC: break;
        case LIST_REC: break;
        case SCAN_REC: break;
        case SEARCH_REC: break;
        case EXPORT_REC: break;
        case IMPORT_REC: break;
        // // RECIPES
        // case 4:
        //     addRecipe(RECIPES, &recElements);
        //     break;
        // case 7:
        //     listRecipeTitlesDisplay();

        //     if(!recElements) {
        //         printf(
        //             RED " [!] List empty\n"
        //             GRY " >>> Returning back to update menu\n" RESET
        //         );
        //         delayedLoad();
        //     }
        //     else
        //         listRecipeTitles(RECIPES, recElements);
        //     break;

        
    }
}