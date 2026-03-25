void addRecipe(recipe RECIPES[], int *INDEX) {
    printf("\nADD RECIPE\n" RESET);

    if(*INDEX < 50) {
        printf(
            GRY " * Enter dish name, classification, number of servings, list of ingredients, and procedures\n\n" RESET
        );
    }
    else {
        printf("\n" LINE );
    }
    char input;

    int recipeIndex = *INDEX;
    while(recipeIndex < 50 && !INPUT_EXIT) {
        printf(PRP "    Dish Name: " GRY " (%d out of 50)\n    " RESET, recipeIndex + 1);
        
        getStringInput(RECIPES[recipeIndex].name, "%20[^\n]s", "\e[1F\e[5G");

        int isUnique = 1;
        do {
            int duplicateFound = 0;

            int uniqueIndex = 0;
            while((uniqueIndex != recipeIndex + 1) && !duplicateFound) {
                if(uniqueIndex != recipeIndex) 
                    if(!strcmp(RECIPES[recipeIndex].name, RECIPES[uniqueIndex].name)) 
                        duplicateFound = 1;
            
                uniqueIndex++;
            }
            isUnique = !duplicateFound;
        
            if(!isUnique) {
                printf(RED "\e[1F\e[0J\e[25G\t\t[!] This item already exists, please enter a new one\e[5G" RESET);
                getStringInput(RECIPES[recipeIndex].name, "%20[^\n]s", "\e[5G");
            }
        }
        while(!isUnique);
        printf("\e[1F\e[25G\t\t\e[0J\n"); // removes the [!] comment
        clearBuffer();

        //------------------------------------------

        printf(
            PRP "\n    Classification: " 
            GRY " [ LEFT / RIGHT ] to choose \n    " 
            RESET
        );

        int classIndex = 0;
        string classification[3]= {
            "Starter",
            "Main",
            "Dessert"
        };
        
        while(!INPUT_ENTER) {
            classIndex = selectionLooper(classIndex, 2);
            
            int selectionDisplayIndex = 0;
            while(selectionDisplayIndex != 3) {
                
                if(classIndex == selectionDisplayIndex) printf(">");
                else printf(GRY ">");
                
                printf(" %-20s" RESET, classification[selectionDisplayIndex]);
                
                selectionDisplayIndex++;
            }
            printf("\n\e[1F\e[5G");
            
            input = getch();
            navigation(input, &classIndex, 'x');
        }   

        RECIPES[recipeIndex].classification = classification[classIndex];
        classIndex = 0;

        printf("\n\e[1F\e[5G\e[0J%s", RECIPES[recipeIndex].classification);
        
        //------------------------------------------

        printf(PRP "\n\n    Number of Servings:\n    " RESET);
        getIntInput(&RECIPES[recipeIndex].servings, "\e[5G");
        clearBuffer();

        //------------------------------------------

        printf(
            PRP "\n    Ingredients: "
            GRY " Enter food item, quantity, unit, and calorie count\n\n" 
            RESET
        );

        int ingredientIndex = 0;
        addIngredient(RECIPES[recipeIndex].ingredients, &ingredientIndex, 20, 1);
        RECIPES[recipeIndex].ingredientCount = ingredientIndex;

        if(ingredientIndex == 20) {
            printf(
                RED "\n     [!] List full\n\n    "
                RESET LINE3 "\n" 
            );
        }

        //------------------------------------------

        printf(
            PRP "\n\n    Steps: " 
            GRY " Enter instructions\n" 
            RESET
        );

        int stepIndex = 0;
        addStep(RECIPES[recipeIndex].steps, &stepIndex, 15, 1);
        RECIPES[recipeIndex].stepCount = stepIndex;

        if(stepIndex == 15) {
            printf(
                RED "\n     [!] List full\n\n    "
                RESET LINE3 "\n" 
            );
        }

        //------------------------------------------

        printf(
            "\n\n" LINE "\n"
            GRY
            " * [ ENTER ] to continue adding dishes\n"
            " * [ X ] to return to update menu\n"
            RESET
        );

        input = getch();
        while(!INPUT_ENTER && !INPUT_EXIT) 
            input = getch();
        
        if(INPUT_ENTER)
            input = ' '; // Resets the input, important to not skip the following classification prompt

        recipeIndex++;
        *INDEX = recipeIndex;

        printf("\e[2F\e[0J");
    }

    if(*INDEX == 50) {
        printf(
            // "\n" LINE 
            RED "\n [!] List full\n"
            GRY " >>> Returning back to update menu\n" RESET
        );
        delayedLoad();
    }
    
}

void listRecipeTitles(recipe RECIPES[], int TOTAL) {
    char temp[20];
    int min = 0;
    
    int sortIndex = 0;
    while(sortIndex < TOTAL) {
        int recipeIndex = sortIndex;
        while(recipeIndex != TOTAL - 1) {
            if(strcmp(RECIPES[min].name, RECIPES[recipeIndex + 1].name) > 0) min = recipeIndex + 1;
            
            recipeIndex++;
        }
        
        strcpy(temp, RECIPES[sortIndex].name);
        strcpy(RECIPES[sortIndex].name, RECIPES[min].name);
        strcpy(RECIPES[min].name, temp);
        
        sortIndex++;
        min = sortIndex;
    }
    
    int printIndex = 0;
    while(printIndex < TOTAL) {
        printf(
            PRP "   %02d) " RESET "%-30s",
            printIndex+1, RECIPES[printIndex].name
        );
        
        printIndex++;
        if(!(printIndex % 4)) printf("\n\n\n");
    }

    printf("\n\n\n");
}

void displayRecipe(recipe RECIPE) {
    printf("\n" LINE "\n");

    int calories = 0;
    int ingredientIndex = 0;
    while(ingredientIndex < RECIPE.ingredientCount) {
        calories += RECIPE.ingredients[ingredientIndex].calories;

        ingredientIndex++;
    }
    ingredientIndex = 0;

    printf(
        "%-20s %-4d %16d calories",
        RECIPE.name,
        RECIPE.servings,
        calories
    );

    printf("\nIngredients:\n");
    while(ingredientIndex < RECIPE.ingredientCount) {
        printf(
            "    %d %s %s    %d calories\n",
            RECIPE.ingredients[ingredientIndex].quantity,
            RECIPE.ingredients[ingredientIndex].unit,
            RECIPE.ingredients[ingredientIndex].item,
            RECIPE.ingredients[ingredientIndex].calories

        );

        ingredientIndex++;
    }

    printf("::\nProcedures:\n");
    int stepIndex = 0;
    while(stepIndex < RECIPE.stepCount) {
        printf(
            "    %2d. %s\n",
            stepIndex+1,
            RECIPE.steps[stepIndex]
        );
        stepIndex++;
    }

    printf("::\n\n\n");
}

void scanRec(recipe RECIPES[], int TOTAL) {
    char input;

    int page = 1;

    while(!INPUT_EXIT) {
        printf("\nSCAN RECIPES\n\n" LINE "\n");


        printf("Recipe #%d\n", page);

        displayRecipe(RECIPES[page-1]);

        if(page < TOTAL) printf(GRY "\n * [ N ] to view next recipe");
        if(page > 1) printf(GRY "\n * [ B ] to view previous recipe");
        printf(GRY "\n * [ X ] to exit\n"RESET);

        input = getch();
        if((input == 'n' || input == 'N') && page < TOTAL) page++;
        if((input == 'b' || input == 'B') && page > 1) page--;

        WIPE
    }

    printf("\n");
    
}

int checkRecipe(recipe RECIPES[], int TOTAL) {
    listRecipeTitles(RECIPES, TOTAL);

    char search[21];
    printf(LINE2 PRP "\n    Enter recipe name:\n    " RESET);
    getStringInput(search,"%20[^\n]s", "\e[1F\e[5G");

    int index = 0;
    int recipeExists = 0;
    do {
        while(index < TOTAL && !recipeExists) {
            recipeExists = !strcmp(RECIPES[index].name, search);
            index++;
        }
        
        if(!recipeExists) {
            printf(RED "\e[1F\e[0J\e[25G\t\t[!] This recipe does not exist\e[5G" RESET);
            getStringInput(search, "%20[^\n]s", "\e[5G");
            clearBuffer();  
        }
    }
    while(!recipeExists);

    return index-1;

}

void searchRec(recipe RECIPES[], int TOTAL) {
    int index = checkRecipe(RECIPES, TOTAL);
    
    displayRecipe(RECIPES[index]);
    
    printf(GRY" * [ ENTER ] to return to update menu\n" RESET);
    
    char input;
    input = getch();
    while(!INPUT_ENTER) 
        input = getch();

    // printf("\e[1F\e[0J\e[25G\n");
    clearBuffer();  
}

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
    
    while(!INPUT_ENTER) {
        printf("\nMODIFY RECIPE\n");
        
        displayRecipe(RECIPE);
        printf(LINE "\n");
        
        option = selectionLooper(option, 4);
        selectionCarousel(option, 5, options, PRP);
        
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
    input = '\0';

    return option;
}

void modRec(recipe RECIPES[], int TOTAL) {
    printf("\nMODIFY RECIPE\n\n");

    int recipeIndex = checkRecipe(RECIPES, TOTAL);
    displayRecipe(RECIPES[recipeIndex]);
    printf(LINE);
    
    clearBuffer();
    WIPE

    int option = modRecMenu(RECIPES[recipeIndex]);
    // int singl

    while(option != 4) {
        WIPE
        
        switch(option) {
            case 0: 
                printf("\nADD INGREDIENTS\n\n");
                addIngredient(RECIPES[recipeIndex].ingredients, &RECIPES[recipeIndex].ingredientCount, 20, 0);
                break;
            case 1:
                if(RECIPES[recipeIndex].ingredientCount > 1) {
                    printf("\nDELETE INGREDIENTS\n\n");
                    deleteIngredient(RECIPES[recipeIndex].ingredients, &RECIPES[recipeIndex].ingredientCount);
                }
                break;
            case 2:
                printf("\nADD STEPS\n\n");
                addStep(RECIPES[recipeIndex].steps, &RECIPES[recipeIndex].stepCount, 15, 0);
                break;
            case 3:
                if(RECIPES[recipeIndex].stepCount > 1) {

                    printf("\nDELETE STEPS\n\n");
                }
                
                break;
            break;
        }
        
        WIPE
        option = modRecMenu(RECIPES[recipeIndex]);
    }
}

// void deleteRec() {}

// void exportRec() {}