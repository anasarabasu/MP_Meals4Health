
void addSteps(char STEPS[15][71], int *INDEX, int MAX, int INDENT) {
    char indent[5] = "";
    if(INDENT) strcpy(indent, "    ");

    char input;

    int stepIndex = *INDEX;
    while(stepIndex < MAX && !INPUT_EXIT) {
        printf(YLW "\n%s    Step #%d: " GRY "(out of %d)" "\n%s    " RESET, indent, stepIndex + 1, MAX, indent);

        if(INDENT) getStringInput(STEPS[stepIndex], "%70[^\n]s", "\e[1F\e[9G");
        else getStringInput(STEPS[stepIndex], "%70[^\n]s", "\e[1F\e[5G");

        //------------------------------------------

        printf(
            GRY "\n"
            "%s * [ ENTER ] to continue adding steps\n"
            "%s * [ X ] to finish\n"
            RESET,
            indent, indent
        );

        input = getch();
        while(!INPUT_ENTER && !INPUT_EXIT) 
            input = getch();

        stepIndex++;
        *INDEX =  stepIndex;
        
        printf("\e[3F\e[0J\n");
        clearBuffer();
    }
}

void deleteSteps(char STEPS[15][71], int *TOTAL) {
    int input = 0;
    do {
        printf("\nDELETE STEPS\n\n");

        int index = 0;
        while(index < *TOTAL) {
            printf(
                PRP "    %2d) "
                RESET " %s\n",
                index+1,
                STEPS[index]
            );
            index++;
        }

        printf(
            "\n"
            LINE2
            "\n    Enter the corresponding number of the step to delete:"
            GRY "  Type 0 to exit" RESET
            "\n    "
        );

        getIntInput(&input, "\e[5G" RESET);
        while(input > *TOTAL) {
            clearBuffer();
            printf("\e[1F\e[0J\e[20G\t\t" RED "[!] Please enter a valid number\e[5G" RESET);
            getIntInput(&input, "\e[5G" RESET);
        }

        printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment
        clearBuffer();

        if(input > 0 && input <= *TOTAL) {
            int shiftIndex = input;

            while(shiftIndex < *TOTAL) {
                strcpy(STEPS[shiftIndex - 1], STEPS[shiftIndex]);
                shiftIndex++;
            }

            (*TOTAL)--;
        }

        WIPE
    }
    while(*TOTAL > 1 && input != 0);
}

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
        addIngredients(RECIPES[recipeIndex].ingredients, &ingredientIndex, 20, 1);
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
        addSteps(RECIPES[recipeIndex].steps, &stepIndex, 15, 1);
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
    recipe temp;
    // char temp[20];
    int min = 0;
    
    int sortIndex = 0;
    while(sortIndex < TOTAL) {
        int recipeIndex = sortIndex;
        while(recipeIndex != TOTAL - 1) {
            if(strcmp(RECIPES[min].name, RECIPES[recipeIndex + 1].name) > 0) min = recipeIndex + 1;
            
            recipeIndex++;
        }
        
        temp = RECIPES[sortIndex];
        RECIPES[sortIndex] = RECIPES[min];
        RECIPES[min] =  temp;
        
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

// returns the index of the matching recipe
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
            index = 0;

            printf(RED "\e[1F\e[0J\e[25G\t\t[!] This recipe does not exist\e[5G" RESET);
            printf("\n");
            getStringInput(search, "%20[^\n]s", "\e[1F\e[5G");
        }
    }
    while(!recipeExists);

    printf("\e[1F\e[25G\t\t\e[0J\n"); // removes the [!] comment

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
                addIngredients(RECIPES[recipeIndex].ingredients, &RECIPES[recipeIndex].ingredientCount, 20, 0);
                break;
            case 1:
                if(RECIPES[recipeIndex].ingredientCount > 1) 
                    deleteIngredients(RECIPES[recipeIndex].ingredients, &RECIPES[recipeIndex].ingredientCount);
                
                break;
            case 2:
                printf("\nADD STEPS\n\n");
                addSteps(RECIPES[recipeIndex].steps, &RECIPES[recipeIndex].stepCount, 15, 0);
                break;
            case 3:
                if(RECIPES[recipeIndex].stepCount > 1) 
                    deleteSteps(RECIPES[recipeIndex].steps, &RECIPES[recipeIndex].stepCount);
                
                break;
            break;
        }
        
        WIPE
        option = modRecMenu(RECIPES[recipeIndex]);
    }
}

void deleteRec(recipe RECIPES[], int *INDEX) {
    char input;

    while (!INPUT_EXIT && *INDEX != 0) {
        printf("\nDELETE RECIPES\n\n");

        int index = checkRecipe(RECIPES, *INDEX);
        clearBuffer();

        int shiftIndex = input;
        while(shiftIndex < *INDEX) {
            RECIPES[shiftIndex] = RECIPES[shiftIndex + 1];
            shiftIndex++;
        }

        (*INDEX)--;
        
        printf(
            GRY "\n"
            " * Recipe #%02d successfully deleted\n\n"
            " * [ ENTER ] to continue deleting recipes\n"
            " * [ X ] to finish\n"
            RESET,
            index+1
        );

        input = getch();
        while(!INPUT_ENTER && !INPUT_EXIT) 
            input = getch();

        WIPE
    }
}
// void exportRec() {}