void viewCalInfo(ingredient FOOD[], int F_ELEM) {    
    int rows = F_ELEM;
    int displayOffset = 0;
    
    char input = '\0';
    while(!INPUT_EXIT) {
        printf(LINE "\nVIEW CALORIE INFO\n\n");
        
        char * col[4]= {
            YLW "FOOD ITEM" RESET,
            YLW "QUANTITY" RESET,
            YLW "UNIT" RESET,
            YLW "CALORIES" RESET
        };
        
        printf(LINE2 " |      ");
        
        int colIndex;
        for(colIndex = 0; colIndex != 4; colIndex++) 
            printf("%-11s%s%10s" , "|", col[colIndex], "|");
    
        printf("\n" LINE);
        
        int displayIndex;
        for(displayIndex = 0; displayIndex < 10 && displayIndex != rows; displayIndex++) 
        printf(
            " |  %02d  |    %-20s    ||    %-19g    ||    %-15s    ||    %-19g    |\n"
            " |      |    %-20s    ||    %-19s    ||    %-15s    ||    %-19s    |\n"
            LINE2, 
            displayIndex + 1 + displayOffset,
            FOOD[displayIndex + displayOffset].item,
            FOOD[displayIndex + displayOffset].quantity,
            FOOD[displayIndex + displayOffset].unit,
            FOOD[displayIndex + displayOffset].calories,
            "", "", "", ""
        );
        
        if(rows > 10) printf(GRY "\n * [ N ] to view next 10 items");
        if(displayOffset) printf(GRY "\n * [ B ] to view previous 10 items");
        printf(GRY "\n * [ X ] to exit\n"RESET);
        
        
        input = getch();
        if((input == 'n' || input == 'N') && rows > 10) {
            displayOffset += 10;
            rows -= 10;

            moveDisplay();
        }
        else if((input == 'b' || input == 'B') && displayOffset) {
            displayOffset -= 10;
            rows += 10;

            moveDisplay();
        }
        else if(!INPUT_EXIT) {
            TOP 
            CLEAN
        }
    }

    printf("\n");
}




void saveCal(ingredient FOOD[], int F_ELEM) {
    printf(LINE "\nSAVE CALORIE INFO\n\n");

    char fileName[21];
    if(checkFileExists(fileName, 1)) {
        printf(GRN "\n    [O] File saved successfully!" RESET);

        FILE *file;
        if((file = fopen(fileName, "w"))) { 
            int index;
            for(index = 0; index < F_ELEM; index++)
                fprintf(
                    file, 
                    "%s\n"
                    "%g %s %g\n\n",
                    FOOD[index].item,
                    FOOD[index].quantity,
                    FOOD[index].unit,
                    FOOD[index].calories
                );

            fclose(file);
        }
        else printf(RED "\n [!] Error!" RESET);
    }

    printf(GRY"\n\n * [ X ]  Return to menu\n" RESET);
    confirmBack();
}




void loadCal(ingredient FOOD[], int *F_ELEM) {
    printf(LINE "\nLOAD CALORIE INFO\n\n");

    char fileName[21];
    if(checkFileExists(fileName, 0)) {
        printf(GRN "    [O] File opened successfully!\n\n\n" RESET);

        FILE *file;
        if((file = fopen(fileName, "r"))) { 
            ingredient temp;

            while(
                fscanf(
                    file,
                    "%[^\n]"
                    "%f %s %g\n\n",
                    temp.item,
                    &temp.quantity,
                    temp.unit,
                    &temp.calories
                ) == 4
                && *F_ELEM < 50
            ) {
                int itemExists = -1; // -1 doesnt exist // 0 ignore // 1 replace
                int stop = 0;

                int index;
                for(index = 0; index < *F_ELEM && !stop; index++) { 
                    if(!strcmp(FOOD[index].item, temp.item)) {
                        stop++;

                        printf(
                            RED "    \"%s\" already exists, overwrite?"
                            GRY "  [ UP / DOWN ] to choose \n" RESET,
                            FOOD[index].item
                        );
                        
                        itemExists = 0;
                        char input = '\0';
                        while(!INPUT_ENTER) {
                            itemExists = selectionLooper(itemExists, 1);
                            
                            string display[2] = {
                                "OLD\n"
                                "        %s\n"
                                "        %g %s %g\n\n",
                                "NEW\n"
                                "        %s\n"
                                "        %g %s %g\n\n",
                            };
                            
                            int displayIndex;
                            for(displayIndex = 0; displayIndex < 2; displayIndex++) {
                                if(itemExists == displayIndex) printf(RESET "        > ");
                                else printf(GRY "        > ");
                                
                                if(!displayIndex) {
                                    printf(
                                        display[displayIndex], 
                                        FOOD[index].item,
                                        FOOD[index]. quantity, FOOD[index].unit, FOOD[index].calories
                                    );    
                                }
                                else {
                                    printf(
                                        display[displayIndex], 
                                        temp.item,
                                        temp.quantity, temp.unit, temp.calories
                                    );
                                    
                                }
                            }
                            
                            input = getch();
                            navigation(input, &itemExists, 'y');

                            printf("\n\e[9F\e[0J");
                        }
                    }
                }

                if(itemExists) {
                    printf(
                        "    %s\n"
                        "    %g %s %g\n\e[0J",
                        temp.item,
                        temp.quantity,
                        temp.unit,
                        temp.calories
                    );
                    
                    if(itemExists == -1) {
                        printf(GRY "    * Added as item #%d\n\n" RESET, *F_ELEM+1);
                        FOOD[*F_ELEM] = temp;
                        (*F_ELEM)++;
                    }
                    else {
                        printf(GRY "    * Replaced item #%d\n\n" RESET, index);
                        FOOD[index-1] = temp;
                    }
                }
                else printf(GRY "\e[0J    * Overwrite cancelled\n\n" RESET);
            }
        }
        fclose(file);
    }
    
    printf(GRY"\n * [ X ]  Return to menu\n" RESET);
    confirmBack();
}