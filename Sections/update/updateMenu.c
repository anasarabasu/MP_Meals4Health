// Asks and validates the log-in credentials
//
// @RETURNS 0 if log-in details are valid RETURNS -1 if not, matching the mode indices
int logIn() {
    printf(
        "\nADMIN LOG IN SCREEN\n"
        "\n"
    );

    char userName[7];
    printf(YLW "    Username: " RESET);
    getStringInput(userName, "%6[^\n]s", "\e[1F\e[15G");
    clearBuffer();

    char pass[8];
    printf(YLW "    Password: " RESET);
    getStringInput(pass, "%7[^\n]s", "\e[1F\e[15G");
    clearBuffer();

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


int updateMenu(int F_ELEM, int R_ELEM) {
    char input;
    
    int option = 0;
    string options[13] = {
        /* 00 */ "Add Food-Calorie Info",
        /* 01 */ "View Food-Calorie Chart",
        /* 02 */ "Save Calorie Info",
        /* 03 */ GRY "Load Calorie Info\n",

        /* 04 */ "Add Recipe",
        /* 05 */ "Modify Recipe",
        /* 06 */ "Delete Recipe",
        /* 07 */ "List Recipe Titles",
        /* 08 */ "Scan Recipes",
        /* 09 */ "Search Recipe by Title",
        /* 10 */ GRY "Export Recipes",
        /* 11 */ GRY "Import Recipes\n",
        
        /* 12 */ "Return to Main Menu"
    };

    if(!F_ELEM) {
        strcpy(options[1], GRY "(EMPTY)  View Food-Calorie Chart");
        strcpy(options[2], GRY "(EMPTY)  Save Calorie Info");

    }

    if(!R_ELEM) {
        strcpy(options[5], GRY "(EMPTY)  Modify Recipe");
        strcpy(options[6], GRY "(EMPTY)  Delete Recipe");
        strcpy(options[7], GRY "(EMPTY)  List Recipe Titles");
        strcpy(options[8], GRY "(EMPTY)  Scan Recipes");
        strcpy(options[9], GRY "(EMPTY)  Search Recipe by Title");
        strcpy(options[10], GRY "(EMPTY)  Export Recipes");

    }
    
    while(!INPUT_ENTER) {
        printf(
            "\n"
            "UPDATE MODE\n"
            "\n"
        );
        
        option = selectionLooper(option, 12);
        if(option < 4 ) selectionCarousel(option, 13, options, YLW);
        else selectionCarousel(option, 13, options, PRP);
        
        printf(
            GRY 
            "\n * [ UP / DOWN ] to navigate\n"
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

void updateFuncSwitch(int OPTION, ingredient FOOD[], int *F_ELEM, recipe RECIPES[], int *R_ELEM) {
    system("cls");

    enum calInfoOptions option = OPTION;
    switch(option) {
        // CAL-INFO
        case ADD_CAL: 
            addCalInfo(FOOD, F_ELEM); 
            break;
        case VIEW_CAL: 
            if(*F_ELEM) viewCalInfo(FOOD, *F_ELEM); 
            break;
        case SAVE_CAL: 
            if(*F_ELEM) saveCal(FOOD);
            break;
        case LOAD_CAL: break;
        case ADD_REC: 
            addRecipe(RECIPES, R_ELEM);
            break;
        case MOD_REC: 
            if(*R_ELEM) modRec(RECIPES, *R_ELEM);
            break;
        case DEL_REC: 
            if(*R_ELEM) deleteRec(RECIPES, R_ELEM);
            break;
        case LIST_REC: 
            printf("\nLIST RECIPE TITLES\n\n");

            if(*R_ELEM) {
                listRecipeTitles(RECIPES, *R_ELEM);

                printf(GRY " * [ ENTER ] to return to update menu\n" RESET);
        
                char input;
                input = getch();
                while(!INPUT_ENTER) 
                    input = getch();
            }
            break;
        case SCAN_REC: 
            if(*R_ELEM) scanRec(RECIPES, *R_ELEM);

            break;
        case SEARCH_REC: 
            printf("\nSEARCH RECIPE BY TITLE\n\n");

            if(*R_ELEM) searchRec(RECIPES, *R_ELEM);
            break;
        case EXPORT_REC: break;
        case IMPORT_REC: break;
    }
}