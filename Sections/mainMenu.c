// menu handler for choosing between the modes
//
// @RETURN the chosen mode option or exit the program
int mainMenu() {
    string options[3] = {
        "Update Recipe Box",
        "Access Recipe Box",
        "Exit Program"
    };

    int mode = 0;

    char input;
    while(!INPUT_ENTER) { // selection carousel
        printf(
            "\n"
            "MENU SELECTION SCREEN\n"
            "\n"
        );
        
        mode = selectionLooper(mode, 2);
        selectionCarousel(mode, 3, options, YLW);
        printf(GRY "\n * [ ↑ / ↓ ] to navigate\n * [ ENTER ] to select\n\n" RESET);

        input = getch();
        navigation(input, &mode, 'y');

        WIPE
    }

    if(mode == 2) mode *= -1;

    return mode;
}