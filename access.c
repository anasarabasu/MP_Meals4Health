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
        getIntInput(&input, "\e[5G" RESET);

        if(input > R_ELEM) printf(RED "\e[1F\e[0J\e[20G\t\t[!] Please enter a valid recipe number\n");
        else {
            int isDuplicate = 0;
            int existsIndex = 0;
            while(existsIndex < listSize && !isDuplicate) {
                if(!strcmp(temp[existsIndex].name, RECIPES[input-1].name)) {
                    printf(RED "\e[1F\e[0J\e[20G\t\t[!] This item already exists\n");
                    isDuplicate++;
                }
                existsIndex++;
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
        getIntInput(&input, "\e[5G" RESET);
        clearBuffer();

        printf(
            "\n" LINE2 "\n"
            "    Shopping List\n\n"
        );

        int index = 0;
        while(index < listSize) {
            int ingredientIndex = 0;
            while(ingredientIndex < temp[index].ingredientCount) {
                temp[index].ingredients[ingredientIndex].quantity = calculateSize(temp[index].ingredients[ingredientIndex].quantity, temp[index].servings, input);

                printf(
                    "        %d) %d %s %s\n",
                    ingredientIndex+1,
                    temp[index].ingredients[ingredientIndex].quantity,
                    temp[index].ingredients[ingredientIndex].unit,
                    temp[index].ingredients[ingredientIndex].item
                );

                ingredientIndex++;
            }
            index++;
        }

        printf("save?");
        getch();
    }
    else printf(GRY "\n\n * Empty list");

    printf(GRY"\n * [ X ] Return to menu\n" RESET);
    confirmBack();
}

void recommenMenu(recipe RECIPES[], int R_ELEM) {
    printf(LINE "\nRECOMMEND MENU\n\n");

    int input;
    printf(YLW "    Enter target calorie intake:\n    " RESET);
    getIntInput(&input, "\e[5G" RESET);
    clearBuffer();

    if(input) {

        printf("save?");
        getch();
    }
    else printf(GRY "\n\n * Empty list");

    printf(GRY"\n * [ X ] Return to menu\n" RESET);
    confirmBack();
}