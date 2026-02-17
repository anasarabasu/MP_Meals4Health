void addCal(ingredient FOOD[], int *INDEX) {
    addCalDisplay();
    printf(GRY " * Enter food item, quantity, unit, and calorie count\n\n" RESET);

    char input = '\0';

    int foodIndex = *INDEX;
    while(foodIndex < 50 && RETURN_CONDITION) {
        printf(YLW "    Food Item: (%d out of 50)\n    " RESET, foodIndex + 1);
        getStringInput(FOOD[foodIndex].item, "%[^\n]20s", "\e[1F\e[5G");
        
        int isDuplicate = 0;
        do {
            int duplicateFound = 0;
            int uniqueIndex = 0;
            while((uniqueIndex != foodIndex + 1) && !duplicateFound) {
                if(uniqueIndex != foodIndex) {
                    if(!strcmp(FOOD[foodIndex].item, FOOD[uniqueIndex].item)) 
                        duplicateFound = 1;
                }
            
            uniqueIndex++;
            
            }
            isDuplicate = duplicateFound;
        
            if(isDuplicate) {
                printf(RED "\e[1F\e[0J\e[20G\t\t[!] This item already exists, please enter a new one\e[5G" RESET);
                getStringInput(FOOD[foodIndex].item, "%[^\n]20s", "\e[1F\e[5G");
            }
        }
        while(isDuplicate);
        printf("\e[1F\e[20G\t\t\e[0J\n"); // removes the [!] comment
        
        printf(YLW "\n    Quantity:\n    " RESET);
        scanf("%f", &FOOD[foodIndex].quantity);
        
        printf(YLW "\n    Unit:\n\n    " RESET);
        getStringInput(FOOD[foodIndex].unit, "%[^\n]20s", "\e[1F\e[5G");
        
        printf(YLW "\n    Calorie Count:\n    " RESET);
        scanf("%f", &FOOD[foodIndex].calories);
        
        
        getch();
        printf(
            GRY
            "\n"
            " * [ ANY KEY ] to continue\n"
            " * [ X ] to finish\n"
            RESET
        );

        input = getch();
        while(input != '\n' && RETURN_CONDITION) 
            input = getch();
        
        foodIndex++;
        *INDEX =  foodIndex;
        printf("\n" LINE "\n");
    }

    if(foodIndex == 50) {
        printf(
            RED "[!] List full\n" 
            GRY " >>> Returning back to update menu\n" RESET
        );
        delayedLoad();
    }
}

void viewCal(ingredient FOOD[], int TOTAL) {
    char input = '\0';

    int rows = TOTAL;
    int displayOffset = 0;
    
    while(RETURN_CONDITION) {
        viewCalDisplay();
        
        char * col[4]= {
            "FOOD ITEM",
            "QUANTITY",
            "UNIT",
            "CALORIES"
        };
        
        printf(LINE2 " |      ");
        int colIndex = 0;
        while(colIndex != 4) {
            printf("%-10s%s%10s", "|", col[colIndex], "|");
            colIndex++;
        }
        printf("\n" LINE);
        
        int displayIndex = 0;
        while(displayIndex < 10 && displayIndex != rows) {
            printf(
                " |  %02d  |    %-19s    ||    %-18.2f    ||    %-14s    ||    %-18.2f    |\n"
                " |      |    %-19s    ||    %-18s    ||    %-14s    ||    %-18s    |\n"
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

        clearScreen();
    }
}

void saveCal() {}
void loadCal() {}

