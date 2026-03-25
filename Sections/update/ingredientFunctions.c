void addIngredients(ingredient INGREDIENT[], int *INDEX, int MAX, int INDENT) {
    char indent[5] = "";
    if(INDENT) strcpy(indent, "    ");

    char input;
    int ingredientIndex = *INDEX;
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
        
        printf(YLW "\n%s    Calorie Count:\n%s    " RESET, indent, indent);
        if(INDENT) getIntInput(&INGREDIENT[ingredientIndex].calories, "\e[9G" RESET);
        else getIntInput(&INGREDIENT[ingredientIndex].calories, "\e[5G" RESET);
        clearBuffer();
        
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
        *INDEX = ingredientIndex;

        if(ingredientIndex != MAX) {
            printf("\e[3F\e[0J");

            if(!INPUT_EXIT) {
                if(INDENT) printf("\n%s" LINE3 "\n", indent);
                else printf("\n" LINE "\n");
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

        WIPE

    }
    while(*TOTAL > 1 && input != 0);
}
