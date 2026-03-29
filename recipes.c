void addIngredients(ingredient INGREDIENT[], int *TOTAL, int MAX, int INDENT) {
    char indent[5] = "";
    if(INDENT) strcpy(indent, "    ");

    char input;
    int ingredientIndex;
    for(ingredientIndex = *TOTAL; ingredientIndex < MAX && !INPUT_EXIT; ingredientIndex++) {
        printf(
            YLW "%s    Food Item: " GRY " (%d out of %d)\n%s    " RESET, 
            indent, ingredientIndex + 1, MAX, indent
        );

        if(INDENT) getStringInput(INGREDIENT[ingredientIndex].item, "%20[^\n]s", "\e[1F\e[9G");
        
        else getStringInput(INGREDIENT[ingredientIndex].item, "%20[^\n]s", "\e[1F\e[5G");
        
        
        int isUnique = 1;
        do {
            int duplicateFound = 0;

            int uniqueIndex;
            for(uniqueIndex = 0; (uniqueIndex != ingredientIndex + 1) && !duplicateFound; uniqueIndex++)
                if(uniqueIndex != ingredientIndex) 
                    if(!strcmp(INGREDIENT[ingredientIndex].item, INGREDIENT[uniqueIndex].item)) 
                        duplicateFound = 1;
            
            isUnique = !duplicateFound;
        
            if(!isUnique) {
                if (INDENT) {
                    printf(RED "\e[1F\e[0J\e[29G\t\t%s[!] This item already exists, please enter a new one\e[9G" RESET, indent);
                    getStringInput(INGREDIENT[ingredientIndex].item, "%20[^\n]s", "\e[9G");
                } 
                else {
                    printf(RED "\e[1F\e[0J\e[25G\t\t%s[!] This item already exists, please enter a new one\e[5G" RESET, indent);
                    getStringInput(INGREDIENT[ingredientIndex].item, "%20[^\n]s", "\e[5G");
                }
            }
        }
        while(!isUnique);
        if(INDENT)
            printf("\e[1F\e[29G\t\t\e[0J\n"); // removes the [!] comment
        else
            printf("\e[1F\e[25G\t\t\e[0J\n"); // removes the [!] comment
        clearBuffer();


        //------------------------------------------
        
        printf(YLW "\n%s    Quantity:\n%s    " RESET, indent, indent);
        if(INDENT) getNumInput(&INGREDIENT[ingredientIndex].quantity, "\e[9G" RESET, 0, 0);
        else getNumInput(&INGREDIENT[ingredientIndex].quantity, "\e[5G" RESET, 0, 0);
        clearBuffer();

        
        //------------------------------------------

        printf(YLW "\n%s    Unit:\n%s    " RESET, indent, indent);
        if(INDENT) getStringInput(INGREDIENT[ingredientIndex].unit, "%20[^\n]s", "\e[1F\e[9G");
        else getStringInput(INGREDIENT[ingredientIndex].unit, "%20[^\n]s", "\e[1F\e[5G");
        clearBuffer();
        

        //------------------------------------------

        if(MAX == 50) {
            printf(YLW "\n%s    Calorie Count:\n%s    " RESET, indent, indent);
            float temp;
            getNumInput(&temp, "\e[5G" RESET, 0, 1);
            INGREDIENT[ingredientIndex].calories = (int) temp;
            clearBuffer();
        }
        
        //------------------------------------------

        if(ingredientIndex+1 < MAX) {
            printf(
                GRY "\n%s * [ ENTER ] to continue adding ingredients"
                "\n%s * [ X ] to finish\n" RESET, 
                indent, indent
            );
    
            input = getch();
            while(!INPUT_ENTER && !INPUT_EXIT) 
                input = getch();
        }
        else {
            printf(GRY "\n%s * [ X ] to finish\n" RESET, indent);
            confirmBack();
        }
        
        
        if(ingredientIndex != MAX) {
            printf("\e[3F\e[0J");
            
            if(!INPUT_EXIT) {
                if(INDENT) printf("\n%s" LINE3 "\n", indent);
                else printf("\n" LINE2 "\n");
            }
        }
    }
    *TOTAL = ingredientIndex;
}

void deleteIngredients(ingredient INGREDIENTS[], int *TOTAL) {
    int input = 0;
    do {
        printf(LINE "\nDELETE INGREDIENTS\n\n");

        int index;
        for(index = 0; index < *TOTAL; index++) 
            printf(
                PRP "    %2d) "
                RESET " %s\n",
                index+1,
                INGREDIENTS[index].item
            );

        printf(
            "\n"
            LINE2
            "\n    Enter the corresponding number of the ingredient to delete:"
            GRY "  Type 0 to exit" RESET
            "\n    "
        );

        getIntInput(&input, "\e[5G" RESET, 1, 1);
        while(input > *TOTAL) {
            clearBuffer();
            printf("\e[1F\e[0J\e[20G\t\t" RED "[!] Please enter a valid number\e[5G" RESET);
            getIntInput(&input, "\e[5G" RESET, 1, 1);
        }

        printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment
        clearBuffer();

        if(input > 0 && input <= *TOTAL) {
            int shiftIndex;
            for(shiftIndex = input; shiftIndex < *TOTAL; shiftIndex++)
                INGREDIENTS[shiftIndex - 1] = INGREDIENTS[shiftIndex];

            (*TOTAL)--;
            
            moveDisplay();
        }
    }
    while(*TOTAL > 1 && input != 0);
}


void addSteps(char STEPS[15][71], int *R_ELEM, int MAX, int INDENT) {
    char indent[5] = "";
    if(INDENT) strcpy(indent, "    ");

    char input;

    int stepIndex = *R_ELEM;
    for(stepIndex = *R_ELEM; stepIndex < MAX && !INPUT_EXIT; stepIndex++) {
        printf(YLW "\n%s    Step #%d: " GRY "(out of %d)" "\n%s    " RESET, indent, stepIndex + 1, MAX, indent);

        if(INDENT) getStringInput(STEPS[stepIndex], "%70[^\n]s", "\e[1F\e[9G");
        else getStringInput(STEPS[stepIndex], "%70[^\n]s", "\e[1F\e[5G");

        //------------------------------------------

        if(stepIndex+1 < MAX) {
            printf(
                GRY "\n%s * [ ENTER ] to continue adding steps"
                "\n%s * [ X ] to finish\n" RESET, 
                indent, indent
            );
    
            input = getch();
            while(!INPUT_ENTER && !INPUT_EXIT) 
                input = getch();
        }
        else {
            printf(GRY "\n%s * [ X ] to finish\n" RESET, indent);
            confirmBack();
        }

        printf("\e[3F\e[0J\n");
        clearBuffer();
    }
    *R_ELEM =  stepIndex;
}

void deleteSteps(char STEPS[15][71], int *R_ELEM) {
    int input = 0;
    do {
        printf(LINE "\nDELETE STEPS\n\n");

        int index;
        for(index = 0; index < *R_ELEM; index++) 
            printf(
                PRP "    %2d) "
                RESET " %s\n",
                index+1,
                STEPS[index]
            );

        printf(
            "\n"
            LINE2
            "\n    Enter the corresponding number of the step to delete:"
            GRY "  Type 0 to exit" RESET
            "\n    "
        );

        getIntInput(&input, "\e[5G" RESET, 1, 1);
        while(input > *R_ELEM) {
            clearBuffer();
            printf("\e[1F\e[0J\e[20G\t\t" RED "[!] Please enter a valid number\e[5G" RESET);
            getIntInput(&input, "\e[5G" RESET, 1, 1);
        }

        printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment
        clearBuffer();

        if(input > 0 && input <= *R_ELEM) {
            int shiftIndex;

            for(shiftIndex = input; shiftIndex < *R_ELEM; shiftIndex++) 
                strcpy(STEPS[shiftIndex - 1], STEPS[shiftIndex]);

            (*R_ELEM)--;
            
            moveDisplay();
        }
    }
    while(*R_ELEM > 1 && input != 0);
}


void addRecipe(recipe RECIPES[], int *R_ELEM) {
    printf(LINE "\nADD RECIPE\n" RESET);

    if(*R_ELEM < 50) {
        printf(
            GRY " * Enter dish name, classification, number of servings, list of ingredients, and procedures\n\n" RESET
        );
    }
    else {
        printf("\n" LINE );
    }
    char input;

    int recipeIndex;
    for(recipeIndex = *R_ELEM; recipeIndex < 50 && !INPUT_EXIT; recipeIndex++) {
        printf(PRP "    Dish Name: " GRY " (%d out of 50)\n    " RESET, recipeIndex + 1);
        
        getStringInput(RECIPES[recipeIndex].name, "%20[^\n]s", "\e[1F\e[5G");

        int isUnique = 1;
        do {
            int duplicateFound = 0;

            int uniqueIndex;
            for(uniqueIndex = 0; (uniqueIndex != recipeIndex + 1) && !duplicateFound; uniqueIndex++)
                if(uniqueIndex != recipeIndex) 
                    if(!strcmp(RECIPES[recipeIndex].name, RECIPES[uniqueIndex].name)) 
                        duplicateFound = 1;
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
        char classification[3][8] = {
            "Starter",
            "Main",
            "Dessert"
        };
        
        while(!INPUT_ENTER) {
            classIndex = selectionLooper(classIndex, 2);
            
            int selectionDisplayIndex;
            for(selectionDisplayIndex = 0; selectionDisplayIndex < 3; selectionDisplayIndex++) {
                if(classIndex == selectionDisplayIndex) printf(">");
                else printf(GRY ">");
                
                printf(" %-20s" RESET, classification[selectionDisplayIndex]);
            }
            printf("\n\e[1F\e[5G");
            
            input = getch();
            navigation(input, &classIndex, 'x');
        }   

        strcpy(RECIPES[recipeIndex].classification, classification[classIndex]);
        classIndex = 0;

        printf("\n\e[1F\e[5G\e[0J%s", RECIPES[recipeIndex].classification);
        
        //------------------------------------------

        printf(PRP "\n\n    Number of Servings:\n    " RESET);

        getIntInput(&RECIPES[recipeIndex].servings, "\e[5G" RESET, 0, 1);
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

        if(ingredientIndex == 20) printf(RED "     [!] List full\n\n    " RESET);

        //------------------------------------------

        printf(
            PRP "\n\n    Steps: " 
            GRY " Enter instructions\n" 
            RESET
        );

        int stepIndex = 0;
        addSteps(RECIPES[recipeIndex].steps, &stepIndex, 15, 1);
        RECIPES[recipeIndex].stepCount = stepIndex;

        if(stepIndex == 15) printf(RED "     [!] List full\n\n    " RESET);

        //------------------------------------------

        printf("\n\n" LINE2 "\n" GRY);
        if(recipeIndex+1 < 50) {
            printf(
                GRY " * [ ENTER ] to continue adding dishes\n"
                " * [ X ] to return to menu\n" RESET
            );

            input = getch();
            while(!INPUT_ENTER && !INPUT_EXIT) 
                input = getch();
        }
        else {
            printf(GRY " * [ X ] to return to menu\n" RESET);
            confirmBack();
        }

        if(INPUT_ENTER) input = ' '; // Resets the input, important to not skip the following classification prompt
        
        printf("\e[2F\e[0J");
    }
    *R_ELEM = recipeIndex;
}

void arrangeRecipeTitle(recipe RECIPES[], int R_ELEM) {
    recipe temp;
    
    int min;
    int sortIndex;
    for(sortIndex = 0; sortIndex < R_ELEM; sortIndex++) {
        min = sortIndex;

        int recipeIndex;
        for(recipeIndex = sortIndex; recipeIndex != R_ELEM - 1; recipeIndex++)
            if(strcmp(RECIPES[min].name, RECIPES[recipeIndex + 1].name) > 0) min = recipeIndex + 1;
        
        temp = RECIPES[sortIndex];
        RECIPES[sortIndex] = RECIPES[min];
        RECIPES[min] =  temp;
    }
}

void listRecipeTitles(recipe RECIPES[], int R_ELEM, char * COLOUR) {
    int printIndex;
    for(printIndex = 0; printIndex < R_ELEM; printIndex++) {
        if(!(printIndex % 4) && printIndex) printf("\n\n\n");
        printf(
            "%s   %02d) " RESET "%-30s",
            COLOUR,
            printIndex+1, RECIPES[printIndex].name
        );
    }

    printf("\n\n\n");
}

void displayRecipe(recipe RECIPE, ingredient CALORIE[], int C_ELEM) {
    int calories = addCalories(&RECIPE, CALORIE, C_ELEM);
        
        printf(
        PRP "    %s\n" RESET
        "        Serving size: %d\n"
        "        Total calories: %d\n",
        RECIPE.name,
        RECIPE.servings,
        calories
    );
        
    int ingredientIndex;

    printf(YLW "\n    Ingredients:\n" RESET );
    for(ingredientIndex = 0; ingredientIndex < RECIPE.ingredientCount; ingredientIndex++)
        printf(
            "        %g %s %s\e[64G%d calories\n",
            RECIPE.ingredients[ingredientIndex].quantity,
            RECIPE.ingredients[ingredientIndex].unit,
            RECIPE.ingredients[ingredientIndex].item,
            RECIPE.ingredients[ingredientIndex].calories

        );

    printf(YLW "\n    Procedures:\n" RESET);
    int stepIndex;
    for(stepIndex = 0; stepIndex < RECIPE.stepCount; stepIndex++)
        printf(
            "       %2d) %s\n",
            stepIndex+1,
            RECIPE.steps[stepIndex]
        );

    printf("\n\n");
}

void scanRec(recipe RECIPES[], int R_ELEM, ingredient CALORIE[], int C_ELEM) {
    int page = 1;
    
    char input;
    while(!INPUT_EXIT) {
        printf(
            LINE "\n    SCAN RECIPES\n\n"
            LINE2 "\n    Recipe #%d out of %d\n\n", 
            page,
            R_ELEM
        );

        displayRecipe(RECIPES[page-1], CALORIE, C_ELEM);
        
        if(page < R_ELEM) printf(GRY "\n * [ N ] to view next recipe");
        if(page > 1) printf(GRY "\n * [ B ] to view previous recipe");
        printf(GRY "\n * [ X ] to exit\n"RESET);
        
        CURSOR_POS
        
        input = getch();
        if((input == 'n' || input == 'N') && page < R_ELEM) {
            page++;
            moveDisplay();
        }
        else if((input == 'b' || input == 'B') && page > 1) {
            page--;
            moveDisplay();
        }
        else if(!INPUT_EXIT) {
            TOP 
            CLEAN
        }
    }

    printf("\n");
}

void scanRecByIngredient(recipe RECIPES[], int R_ELEM, ingredient CALORIE[], int C_ELEM) {
    printf(LINE "\nSCAN RECIPES BY INGREDIENT\n\n");

    char search[21];
    printf(LINE2 PRP "\n    Enter ingredient name:\n    " RESET);
    getStringInput(search,"%20[^\n]s", "\e[1F\e[5G");

    recipe temp[50];
    int recipesFound = 0;

    int index;
    for(index = 0; index < R_ELEM; index++) {
        int scanIngredients;
        for(scanIngredients = 0; scanIngredients < RECIPES[index].ingredientCount; scanIngredients++)
            if(!strcmp(RECIPES[index].ingredients[scanIngredients].item, search)) {
                temp[recipesFound] = RECIPES[index];
                recipesFound++;


            }
    }
    
    clearBuffer();

    char input;
    if(!recipesFound) {
        printf(
            RED "\e[2F\e[29G\t\t [!] That item is not used anywhere\n" RESET
            GRY "\n\n * [ X ] Return update menu\n" RESET
        );
        
        confirmBack();
    }
    else {
        int page = 1;

        TOP
        CLEAN

        while(!INPUT_EXIT) {
            printf(
                LINE "\nSCAN RECIPES BY INGREDIENT\n\n"
                LINE2 PRP "\n    Enter ingredient name:\n    " RESET
                "%s\n"
                "\n" LINE2 "\n"
                "    Recipe #%d out of %d\n\n",
                search,
                page,
                recipesFound
            );
            
            displayRecipe(temp[page-1], CALORIE, C_ELEM); 

            if(page < recipesFound) printf(GRY "\n * [ N ] to view next recipe");
            if(page > 1) printf(GRY "\n * [ B ] to view previous recipe");
            printf(GRY "\n * [ X ] to exit\n"RESET);
            
            CURSOR_POS

            input = getch();
            if((input == 'n' || input == 'N') && page < recipesFound) {
                page++;
                moveDisplay();
            }
            else if((input == 'b' || input == 'B') && page > 1) {
                page--;
                moveDisplay();
            }
            else if(!INPUT_EXIT) {
                TOP
                CLEAN
            }
        }
    }
}

// returns the index of the matching recipe
int checkRecipe(recipe RECIPES[], int R_ELEM) {
    listRecipeTitles(RECIPES, R_ELEM, PRP);

    char search[21];
    printf(LINE2 PRP "\n    Enter recipe name:\n    " RESET);
    getStringInput(search,"%20[^\n]s", "\e[1F\e[5G");

    int index = 0;
    int recipeExists = 0;
    while(!recipeExists) {
        for(; index < R_ELEM && !recipeExists; index++)
            recipeExists = !strcmp(RECIPES[index].name, search);
        
        if(!recipeExists) {
            index = 0;
    
            printf(RED "\e[1F\e[0J\e[25G\t\t[!] This recipe does not exist\e[5G" RESET);
            printf("\n");
            getStringInput(search, "%20[^\n]s", "\e[1F\e[5G");
        }

    }

    printf("\e[1F\e[25G\t\t\e[0J\n"); // removes the [!] comment

    return index-1;
}


void deleteRec(recipe RECIPES[], int *R_ELEM) {
    char input;
    while (!INPUT_EXIT && *R_ELEM != 0) {
        printf(LINE "\nDELETE RECIPES\n\n");

        int index = checkRecipe(RECIPES, *R_ELEM);
        clearBuffer();

        int shiftIndex;
        for(shiftIndex = index; shiftIndex < *R_ELEM; shiftIndex++) 
            RECIPES[shiftIndex] = RECIPES[shiftIndex + 1];


        (*R_ELEM)--;

        if(*R_ELEM) {
            printf(
                GRY "\n\n"
                " * Recipe #%d successfully deleted\n\n\n"
                " * [ ENTER ] to continue deleting recipes\n"
                " * [ X ] to finish\n"
                RESET,
                index+1
            );
            
            input = getch();
            while(!INPUT_ENTER && !INPUT_EXIT) 
                input = getch();
        }
        else {
            printf(GRY "\n\n * [ X ] to finish\n" RESET);
            confirmBack();
        }

        if(INPUT_ENTER) moveDisplay();
    }
}

void searchRec(recipe RECIPES[], int R_ELEM, ingredient CALORIE[], int C_ELEM) {
    printf(LINE "\nSEARCH RECIPE BY TITLE\n\n");

    int index = checkRecipe(RECIPES, R_ELEM);
    
    printf("\n" LINE2 "\n\n");
    displayRecipe(RECIPES[index], CALORIE, C_ELEM);
    
    printf(GRY" * [ X ] Return update menu\n" RESET);
    
    confirmBack();
    clearBuffer();  
}


void exportRec(recipe RECIPES[], int R_ELEM) {
    printf(LINE "\nEXPORT RECIPES\n\n");

    filename fileName;
    if(checkFileExists(fileName, 1)) {
        printf(GRN "    [O] File saved successfully!" RESET);

        FILE *file;
        if((file = fopen(fileName, "w"))) { 
            int index;
            for(index = 0; index < R_ELEM; index++) {
                fprintf(
                    file, 
                    "%s\n"
                    "%d %s\n"
                    "Ingredients %d\n",
                    RECIPES[index].name,
                    RECIPES[index].servings,
                    RECIPES[index].classification,
                    RECIPES[index].ingredientCount
                );

                int recIndex;
                for(recIndex = 0; recIndex < RECIPES[index].ingredientCount; recIndex++) 
                    fprintf(
                        file,
                        "%g %s %s\n",
                        RECIPES[index].ingredients[recIndex].quantity,
                        RECIPES[index].ingredients[recIndex]. unit,
                        RECIPES[index].ingredients[recIndex].item
                    );

                fprintf(
                    file,
                    "Steps %d\n",
                    RECIPES[index].stepCount
                );

                for(recIndex = 0; recIndex < RECIPES[index].stepCount; recIndex++) 
                    fprintf(
                        file,
                        "%s\n",
                        RECIPES[index].steps[recIndex]
                    );

                fprintf(file, "\n");
            }

            fclose(file);
        }
        else printf(RED "\n [!] Error!" RESET);
    }

    printf(GRY"\n\n * [ X ]  Return to menu\n" RESET);
    confirmBack();
}


void importRec(recipe RECIPES[], int *R_ELEM) {
    printf(LINE "\nIMPORT RECIPES\n\n");

    filename fileName;
    if(checkFileExists(fileName, 0)) {
        printf(GRN "    [O] File opened successfully!\n\n\n" RESET);

        FILE *file;
        if((file = fopen(fileName, "r"))) { 
            recipe temp;


            while(
                fscanf(
                    file, 
                    "%20[^\n]"
                    "%d %s\n",
                    temp.name,
                    &temp.servings,
                    temp.classification
                ) == 3
                && *R_ELEM < 50
            ) {
                fscanf(file, "Ingredients %d\n", &temp.ingredientCount);

                int recIndex;
                for(recIndex = 0; recIndex < temp.ingredientCount; recIndex++) 
                    fscanf(
                        file,
                        "%f %s %[^\n]\n",
                        &temp.ingredients[recIndex].quantity,
                        temp.ingredients[recIndex]. unit,
                        temp.ingredients[recIndex].item
                    );
                
                fscanf(file, "Steps %d\n", &temp.stepCount);
                
                for(recIndex = 0; recIndex < temp.stepCount; recIndex++) 
                    fscanf(file, "%[^\n]\n", temp.steps[recIndex]);
                
                int itemExists = -1;
                int stop = 0;

                int index;
                for(index = 0; index < *R_ELEM && !stop; index++) {
                    if(!strcmp(RECIPES[index].name, temp.name)) {
                        stop++;

                        printf(
                            RED "    \"%s\" already exists, overwrite?"
                            GRY "  [ UP / DOWN ] to choose \n" RESET,
                            RECIPES[index].name
                        );

                        itemExists = 0;
                        char input = '\0';
                        while(!INPUT_ENTER) {
                            itemExists = selectionLooper(itemExists, 1);

                            string display[2] = {
                                "OLD\n",
                                "NEW\n"
                            };

                            int displayIndex;
                            for(displayIndex = 0; displayIndex < 2; displayIndex++) {
                                if(itemExists == displayIndex) printf(RESET "        > ");
                                else printf(GRY "        > ");

                                printf(display[displayIndex]);
                            }

                            input = getch();
                            navigation(input, &itemExists, 'y');
                            
                            printf("\n\e[3F\e[0J");

                        }
                    }
                }

                if(itemExists) {
                    printf("    %s\n", temp.name);

                    if(itemExists == -1) {
                        printf(GRY "    * Added as recipe #%d\n\n" RESET, *R_ELEM+1);
                        RECIPES[*R_ELEM] = temp;
                        (*R_ELEM)++;
                    }
                    else {
                        printf(GRY "    * Replaced recipe #%d\n\n" RESET, index);
                        RECIPES[index-1] = temp;
                    }
                }            
                else printf(GRY "\e[0J    * Overwrite cancelled\n\n" RESET);
            }
        }
        fclose(file);
    }
    
    printf(GRY"\n * [ X ]  Return to menu\n" RESET);
    confirmBack();
}