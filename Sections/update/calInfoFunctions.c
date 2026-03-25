void addCalInfo(ingredient FOOD[], int *INDEX) {
    printf("\nADD CALORIE INFO\n" RESET); 

    if(*INDEX < 50) {
        printf(GRY " * Enter food item, quantity, unit, and calorie count\n\n" RESET);
        addIngredients(FOOD, INDEX, 50, 0);
    }
    if(*INDEX == 50) {
        printf(
            "\n" LINE 
            RED "\n [!] List full\n"
            GRY " >>> Returning back to update menu\n" RESET
        );
        delayedLoad();
    }
}

void viewCalInfo(ingredient FOOD[], int INDEX) {
    char input;

    int rows = INDEX;
    int displayOffset = 0;
    
    while(!INPUT_EXIT) {
        printf("\nVIEW CALORIE INFO\n\n");

        char * col[4]= {
            "FOOD ITEM",
            "QUANTITY",
            "UNIT",
            "CALORIES"
        };
        
        printf(LINE2 " |      ");
        int colIndex = 0;
        while(colIndex != 4) {
            printf("%-11s%s%10s", "|", col[colIndex], "|");
            colIndex++;
        }
        printf("\n" LINE);
        
        int displayIndex = 0;
        while(displayIndex < 10 && displayIndex != rows) {
            printf(
                " |  %02d  |    %-20s    ||    %-19d    ||    %-15s    ||    %-19d    |\n"
                " |      |    %-20s    ||    %-19s    ||    %-15s    ||    %-19s    |\n"
                LINE2, 
                displayIndex + 1 + displayOffset,
                FOOD[displayIndex + displayOffset].item,
                FOOD[displayIndex + displayOffset].quantity,
                FOOD[displayIndex + displayOffset].unit,
                FOOD[displayIndex + displayOffset].calories,
                "", "", "", ""
            );
            displayIndex++;
        }
        
        if(rows > 10) printf(GRY "\n * [ N ] to view next 10 items");
        if(displayOffset) printf(GRY "\n * [ B ] to view previous 10 items");
        printf(GRY "\n * [ X ] to exit\n"RESET);
        
        input = getch();
        if((input == 'n' || input == 'N') && rows > 10) {
            displayOffset += 10;
            rows -= 10;
        }
        if((input == 'b' || input == 'B') && displayOffset) {
            displayOffset -= 10;
            rows += 10;
        }

        WIPE
    }

    printf("\n");
}

void saveCal(ingredient FOOD[]) {
    printf("\nSAVE CALORIE INFO\n\n");

    filename fileName;
    printf(YLW"    File Name: \n    " RESET);
    getStringInput(fileName, "%17[^\n]s", "\e[1F\e[5G");

    printf(GRY "\n * File saved successfully!\n");
    delayedLoad();

}


void loadCal() {}

