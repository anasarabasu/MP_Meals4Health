int modRecMenu(recipe RECIPE, ingredient CALORIE[], int C_ELEM) {
    int option = 0;
    string options[5] = {
        "Add Ingredients",
        "Add Steps\n",
        "Delete Ingredients",
        "Delete Steps\n",
        "Return to Update Menu"
    };

    if(RECIPE.ingredientCount == 50) strcpy(options[0], GRY "( FULL ) Add Ingredients" RESET);
    if(RECIPE.stepCount == 15) strcpy(options[1], GRY "( FULL ) Add Steps\n" RESET);
    
    if(RECIPE.ingredientCount == 1) strcpy(options[2], GRY "Delete Ingredients    " RESET RED "[!] User is not allowed to delete all ingredients");
    if(RECIPE.stepCount == 1) strcpy(options[3], GRY "Delete Steps    " RESET RED "[!] User is not allowed to delete all steps\n");
    
    moveDisplay();

    char input = '\0';
    while(!INPUT_ENTER) {
        TOP
        CLEAN

        printf(LINE "\nMODIFY RECIPE\n\n");
        
        displayRecipe(RECIPE, CALORIE, C_ELEM);
        printf(LINE2 "\n");
        
        option = selectionLooper(option, 4);
        if(option < 2) selectionCarousel(option, 5, options, YLW);
        else selectionCarousel(option, 5, options, PRP);
        
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

    return option;
}




void modRecSwitch(recipe RECIPES[], int R_ELEM, ingredient CALORIE[], int C_ELEM) {
    printf(LINE "\nMODIFY RECIPE\n\n");

    int recipeIndex = checkRecipe(RECIPES, R_ELEM);
    clearBuffer();

    int option = modRecMenu(RECIPES[recipeIndex], CALORIE, C_ELEM);
    while(option != 4) {
        moveDisplay();

        switch(option) {
            case 0: 
                printf(LINE "\nADD INGREDIENTS\n\n");
                addIngredients(RECIPES[recipeIndex].ingredients, &RECIPES[recipeIndex].ingredientCount, 20, 0);
                break;
            case 1:
                printf(LINE "\nADD STEPS\n\n");
                addSteps(RECIPES[recipeIndex].steps, &RECIPES[recipeIndex].stepCount, 15, 0);
                break;
            case 2:
                if(RECIPES[recipeIndex].ingredientCount > 1) 
                    deleteIngredients(RECIPES[recipeIndex].ingredients, &RECIPES[recipeIndex].ingredientCount);
                
                break;
            case 3:
                if(RECIPES[recipeIndex].stepCount > 1) 
                    deleteSteps(RECIPES[recipeIndex].steps, &RECIPES[recipeIndex].stepCount);
                
                break;
            break;
        }
        
        option = modRecMenu(RECIPES[recipeIndex], CALORIE, C_ELEM);
    }
}




//---------------------------------------------------------------------------

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

    int canProceed = 1;
    if(strcmp(userName, "admin") || strcmp(pass, "ad1234")) {
        printf(          
            RED "\n [!] Invalid username or password entered\n" 
            GRY " [ X ] Return back to main menu\n" 
            RESET
        );
        

        canProceed = 0;
    }
    else {
        printf(
            GRN "\n [O] User validated!\n"
            GRY " [ X ]  Proceed to update mode\n"
            RESET
        );
    }

    confirmBack();
    moveDisplay();

    return canProceed;
}




int updateMenu(int F_ELEM, int R_ELEM) {
    int option = 0;
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
    
    if(!F_ELEM) {
        strcpy(options[1], GRY "( NO DATA )  View Food-Calorie Chart");
        strcpy(options[2], GRY "( NO DATA )  Save Calorie Info");
        
    }
    if(F_ELEM == 50) {
        strcpy(options[0], GRY "( FULL )  Add Food-Calorie Info");
        strcpy(options[3], GRY "( FULL )  Load Calorie Info\n");
    }
    
    if(!R_ELEM) {
        strcpy(options[5], GRY "( NO DATA )  Modify Recipe");
        strcpy(options[6], GRY "( NO DATA )  Delete Recipe");
        strcpy(options[7], GRY "( NO DATA )  List Recipe Titles");
        strcpy(options[8], GRY "( NO DATA )  Scan Recipes");
        strcpy(options[9], GRY "( NO DATA )  Search Recipe by Title");
        strcpy(options[10], GRY "( NO DATA )  Export Recipes");
    }
    if(R_ELEM == 50) {
        strcpy(options[4], GRY "( FULL )  Add Recipe");
        strcpy(options[11], GRY "( FULL )  Import Recipes\n");
    }
    
    char input = '\0';
    while(!INPUT_ENTER) {
        TOP
        CLEAN

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
    }

    if(option == 12) option = -1;

    return option;
}




void updateFuncSwitch(int OPTION, ingredient FOOD[], int *F_ELEM, recipe RECIPES[], int *R_ELEM) {
    moveDisplay();

    switch(OPTION) {
        // CAL-
        case 0: 
            printf(LINE "\nADD CALORIE INFO\n" RESET); 
            if(*F_ELEM < 50) addIngredients(FOOD, F_ELEM, 50, 0);
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
            arrangeRecipeTitle(RECIPES, *R_ELEM);
            break;
        case 5: 
            if(*R_ELEM) modRecSwitch(RECIPES, *R_ELEM, FOOD, *F_ELEM);
            break;
        case 6: 
            if(*R_ELEM) deleteRec(RECIPES, R_ELEM);
            break;
        case 7: 
            printf(LINE "\nLIST RECIPE TITLES\n\n");

            if(*R_ELEM) {
                listRecipeTitles(RECIPES, *R_ELEM, PRP);

                printf(GRY " * [ X ] Return to menu\n" RESET);
                confirmBack();
            }
            break;
        case 8: 
            if(*R_ELEM) scanRec(RECIPES, *R_ELEM, FOOD, *F_ELEM);
            break;
        case 9: 
            if(*R_ELEM) searchRec(RECIPES, *R_ELEM, FOOD, *F_ELEM);
            break;
        case 10: 
            if(*R_ELEM) exportRec(RECIPES, *R_ELEM);
            break;
        case 11: 
            if(*R_ELEM != 50) {
                importRec(RECIPES, R_ELEM);
                arrangeRecipeTitle(RECIPES, *R_ELEM);
            }
            break;
    }
}




//---------------------------------------------------------------------------

int accessMenu(int R_ELEM) {
    int option = 0;
    string options[9] = {
        /* 00 */ "Load Calorie Info",
        /* 01 */ "Import Recipes\n",

        /* 02 */ "List Recipe Titles",
        /* 03 */ "Search Recipe by Title",
        /* 04 */ "Scan Recipes",
        /* 05 */ "Scan Recipes by Ingredient\n",

        /* 06 */ "Generate Shopping List",
        /* 07 */ "Recommend Menu\n",

        /* 08 */ "Return to Main Menu"
    };

    if(!R_ELEM) {
        strcpy(options[2], GRY "( NO DATA )  List Recipe Titles");
        strcpy(options[3], GRY "( NO DATA )  Search Recipe by Title\n");
        strcpy(options[4], GRY "( NO DATA )  Scan Recipes");
        strcpy(options[5], GRY "( NO DATA )  Scan Recipes by Ingredient");
        strcpy(options[6], GRY "( NO DATA )  Generate Shopping List");
        strcpy(options[7], GRY "( INCOMPLETE DATA )  Recommend Menu\n");
    }
    
    char input = '\0';
    while(!INPUT_ENTER) {
        TOP
        CLEAN

        printf(LINE "\n ACCESS MODE\n\n");

        option = selectionLooper(option, 8);
        if(option < 2) selectionCarousel(option, 9, options, YLW);
        else if(option < 6) selectionCarousel(option, 9, options, PRP);
        else selectionCarousel(option, 9, options, YLW);


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

    if(option == 8) option = -1;
    return option;
}




void accessFuncSwitch(int OPTION, ingredient FOOD[], int *F_ELEM, recipe RECIPES[], int *R_ELEM) {
    moveDisplay();

    switch(OPTION) {
        case 0: 
            loadCal(FOOD, F_ELEM);
            break;
        case 1: 
            importRec(RECIPES, R_ELEM);
            arrangeRecipeTitle(RECIPES, *R_ELEM);

            break;
        case 2: 
            printf(LINE "\nLIST RECIPE TITLES\n\n");

            if(*R_ELEM) {
                listRecipeTitles(RECIPES, *R_ELEM, PRP);

                printf(GRY " * [ X ] Return to menu\n" RESET);
                confirmBack();
            }
            break;
        case 3: 
            if(*R_ELEM) searchRec(RECIPES, *R_ELEM, FOOD, *F_ELEM);
            break;
        case 4: 
            if(*R_ELEM) scanRec(RECIPES, *R_ELEM, FOOD, *F_ELEM);
            break;
        case 5: 
            if(*R_ELEM) scanRecByIngredient(RECIPES, *R_ELEM, FOOD, *F_ELEM);
            break;
        case 6: 
            if(*R_ELEM) genereateShopList(RECIPES, *R_ELEM);
            break;
        case 7: 
            // if(*R_ELEM && *F_ELEM) 
            recommendMenu(RECIPES, *R_ELEM, FOOD, *F_ELEM);
            break;
    }
}




//---------------------------------------------------------------------------

int mainMenu() {
    int option = 0;
    char options[3][90] = {
        "Update Recipe Box",
        "Access Recipe Box",
        "Exit Program"
    };

    char input = '\0';
    while(!INPUT_ENTER) { // selection carousel
        TOP
        CLEAN

        printf(
            LINE
            "\n"
            "MENU SELECTION SCREEN\n"
            "\n"
        );
        
        option = selectionLooper(option, 2);
        selectionCarousel(option, 3, options, YLW);
        printf(GRY "\n * [ UP / DOWN ] to navigate\n * [ ENTER ] to select\n" RESET);
        
        CURSOR_POS
        
        input = getch();
        navigation(input, &option, 'y');
    }

    if(option == 2) option *= -1;

    return option;
}




void menuSwitch() {
    ingredient food[50];
    int fElem = 0;

    recipe recipes[50];
    int rElem = 0;

    int isLogged = 0;
    
    int mode = -1;
    while(mode != -2) { 
        switch(mode) { 
            case -1: 
                mode = mainMenu();

                fElem = 0;
                rElem = 0;

                isLogged = 0;
                break;
            case 0: {
                if(!isLogged) {
                    isLogged = logIn();

                    if(!isLogged) mode = -1;
                }

                if(isLogged) {
                    TOP
                    int option = updateMenu(fElem, rElem);
                    if(option == -1) mode = -1;

                    updateFuncSwitch(option, food, &fElem, recipes, &rElem);
                }
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
        
        moveDisplay();
    }
}
