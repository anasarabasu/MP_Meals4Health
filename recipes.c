void addIngredients(ingredient INGREDIENT[], int *TOTAL, int MAX, int INDENT) {
    char indent[5] = "";
    if(INDENT) strcpy(indent, "    ");

    char input;
    int ingredientIndex = *TOTAL;
    while(ingredientIndex < MAX && !INPUT_EXIT) {
        printf(
            YLW "%s    Food Item: " GRY " (%d out of %d)\n%s    " RESET, 
            indent, ingredientIndex + 1, MAX, indent
        );

        if(INDENT) getStringInput(INGREDIENT[ingredientIndex].item, "%20[^\n]s", "\e[1F\e[9G");
        
        else getStringInput(INGREDIENT[ingredientIndex].item, "%20[^\n]s", "\e[1F\e[5G");
        
        
        int isUnique = 1;
        do {
            int duplicateFound = 0;

            int uniqueIndex = 0;
            while((uniqueIndex != ingredientIndex + 1) && !duplicateFound) {
                if(uniqueIndex != ingredientIndex) 
                    if(!strcmp(INGREDIENT[ingredientIndex].item, INGREDIENT[uniqueIndex].item)) 
                        duplicateFound = 1;
            
                uniqueIndex++;
            }
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
        if(INDENT) getIntInput(&INGREDIENT[ingredientIndex].quantity, "\e[9G" RESET);
        else getIntInput(&INGREDIENT[ingredientIndex].quantity, "\e[5G" RESET);
        clearBuffer();

        
        //------------------------------------------

        printf(YLW "\n%s    Unit:\n%s    " RESET, indent, indent);
        if(INDENT) getStringInput(INGREDIENT[ingredientIndex].unit, "%20[^\n]s", "\e[1F\e[9G");
        else getStringInput(INGREDIENT[ingredientIndex].unit, "%20[^\n]s", "\e[1F\e[5G");
        clearBuffer();
        

        //------------------------------------------

        if(MAX == 50) {
            printf(YLW "\n%s    Calorie Count:\n%s    " RESET, indent, indent);
            // if(INDENT) getIntInput(&INGREDIENT[ingredientIndex].calories, "\e[9G" RESET);
            getIntInput(&INGREDIENT[ingredientIndex].calories, "\e[5G" RESET);
            clearBuffer();
        }
        
        //------------------------------------------

        printf(
            GRY "\n"
            "%s * [ ENTER ] to continue adding ingredients\n"
            "%s * [ X ] to finish\n"
            RESET,
            indent, indent
        );

        input = getch();
        while(!INPUT_ENTER && !INPUT_EXIT) 
            input = getch();
        
        ingredientIndex++;
        *TOTAL = ingredientIndex;

        if(ingredientIndex != MAX) {
            printf("\e[3F\e[0J");

            if(!INPUT_EXIT) {
                if(INDENT) printf("\n%s" LINE3 "\n", indent);
                else printf("\n" LINE2 "\n");
            }
        }
    }
}

void deleteIngredients(ingredient INGREDIENTS[], int *TOTAL) {
    int input = 0;
    do {
        printf("\nDELETE INGREDIENTS\n\n");

        int index = 0;
        while(index < *TOTAL) {
            printf(
                PRP "    %2d) "
                RESET " %s\n",
                index+1,
                INGREDIENTS[index].item
            );
            index++;
        }

        printf(
            "\n"
            LINE2
            "\n    Enter the corresponding number of the ingredient to delete:"
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
                INGREDIENTS[shiftIndex - 1] = INGREDIENTS[shiftIndex];
                shiftIndex++;
            }

            (*TOTAL)--;
        }

        TOP
    }
    while(*TOTAL > 1 && input != 0);
}


void addSteps(char STEPS[15][71], int *R_ELEM, int MAX, int INDENT) {
    char indent[5] = "";
    if(INDENT) strcpy(indent, "    ");

    char input;

    int stepIndex = *R_ELEM;
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
        *R_ELEM =  stepIndex;
        
        printf("\e[3F\e[0J\n");
        clearBuffer();
    }
}

void deleteSteps(char STEPS[15][71], int *R_ELEM) {
    int input = 0;
    do {
        printf("\nDELETE STEPS\n\n");

        int index = 0;
        while(index < *R_ELEM) {
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
        while(input > *R_ELEM) {
            clearBuffer();
            printf("\e[1F\e[0J\e[20G\t\t" RED "[!] Please enter a valid number\e[5G" RESET);
            getIntInput(&input, "\e[5G" RESET);
        }

        printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment
        clearBuffer();

        if(input > 0 && input <= *R_ELEM) {
            int shiftIndex = input;

            while(shiftIndex < *R_ELEM) {
                strcpy(STEPS[shiftIndex - 1], STEPS[shiftIndex]);
                shiftIndex++;
            }

            (*R_ELEM)--;
        }

        TOP
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

    int recipeIndex = *R_ELEM;
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
        char classification[3][8] = {
            "Starter",
            "Main",
            "Dessert"
        };
        
        while(!INPUT_ENTER) {
            classIndex = selectionLooper(classIndex, 2);
            
            int selectionDisplayIndex = 0;
            while(selectionDisplayIndex < 3) {
                
                if(classIndex == selectionDisplayIndex) printf(">");
                else printf(GRY ">");
                
                printf(" %-20s" RESET, classification[selectionDisplayIndex]);
                
                selectionDisplayIndex++;
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
            "\n\n" LINE2 "\n"
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
        *R_ELEM = recipeIndex;

        printf("\e[2F\e[0J");
    }

    if(*R_ELEM == 50) {
        printf(
            // "\n" LINE 
            RED "\n [!] List full\n"
            GRY " [ X ] Return to update menu\n" RESET
        );
        
        char input = getch();
        while(!INPUT_EXIT)
            input = getch();

    }
    
}

void listRecipeTitles(recipe RECIPES[], int R_ELEM) {
    recipe temp;
    // char temp[20];
    int min = 0;
    
    int sortIndex = 0;
    while(sortIndex < R_ELEM) {
        int recipeIndex = sortIndex;
        while(recipeIndex != R_ELEM - 1) {
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
    while(printIndex < R_ELEM) {
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
    int calories = 0;
    int ingredientIndex = 0;
    while(ingredientIndex < RECIPE.ingredientCount) {
        calories += RECIPE.ingredients[ingredientIndex].calories;

        ingredientIndex++;
    }
    ingredientIndex = 0;

    printf(
        "    %-20s %-4d %16d calories",
        RECIPE.name,
        RECIPE.servings,
        calories
    );

    printf("\n    Ingredients:\n");
    while(ingredientIndex < RECIPE.ingredientCount) {
        printf(
            "        %d %s %s    %d calories\n",
            RECIPE.ingredients[ingredientIndex].quantity,
            RECIPE.ingredients[ingredientIndex].unit,
            RECIPE.ingredients[ingredientIndex].item,
            RECIPE.ingredients[ingredientIndex].calories

        );

        ingredientIndex++;
    }

    printf("\n    Procedures:\n");
    int stepIndex = 0;
    while(stepIndex < RECIPE.stepCount) {
        printf(
            "        %2d. %s\n",
            stepIndex+1,
            RECIPE.steps[stepIndex]
        );
        stepIndex++;
    }

    printf("\n\n");
}

void scanRec(recipe RECIPES[], int R_ELEM) {
    int page = 1;
    
    char input;
    while(!INPUT_EXIT) {
        TOP
        CLEAN

        printf(
            LINE "\n    SCAN RECIPES\n\n"
            LINE2 "\n    Recipe #%d\n\n", 
            page
        );

        displayRecipe(RECIPES[page-1]);

        if(page < R_ELEM) printf(GRY "\n * [ N ] to view next recipe");
        if(page > 1) printf(GRY "\n * [ B ] to view previous recipe");
        printf(GRY "\n * [ X ] to exit\n"RESET);

        CURSOR_POS

        input = getch();
        if((input == 'n' || input == 'N') && page < R_ELEM) page++;
        if((input == 'b' || input == 'B') && page > 1) page--;

    }

    printf("\n");
    
}

void scanRecByIngredient(recipe RECIPES[], int R_ELEM) {
    printf(LINE "\nSCAN RECIPES BY INGREDIENT\n\n");

    char search[21];
    printf(LINE2 YLW "\n    Enter ingredient name:\n    " RESET);
    getStringInput(search,"%20[^\n]s", "\e[1F\e[5G");

    recipe temp[50];
    int recipesFound = 0;

    int index = 0;
    while(index < R_ELEM) {
        int scanIngredients = 0;
        while(scanIngredients < RECIPES[index].ingredientCount) {
            if(!strcmp(RECIPES[index].ingredients[scanIngredients].item, search)) {
                temp[recipesFound] = RECIPES[index];
                recipesFound++;


            }
            scanIngredients++;
        }
        index++;
    }
    
    clearBuffer();

    char input;
    if(!recipesFound) {
        printf(
            RED "\e[2F\e[29G\t\t [!] That item is not used anywhere\n" RESET
            GRY "\n\n * [ X ] Return update menu\n" RESET
        );
        
        input = getch();
        while(!INPUT_EXIT) 
            input = getch();

    }
    else {
        printf("\n" LINE2 "\n");
        
        int page = 1;

        while(!INPUT_EXIT) {
            TOP
            printf("\e[11E");
            CLEAN 
            
            displayRecipe(temp[page-1]);

            if(page < recipesFound) printf(GRY "\n * [ N ] to view next recipe");
            if(page > 1) printf(GRY "\n * [ B ] to view previous recipe");
            printf(GRY "\n * [ X ] to exit\n"RESET);
            
            CURSOR_POS

            input = getch();
            if((input == 'n' || input == 'N') && page < recipesFound) page++;
            if((input == 'b' || input == 'B') && page > 1) page--;

        }
    }
}

// returns the index of the matching recipe
int checkRecipe(recipe RECIPES[], int R_ELEM) {
    listRecipeTitles(RECIPES, R_ELEM);

    char search[21];
    printf(LINE2 PRP "\n    Enter recipe name:\n    " RESET);
    getStringInput(search,"%20[^\n]s", "\e[1F\e[5G");

    int index = 0;
    int recipeExists = 0;
    while(!recipeExists) {
        while(index < R_ELEM && !recipeExists) {
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

    printf("\e[1F\e[25G\t\t\e[0J\n"); // removes the [!] comment

    return index-1;
}


void deleteRec(recipe RECIPES[], int *R_ELEM) {
    char input;

    while (!INPUT_EXIT && *R_ELEM != 0) {
        printf(LINE "\nDELETE RECIPES\n\n");

        int index = checkRecipe(RECIPES, *R_ELEM);
        clearBuffer();

        int shiftIndex = input;
        while(shiftIndex < *R_ELEM) {
            RECIPES[shiftIndex] = RECIPES[shiftIndex + 1];
            shiftIndex++;
        }

        (*R_ELEM)--;
        
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

        TOP
    }
}

void searchRec(recipe RECIPES[], int R_ELEM) {
    printf(LINE "\nSEARCH RECIPE BY TITLE\n\n");

    int index = checkRecipe(RECIPES, R_ELEM);
    
    printf("\n" LINE2 "\n\n");
    displayRecipe(RECIPES[index]);
    
    printf(GRY" * [ X ] Return update menu\n" RESET);
    
    char input;
    input = getch();
    while(!INPUT_EXIT) 
        input = getch();

    clearBuffer();  
}


void exportRec(recipe RECIPES[], int R_ELEM) {
    printf(LINE "\nEXPORT RECIPES\n\n");

    filename fileName;
    if(checkFileExists(fileName, 1)) {
        printf(GRY "    * File saved successfully!" RESET);

        FILE *file;
        if(file = fopen(fileName, "w")) { 
            int index = 0;
            while(index < R_ELEM) {
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

                int recIndex = 0;
                while(recIndex < RECIPES[index].ingredientCount) {
                    fprintf(
                        file,
                        "%d %s %s\n",
                        RECIPES[index].ingredients[recIndex].quantity,
                        RECIPES[index].ingredients[recIndex]. unit,
                        RECIPES[index].ingredients[recIndex].item
                    );
                    recIndex++;
                }

                fprintf(
                    file,
                    "Steps %d\n",
                    RECIPES[index].stepCount
                );

                recIndex = 0;
                while(recIndex < RECIPES[index].stepCount) {
                    fprintf(
                        file,
                        "%s\n",
                        RECIPES[index].steps[recIndex]
                    );
                    recIndex++;
                }

                fprintf(file, "\n");
                index++;
            }

            fclose(file);
        }
        else printf(RED "\n [!] Error!" RESET);
    }

    printf(GRY"\n\n * [ X ]  Return to main menu\n" RESET);

    char input = getch();
    while(!INPUT_EXIT)
        input = getch();
}


void parseString() {}


void importRec(recipe RECIPES[], int *R_ELEM) {
    printf(LINE "\nEXPORT RECIPES\n\n");

    filename fileName;
    if(checkFileExists(fileName, 0)) {
        printf(GRY "    * File opened successfully!\n\n\n" RESET);

        FILE *file;
        if(file = fopen(fileName, "r")) { 
            recipe temp;

            int index = 0;
            while(
                fscanf(
                    file, 
                    "%s",
                    // "%d %s\n",
                    // "Ingredients %d\n",
                    temp.name
                    // temp.servings,
                    // temp.classification
                    // temp.ingredientCount
                ) 

                && *R_ELEM < 50
            ) {
                // int recIndex = 0;
                // while(temp.ingredientCount) {
                //     fprintf(
                //         file,
                //         "%d %s %s\n",
                //         temp.ingredients[recIndex].quantity,
                //         temp.ingredients[recIndex]. unit,
                //         temp.ingredients[recIndex].item
                //     );
                //     recIndex++;
                // }

                // fscanf(
                //     file,
                //     "Steps %d\n",
                //     temp.stepCount
                // );

                // recIndex = 0;
                // while(recIndex < temp.stepCount) {
                //     fprintf(
                //         file,
                //         "%s\n",
                //         temp.steps[recIndex]
                //     );
                //     recIndex++;
                // }    
                index++;
                printf("%d", index);
            }
        }
        fclose(file);
    }
    
    printf(GRY"\n * [ X ]  Return to main menu\n" RESET);

    char input = getch();
    while(!INPUT_EXIT)
        input = getch();
}