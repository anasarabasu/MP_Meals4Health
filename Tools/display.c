#define WIPE printf("\e[H\e[0J");

#define RESET "\e[0m"
#define BLINK "\e[5m"
#define GRY "\e[1;30m"
#define RED "\e[31m"
#define GRN "\e[32m"
#define YLW "\e[33m"
#define PRP "\e[35m"

#define LINE "======================================================================================================================\n"
#define LINE2 " --------------------------------------------------------------------------------------------------------------------\n"
#define LINE3 " ----------------------------------------------------------------------\n"

// Handles the rotating menu options display
//
// @param SELECTED - index of currently selected option
// @param MAX - total total number of options to choose from
// @param OPTIONS - string array of options to be displayed
void selectionCarousel(int SELECTED, int MAX, string OPTIONS[], char * COLOUR) {
    int selectionDisplayIndex;

    for(selectionDisplayIndex = 0; selectionDisplayIndex != MAX; selectionDisplayIndex++) {
        if(SELECTED == selectionDisplayIndex) {
            if(SELECTED == MAX - 1) printf(RED " >>> " BLINK);
            else printf("%s >>> " BLINK, COLOUR);
        }
        else printf("    ");

        printf("%s\n" RESET, OPTIONS[selectionDisplayIndex]);
    }
}

// Dot dot dot
void delayedLoad() {
    int index;
    for(index = 0; index != 3; index++) {
        sleep(1);
        printf(GRY " .\n" RESET);
    }

    WIPE
}


//------------------------------------------

void addRecDisplay() {
    printf(
        "\n"
        "    ADD RECIPE\n\n"
        GRY " * Enter dish name, classification, number of servings, list of ingredients, and procedures\n\n" RESET
    );
}

void listRecipeTitlesDisplay() {
    printf(
        "\n"
        "    LIST RECIPE TITLES\n\n"
    );
}