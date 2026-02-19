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

void delayedLoad() {
    int index = 0;

    while(index != 3) {
        sleep(1);
        printf(GRY " .\n" RESET);
        index++;
    }

    clearScreen();
}

//
// @param SELECTED - index of currently selected option
// @param MAX - total total number of options to choose from
// @param OPTIONS - string array of options to be displayed
void selectionCarousel(int SELECTED, int MAX, string OPTIONS[], char * COLOUR) {
    int selectionDisplayIndex = 0;
    while(selectionDisplayIndex != MAX) {
        if(SELECTED == selectionDisplayIndex) {
            if(SELECTED == MAX - 1) printf(RED " >>> " BLINK);
            else printf("%s >>> " BLINK, COLOUR);
        }
        else printf("    ");

        printf("%s\n" RESET, OPTIONS[selectionDisplayIndex]);

        selectionDisplayIndex++;
    }
}

//------------------------------------------

void menuDisplay() {
    printf(
        "\n"
        "    MENU SELECTION SCREEN\n"
        "\n"
    );
}

//------------------------------------------

void logInDisplay() {
    printf(
        "\n"
        "    ADMIN LOG IN SCREEN\n"
        "\n"
    );
}

void adminDisplay() {
    printf(
        "\n"
        "    UPDATE MODE\n"
        "\n"
    );
}

//------------------------------------------

void addCalDisplay() {
    printf(
        "\n"
        "   ADD CALORIE INFO\n\n"
        GRY " * Enter food item, quantity, unit, and calorie count\n\n" RESET
    );
}

void viewCalDisplay() {
    printf(
        "\n"
        "    VIEW CALORIE INFO\n\n"
    );
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