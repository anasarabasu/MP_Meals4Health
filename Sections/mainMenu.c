// Processes arrow key input for option navigation
//  @RETURNS the index for the state option selected
int mainMenu() {
    int selected = 0;
    char input = '\0';

    string options[3] = {
        "Update Recipe Box",
        "Access Recipe Box",
        "Exit Program"
    };

    while(input != '\n') { // selection carousel
        menuDisplay();
        
        selected = selectionLooper(selected, 2);
        selectionCarousel(selected, 3, options, YLW);
        printf(GRY "\n * [ ↑ / ↓ ] to navigate\n * [ ENTER ] to select\n\n" RESET);

        input = getch();
        navigation(input, &selected, 'y');

        clearScreen();
    }

    if(selected == 2) selected *= -1;

    return selected;
}