void genereateShopList(recipe RECIPES[], int R_ELEM) {
    printf(LINE "\nGENERATE SHOPPING LIST\n\n");

    listRecipeTitles(RECIPES, R_ELEM);

    printf(
        LINE2 PRP "\n    Enter the recipe's corresponding nuber:  " 
        GRY "Type 0 to exit" RESET
        "\n    "
    );

    recipe temp[50];

    int listSize = 0;
    int input = 67;
    while(listSize < 50 && input != 0) {
        getIntInput(&input, "\e[5G" RESET);

        if(input > R_ELEM) printf(RED "\e[1F\e[0J\e[20G\t\t[!] Please enter a valid recipe number");
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

            if(!isDuplicate) {
                printf("\e[1F\e[5G%d - %s\n\n", input, RECIPES[input-1].name);

                temp[listSize] = RECIPES[input-1];
                listSize++;
            }
        }
    }

    clearBuffer();

    // printf(LINE2);
    // int index = 0;
    // while(index < listSize) {
    //     printf()
    //     index++;
    // }

    printf(GRY" * [ X ] Return update menu\n" RESET);
    
    char input;
    input = getch();
    while(!INPUT_EXIT) 
        input = getch();
}

void recommenMenu(recipe RECIPES[], int R_ELEM) {
    printf(LINE "\nRECOMMEND MENU\n\n");

}