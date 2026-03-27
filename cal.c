void addCalInfo(ingredient FOOD[], int *F_ELEM) {
    printf(LINE "\nADD CALORIE INFO\n" RESET); 

    if(*F_ELEM < 50) {
        printf(GRY " * Enter food item, quantity, unit, and calorie count\n\n" RESET);
        addIngredients(FOOD, F_ELEM, 50, 0);
    }
    if(*F_ELEM == 50) {
        printf(
            "\n" LINE 
            RED "\n [!] List full\n"
            GRY " * [ X ] Return to update menu\n" RESET
        );

        char input = getch();
        while(!INPUT_EXIT)
            input = getch();
    }
}

void viewCalInfo(ingredient FOOD[], int F_ELEM) {    
    char input;

    int rows = F_ELEM;
    int displayOffset = 0;
    
    while(!INPUT_EXIT) {
        TOP
        CLEAN

        printf(LINE "\nVIEW CALORIE INFO\n\n");

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

    }

    printf("\n");
}

void saveCal(ingredient FOOD[], int F_ELEM) {
    printf(LINE "\nSAVE CALORIE INFO\n\n");

    filename fileName;
    if(checkFileExists(fileName, 1)) {
        printf(GRN "    [O] File saved successfully!" RESET);

        FILE *file;
        if(file = fopen(fileName, "w")) { 
            int index = 0;
            while(index < F_ELEM) {
                fprintf(
                    file, 
                    "%s\n"
                    "%d %s %d\n\n",
                    FOOD[index].item,
                    FOOD[index].quantity,
                    FOOD[index].unit,
                    FOOD[index].calories
                );

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


void loadCal(ingredient FOOD[], int *F_ELEM) {
    printf(LINE "\nLOAD CALORIE INFO\n\n");

    filename fileName;
    if(checkFileExists(fileName, 0)) {
        printf(GRN "    [O] File opened successfully!\n\n\n" RESET);

        FILE *file;
        if(file = fopen(fileName, "r")) { 
            ingredient temp;

            while(
                fscanf(
                    file,
                    "%s\n"
                    "%d %s %d\n\n",
                    temp.item,
                    &temp.quantity,
                    temp.unit,
                    &temp.calories
                ) == 4
                && *F_ELEM < 50
            ) {
                int itemExists = -1; // -1 doesnt exist // 0 ignore // 1 replace
                int stop = 0;

                int index = 0;
                while(index < *F_ELEM && !stop) { 
                    // printf("%d\n", !strcmp(FOOD[index].item, temp.item));
                    if(!strcmp(FOOD[index].item, temp.item)) {
                        stop = 1;

                        printf(
                            RED "    \"%s\" already exists, overwrite?"
                            GRY "  [ UP / DOWN ] to choose \n" RESET,
                            FOOD[index].item
                        );
                        
                        itemExists = 0;
                        char input = '\0';
                        while(!INPUT_ENTER) {
                            itemExists = selectionLooper(itemExists, 1);
                            
                            int displayIndex = 0;
                            string display[2] = {
                                "OLD\n"
                                "        %s\n"
                                "        %d %s %d\n\n",
                                "NEW\n"
                                "        %s\n"
                                "        %d %s %d\n\n",
                            };
                            
                            while(displayIndex < 2) {
                                if(itemExists == displayIndex) printf(RESET "        > ");
                                else printf(GRY "        > ");
                                
                                if(!displayIndex) {
                                    printf(
                                        display[displayIndex], 
                                        FOOD[index].item,
                                        FOOD[index]. quantity,FOOD[index].unit, FOOD[index].calories
                                    );    
                                }
                                else {
                                    printf(
                                        display[displayIndex], 
                                        temp.item,
                                        temp.quantity, temp.unit, temp.calories
                                    );
                                    
                                }
                                displayIndex++;
                            }
                            printf("\n\e[9F\0[0J");
                            
                            input = getch();
                            navigation(input, &itemExists, 'y');
                        }
                    }

                    index++;
                }

                if(itemExists) {
                    printf(
                        "    %-21s\n"
                        "    %d %s %d\n\e[0J",
                        temp.item,
                        temp.quantity,
                        temp.unit,
                        temp.calories
                    );
                    
                    if(itemExists == -1) {
                        printf(
                            GRY "    * Added as item #%d\n\n" RESET,
                            *F_ELEM+1
                        );
                        FOOD[*F_ELEM] = temp;
                        (*F_ELEM)++;
                    }
                    else {
                        printf(
                            GRY "    * Replaced item #%d\n\n" RESET,
                            index
                        );
                        FOOD[index-1] = temp;

                    }
                }
                else printf(GRY "\e[0J    * Overwrite cancelled\n\n" RESET);
            }
        }
        fclose(file);
    }
    
    printf(GRY"\n * [ X ]  Return to main menu\n" RESET);

    char input = getch();
    while(!INPUT_EXIT)
        input = getch();
}