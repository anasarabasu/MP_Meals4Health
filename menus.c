int modRecMenu(recipe RECIPE) {
    char input;
    
    int option = 0;
    string options[5] = {
        "Add Ingredient",
        "Delete Ingredient\n",
        "Add Step",
        "Delete Step\n",
        "Return to Update Menu"
    };

    if(RECIPE.ingredientCount == 1) strcpy(options[1], GRY "Delete Ingredient    " RESET RED "[!] User is not allowed to delete all ingredients\n");
    if(RECIPE.stepCount == 1) strcpy(options[3], GRY "Delete Step    " RESET RED "[!] User is not allowed to delete all ingredients\n");
    
    CURSOR_POS
    printf(" ");
    int space = 0; 
    for(space; space <= 24; space++) printf("\n");

    while(!INPUT_ENTER) {
        TOP

        printf(LINE "\nMODIFY RECIPE\n\n");
        
        displayRecipe(RECIPE);
        printf(LINE2 "\n");
        
        option = selectionLooper(option, 4);
        selectionCarousel(option, 5, options, PRP);
        
        printf(
            GRY 
            "\n * [ UP / DOWN ] to navigate\n"
            " * [ ENTER ] to select\n\n" 
            RESET
        );
        
        CURSOR_POS

        input = getch();
        navigation(input, &option, 'y');
        
    }
    input = '\0';

    return option;
}

void modRecSwitch(recipe RECIPES[], int R_ELEM) {
    printf(LINE "\nMODIFY RECIPE\n\n");

    int recipeIndex = checkRecipe(RECIPES, R_ELEM);
    
    displayRecipe(RECIPES[recipeIndex]);
    printf(LINE2);
    
    clearBuffer();
    TOP
    CLEAN

    int option = modRecMenu(RECIPES[recipeIndex]);
    
    
    while(option != 4) {
        printf(" ");
        int space = 0; 
        for(space; space <= 24; space++) printf("\n");
        TOP

        switch(option) {
            case 0: 
                printf(LINE "\nADD INGREDIENTS\n\n");
                addIngredients(RECIPES[recipeIndex].ingredients, &RECIPES[recipeIndex].ingredientCount, 20, 0);
                break;
            case 1:
                if(RECIPES[recipeIndex].ingredientCount > 1) 
                    deleteIngredients(RECIPES[recipeIndex].ingredients, &RECIPES[recipeIndex].ingredientCount);
                
                break;
            case 2:
                printf(LINE "\nADD STEPS\n\n");
                addSteps(RECIPES[recipeIndex].steps, &RECIPES[recipeIndex].stepCount, 15, 0);
                break;
            case 3:
                if(RECIPES[recipeIndex].stepCount > 1) 
                    deleteSteps(RECIPES[recipeIndex].steps, &RECIPES[recipeIndex].stepCount);
                
                break;
            break;
        }
        
        option = modRecMenu(RECIPES[recipeIndex]);
    }
}

//---------------------------------------------------------------------------


// Asks and validates the log-in credentials
//
// @RETURNS 0 if log-in details are valid RETURNS -1 if not, matching the mode indices
int logIn() {
    printf(
        LINE
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
            GRY " [ X ] Return back to main menu\n" 
            RESET
        );
        

        canProceed = -1;
    }
    else {
        printf(
            GRN "\n [O] User validated!\n"
            GRY " [ X ]  Proceed to update mode\n"
            RESET
        );
    }

    CURSOR_POS

    char input = getch();
    while(!INPUT_EXIT)
        input = getch();

    printf(" ");
    int space = 0; 
    for(space; space <= 24; space++) printf("\n");

    return canProceed;
}


int updateMenu(int F_ELEM, int R_ELEM) {
    int option = 11;
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
        /* 11 */ GRY "Import Recipes\n",
        
        /* 12 */ "Return to Main Menu"
    };
    
    if(!F_ELEM) {
        strcpy(options[1], GRY "( EMPTY )  View Food-Calorie Chart");
        strcpy(options[2], GRY "( EMPTY )  Save Calorie Info");
        
    }
    if(F_ELEM == 50) strcpy(options[3], GRY "( FULL )  Load Calorie Info\n");
    
    if(!R_ELEM) {
        strcpy(options[5], GRY "( EMPTY )  Modify Recipe");
        strcpy(options[6], GRY "( EMPTY )  Delete Recipe");
        strcpy(options[7], GRY "( EMPTY )  List Recipe Titles");
        strcpy(options[8], GRY "( EMPTY )  Scan Recipes");
        strcpy(options[9], GRY "( EMPTY )  Search Recipe by Title");
        strcpy(options[10], GRY "( EMPTY )  Export Recipes");
    }
    if(R_ELEM == 50) strcpy(options[11], GRY "( FULL )  Import Recipes\n");
    
    char input;
    while(!INPUT_ENTER) {
        printf(LINE"\nUPDATE MODE\n\n");
        
        option = selectionLooper(option, 12);
        if(option < 4 ) selectionCarousel(option, 13, options, YLW);
        else selectionCarousel(option, 13, options, PRP);
        
        printf(
            GRY 
            "\n * [ UP / DOWN ] to navigate\n"
            " * [ ENTER ] to select\n\n" 
            RESET
        );

        CURSOR_POS

        input = getch();
        navigation(input, &option, 'y');

        TOP
    }

    if(option == 12) option = -1;

    return option;
}

void updateFuncSwitch(int OPTION, ingredient FOOD[], int *F_ELEM, recipe RECIPES[], int *R_ELEM) {
    CURSOR_POS
    printf(" ");
    int space = 0; 
    for(space; space <= 24; space++) printf("\n");
    TOP

    switch(OPTION) {
        // CAL-
        case 0: 
            addCalInfo(FOOD, F_ELEM); 
            break;
        case 1: 
            if(*F_ELEM) viewCalInfo(FOOD, *F_ELEM); 
            break;
        case 2: 
            if(*F_ELEM) saveCal(FOOD, *F_ELEM);
            break;
        case 3: 
            if(*F_ELEM != 50) loadCal(FOOD, F_ELEM);
            break;

        // REC 
        case 4: 
            addRecipe(RECIPES, R_ELEM);
            break;
        case 5: 
            if(*R_ELEM) modRecSwitch(RECIPES, *R_ELEM);
            break;
        case 6: 
            if(*R_ELEM) deleteRec(RECIPES, R_ELEM);
            break;
        case 7: 
            printf(LINE "\nLIST RECIPE TITLES\n\n");

            if(*R_ELEM) {
                listRecipeTitles(RECIPES, *R_ELEM);

                printf(GRY " * [ X ] Return to update menu\n" RESET);
        
                char input;
                input = getch();
                while(!INPUT_EXIT) 
                    input = getch();
            }
            break;
        case 8: 
            if(*R_ELEM) scanRec(RECIPES, *R_ELEM);
            break;
        case 9: 
            if(*R_ELEM) searchRec(RECIPES, *R_ELEM);
            break;
        case 10: 
            if(*R_ELEM) exportRec(RECIPES, *R_ELEM);
            break;
        case 11: 
            if(*R_ELEM != 50) importRec(RECIPES, R_ELEM);
            break;
    }

    CURSOR_POS
    printf(" ");
    space = 0; 
    for(space; space <= 24; space++) printf("\n");
    TOP
}

//---------------------------------------------------------------------------

int accessMenu(int R_ELEM) {
    int option = 5;
    string options[9] = {
        /* 00 */ "Import Food-Calorie Info",
        /* 01 */ GRY "Import Recipes\n",

        /* 02 */ "List Recipe Titles",
        /* 03 */ "Search Recipe by Title\n",

        /* 04 */ "Scan Recipes",
        /* 05 */ "Scan Recipes by Ingredient\n",

        /* 06 */ "Generate Shopping List",
        /* 07 */ "Recommend Menu\n",

        /* 08 */ "Return to Main Menu"
    };

    if(!R_ELEM) {
        strcpy(options[2], GRY "( EMPTY )  List Recipe Titles");
        strcpy(options[3], GRY "( EMPTY )  Search Recipe by Title\n");
        strcpy(options[4], GRY "( EMPTY )  Scan Recipes");
        strcpy(options[5], GRY "( EMPTY )  Scan Recipes by Ingredient\n");
        strcpy(options[6], GRY "( EMPTY )  Generate Shopping List");
        strcpy(options[7], GRY "( EMPTY )  Recommend Menu\n");
    }
    
    char input;
    while(!INPUT_ENTER) {
        printf(LINE "\n ACCESS MODE\n\n");

        option = selectionLooper(option, 8);
        if(option < 2) selectionCarousel(option, 9, options, YLW);
        else if(option < 4) selectionCarousel(option, 9, options, PRP);
        else if(option < 6) selectionCarousel(option, 9, options, YLW);
        else selectionCarousel(option, 9, options, PRP);


        printf(
            GRY 
            "\n * [ UP / DOWN ] to navigate\n"
            " * [ ENTER ] to select\n\n" 
            RESET
        );

        CURSOR_POS

        input = getch();
        navigation(input, &option, 'y');

        TOP
    }

    if(option == 8) option = -1;
    return option;
}

void accessFuncSwitch(int OPTION, ingredient FOOD[], int *F_ELEM, recipe RECIPES[], int *R_ELEM) {
    CURSOR_POS
    printf(" ");
    int space = 0; 
    for(space; space <= 24; space++) printf("\n");
    TOP

    switch(OPTION) {
        case 0: 
            loadCal(FOOD, F_ELEM);
            break;
        case 1: 
            break;
        case 2: 
            printf(LINE "\nLIST RECIPE TITLES\n\n");

            if(*R_ELEM) {
                listRecipeTitles(RECIPES, *R_ELEM);

                printf(GRY " * [ X ] Return to update menu\n" RESET);
        
                char input;
                input = getch();
                while(!INPUT_EXIT) 
                    input = getch();
            }
            break;
        case 3: 
            if(*R_ELEM) searchRec(RECIPES, *R_ELEM);
            break;
        case 4: 
            if(*R_ELEM) scanRec(RECIPES, *R_ELEM);
            break;
        case 5: 
            if(*R_ELEM) scanRecByIngredient(RECIPES, *R_ELEM);
            break;
        case 6: 
            if(*R_ELEM) genereateShopList(RECIPES, *R_ELEM);
            break;
        case 7: 
            if(*R_ELEM) recommenMenu(RECIPES, *R_ELEM);
            break;
    }

    CURSOR_POS
    printf(" ");
    space = 0; 
    for(space; space <= 24; space++) printf("\n");
    TOP
}



//---------------------------------------------------------------------------

// menu handler for choosing between the modes
//
// @RETURN the chosen mode option or exit the program
int mainMenu() {
    char options[3][90] = {
        "Update Recipe Box",
        "Access Recipe Box",
        "Exit Program"
    };

    int mode = 0;

    int x = 0;
    char input;
    while(!INPUT_ENTER) { // selection carousel
        TOP

        printf(
            LINE
            "\n"
            "MENU SELECTION SCREEN\n"
            "\n"
        );
        
        mode = selectionLooper(mode, 2);
        selectionCarousel(mode, 3, options, YLW);
        printf(GRY "\n * [ UP / DOWN ] to navigate\n * [ ENTER ] to select\n" RESET);
        
        CURSOR_POS
        
        input = getch();
        navigation(input, &mode, 'y');
    }

    if(mode == 2) mode *= -1;

    return mode;
}

void menuSwitch() {
    ingredient food[50];
    int fElem = 0;

    recipe recipes[50];
    int rElem = 3;

    strcpy(recipes[0].name, "1");
    recipes[0].ingredientCount = 1;
    strcpy(recipes[0].ingredients[0].item, "1");

    strcpy(recipes[1].name, "2");
    recipes[1].ingredientCount = 1;
    strcpy(recipes[1].ingredients[0].item, "2");

    strcpy(recipes[2].name, "3");
    recipes[2].ingredientCount = 1;
    strcpy(recipes[2].ingredients[0].item, "1");
    int mode = -1;
    mode = 1;


    while(mode != -2) { 
        switch(mode) { 
            case -1: 
                mode = mainMenu();

                // reset
                // fElem = 0;
                // rElem = 0;
                break;
            case 0: {
                // mode = logIn();

                TOP
                
                int option = 0;
                if(!mode) option = updateMenu(fElem, rElem);
                if(option == -1) mode = -1;
                
                updateFuncSwitch(option, food, &fElem, recipes, &rElem);
                
                break;
            }
            
            case 1: {
                TOP 

                int option = 0;
                if(mode) option = accessMenu(rElem);
                if(option == -1) mode = -1;

                accessFuncSwitch(option, food, &fElem, recipes, &rElem);
                break;
            }
            default: 
                printf(" >>> Program stuck in a loop");
                getch();
            break;
        }
        
        CURSOR_POS
        printf(" ");
        int space = 0; 
        for(space; space <= 24; space++) printf("\n");
        TOP
    }
    
}
