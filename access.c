void genereateShopList(recipe RECIPES[], int R_ELEM) {
    printf(LINE "\nGENERATE SHOPPING LIST\n\n");

    listRecipeTitles(RECIPES, R_ELEM, YLW);

    printf(
        LINE2 YLW "\n    Enter the recipe's corresponding nuber:  " 
        GRY "Type 0 to exit" RESET
        "\n    "
    );

    recipe temp[50];

    int listSize = 0;
    int input = 67;
    while(listSize < 50 && input != 0) {
        getIntInput(&input, "\e[5G" RESET, 1, 1);

        if(input > R_ELEM) printf(RED "\e[1F\e[0J\e[20G\t\t[!] Please enter a valid recipe number\n");
        else {
            int isDuplicate = 0;
            int existsIndex;
            for(existsIndex = 0; existsIndex < listSize && !isDuplicate; existsIndex++)
                if(!strcmp(temp[existsIndex].name, RECIPES[input-1].name)) {
                    printf(RED "\e[1F\e[0J\e[20G\t\t[!] This item already exists\n");
                    isDuplicate++;
                }

            if(!isDuplicate && input) {
                printf("\e[1F\e[5G%d - %s\n\n", input, RECIPES[input-1].name);

                temp[listSize] = RECIPES[input-1];
                listSize++;
            }
        }
    }
    clearBuffer();

    if(listSize) {
        printf(YLW "\n    Enter the number of people to cook for:\n    " RESET);

        getIntInput(&input, "\e[5G" RESET, 0, 1);
        clearBuffer();

        printf(
            "\n" LINE2 "\n"
            "    Shopping List\n\n"
        );

        int index;
        for(index = 0; index < listSize; index++) {
            int ingredientIndex;
            for(ingredientIndex = 0; ingredientIndex < temp[index].ingredientCount; ingredientIndex++) {
                temp[index].ingredients[ingredientIndex].quantity = calculateServingSize(temp[index].ingredients[ingredientIndex].quantity, temp[index].servings, input);

                printf(
                    YLW "        %d)" RESET " %g %s %s\n\n",
                    ingredientIndex+1,
                    temp[index].ingredients[ingredientIndex].quantity,
                    temp[index].ingredients[ingredientIndex].unit,
                    temp[index].ingredients[ingredientIndex].item
                );
            }
        }
    }

    printf(GRY"\n * [ X ] Return to menu\n" RESET);
    confirmBack();
}

void recommendMenu(recipe RECIPES[], int R_ELEM, ingredient CALORIE[], int C_ELEM) {
    printf(
        LINE "\nRECOMMEND MENU\n\n"
        YLW "    Enter target calorie intake:\n    " RESET
    );

    int input;
    getIntInput(&input, "\e[5G" RESET, 0, 1);
    clearBuffer();

    int calorieGoal = input;
    
    recipe temp[51];

    recipe final[3];
    int finalCount = 0;
    
    char classification[3][8] = {
        "Main",
        "Starter",
        "Dessert"
    };

    int index;
    for(index = 0; index < 3; index++) {
        int tempCount = 0;
        
        int recipeIndex;
        for(recipeIndex = 0; recipeIndex < R_ELEM; recipeIndex++) { //MAIN
            temp[50] = RECIPES[recipeIndex];
            
            int ingredientIndex;
            for(ingredientIndex = 0; ingredientIndex < temp[50].ingredientCount; ingredientIndex++) {
                temp[50].ingredients[ingredientIndex].quantity = calculateServingSize(temp[50].ingredients[ingredientIndex].quantity, temp[50].servings, 1);
            }
            temp[50].servings = 1;
                
            int calories = addCalories(&temp[50], CALORIE, C_ELEM);
            
            if(!strcmp(temp[50].classification, classification[index]) && calories <= calorieGoal) {
                temp[tempCount] = temp[50];
                tempCount++;
            }
        }
        
        if(tempCount) {
            int chosenIndex = 0;
            if(tempCount > 1) chosenIndex = rng(tempCount);
            
            int calories = addCalories(&temp[chosenIndex], CALORIE, C_ELEM);
            final[finalCount] = temp[chosenIndex];
            finalCount++;
            
            calorieGoal -= calories;
        }

    }
    
    if(!strcmp(final[1].classification, "Starter")) {
        temp[0] = final[0];
        final[0] = final[1];
        final[1] = temp[0];
    }


    printf(
        "\n" LINE2 "\n"
        "    Suggested Menu......Total Calories %d~\n"
        "\n" LINE2 "\n\n",
        input-calorieGoal
    );

    for(index = 0; index < finalCount; index ++) {
        printf("  >>> %s <<<\n\n", final[index].classification);
        displayRecipe(final[index], CALORIE, C_ELEM);
        printf("\n");

        if(index < finalCount-1) {
            printf(GRY " * [ ENTER ] to show next dish\e[1G" RESET);
            
            char input = getch();
            while(!INPUT_ENTER)
            input = getch();
        }

        CLEAN
    }

    printf(GRY"\n * [ X ] Return to menu\n" RESET);
    confirmBack();
}