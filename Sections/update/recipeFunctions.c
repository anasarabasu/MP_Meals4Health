void addRecipe(recipe RECIPES[], int *INDEX) {
    addRecDisplay();

    char input = '\0';

    int classIndex = 0;
    string classification[3]= {
        "Starter",
        "Main",
        "Dessert"
    };

    int recipeIndex = *INDEX;
    while(recipeIndex < 50 && RETURN_CONDITION) {
        printf(PRP "    Dish Name: " GRY " (%d out of 50)\n    " RESET, recipeIndex + 1);
        getStringInput(RECIPES[recipeIndex].name, "%[^\n]20s", "\e[1F\e[5G");

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
                printf(RED "\e[1F\e[0J\e[20G\t\t[!] This item already exists, please enter a new one\e[5G" RESET);
                getStringInput(RECIPES[recipeIndex].name, "%[^\n]20s", "\e[1F\e[5G");
            }
        }
        while(!isUnique);
        printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment
        
        //------------------------------------------

        printf(
            PRP "\n    Classification: " 
            GRY " [ ← / → ] to choose \n    " 
            RESET
        );

        while(input != '\n') {
            classIndex = selectionLooper(classIndex, 2);
            
            int selectionDisplayIndex = 0;
            while(selectionDisplayIndex != 3) {
                
                if(classIndex == selectionDisplayIndex) printf(">>>" BLINK);
                else printf(GRY ">>>");
                
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
        scanf("%d", &RECIPES[recipeIndex].servings);

        //------------------------------------------

        printf(
            PRP "\n    Ingredients: "
            GRY " Enter food item, quantity, unit, and calorie count\n\n" 
            RESET
        );

        int ingredientIndex = 0;

        addIngredient(RECIPES[recipeIndex].ingredients, &ingredientIndex, 20, 1);

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

        addStep(RECIPES[stepIndex].steps, &stepIndex, 15, 1);

        if(stepIndex == 15) {
            printf(
                RED "\n     [!] List full\n\n    "
                RESET LINE3 "\n" 
            );
        }

        //------------------------------------------

        printf(
            "\n\n\n\n" LINE "\n"
            GRY
            " * [ ANY KEY ] to continue adding dishes\n"
            " * [ X ] to finish\n"
            RESET
        );

        input = getch();
        while(input != '\n' && RETURN_CONDITION) 
            input = getch();
        
        if(RETURN_CONDITION)
            input = '\0'; // Resets the input, important to not skip the following classification prompt

        recipeIndex++;
        *INDEX = recipeIndex;

        printf("\e[2F\e[0J");

    }
    
}

// void modRec() {}
// void deleteRec() {}
// void listRec() {}
// void scanRec() {}
// void searchRec() {}
// void exportRec() {}