void addIngredient(ingredient INGREDIENT[], int *INDEX, int MAX, int INDENT) {
    char indent[5] = "";
    if(INDENT) strcpy(indent, "    ");

    char input = '\0';

    // int ingredientIndex = 18;
    int ingredientIndex = *INDEX;
    while(ingredientIndex < MAX && RETURN_CONDITION) {
        printf(YLW "%s    Food Item: " GRY " (%d out of %d)\n%s    " RESET, indent, ingredientIndex + 1, MAX, indent);
        if(INDENT) {
            if(!ingredientIndex) printf("\n");
            getStringInput(INGREDIENT[ingredientIndex].item, "%[^\n]20s", "\e[1F\e[9G");
        }
        else getStringInput(INGREDIENT[ingredientIndex].item, "%[^\n]20s", "\e[1F\e[5G");
        
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
                    printf(RED "\e[1F\e[0J\e[20G\t\t%s[!] This item already exists, please enter a new one\e[9G" RESET, indent);
                    getStringInput(INGREDIENT[ingredientIndex].item, "%[^\n]20s", "\e[1F\e[9G");
                } 
                else {
                    printf(RED "\e[1F\e[0J\e[20G\t\t%s[!] This item already exists, please enter a new one\e[5G" RESET, indent);
                    getStringInput(INGREDIENT[ingredientIndex].item, "%[^\n]20s", "\e[1F\e[5G");
                }
            }
        }
        while(!isUnique);
        printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment
        
        //------------------------------------------
        
        printf(YLW "\n%s    Quantity:\n%s    " RESET, indent, indent);
        scanf("%f", &INGREDIENT[ingredientIndex].quantity);
        
        //------------------------------------------

        printf(YLW "\n%s    Unit:\n\n%s    " RESET, indent, indent);
        if(INDENT) getStringInput(INGREDIENT[ingredientIndex].unit, "%[^\n]20s", "\e[1F\e[9G");
        else getStringInput(INGREDIENT[ingredientIndex].unit, "%[^\n]20s", "\e[1F\e[5G");
        
        //------------------------------------------
        
        printf(YLW "\n%s    Calorie Count:\n%s    " RESET, indent, indent);
        scanf("%f", &INGREDIENT[ingredientIndex].calories);
        
        //------------------------------------------

        getch();
        printf(
            GRY "\n"
            "%s * [ ANY KEY ] to continue adding ingredients\n"
            "%s * [ X ] to finish\n"
            RESET,
            indent, indent
        );

        input = getch();
        while(input != '\n' && RETURN_CONDITION) 
            input = getch();
        
        ingredientIndex++;
        *INDEX = ingredientIndex;
        if(ingredientIndex != MAX) {
            printf("\e[3F\e[0J");

            if(RETURN_CONDITION) {
                if(INDENT) printf("\n%s" LINE3 "\n", indent);
                else printf("\n" LINE "\n");
            }
        }
    }
}

void addStep(char STEPS[15][70], int *INDEX, int MAX, int INDENT) {
    char indent[5] = "";
    if(INDENT) strcpy(indent, "    ");

    char input = '\0';

    int stepIndex = *INDEX;
    while(stepIndex < MAX && RETURN_CONDITION) {
        printf(YLW "\n%s    Step #%d: " GRY "(out of %d)" "\n%s    " RESET, indent, stepIndex + 1, MAX + 1, indent);
        if(INDENT) {
            getStringInput(STEPS[stepIndex], "%[^\n]70s", "\e[1F\e[9G");
        }

        //------------------------------------------

        printf(
            GRY "\n"
            "%s * [ ANY KEY ] to continue adding steps\n"
            "%s * [ X ] to finish\n"
            RESET,
            indent, indent
        );

        input = getch();
        while(input != '\n' && RETURN_CONDITION) 
            input = getch();

        stepIndex++;
        *INDEX =  stepIndex;
        
        printf("\e[3F\e[0J");
    }
}