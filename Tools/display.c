#define RESET "\e[0m"
#define BLINK "\e[5m"
#define GRY "\e[30m"
#define RED "\e[31m"
#define GRN "\e[32m"
#define YLW "\e[33m"

#define LINE "==================================================\n\n"

void delayedLoad() {
    int index = 0;

    while(index != 4) {
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
void selectionCarousel(int SELECTED, int MAX, string OPTIONS[]) {
    int selectionDisplayIndex = 0;
    while(selectionDisplayIndex != MAX) {
        if(SELECTED == selectionDisplayIndex) printf(YLW " >>> " BLINK);
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

void addCalDisplay() {
    printf(
        "\n"
        "   ADD CALORIE INFO\n"
        "\n"
    );
}

void viewCalDisplay() {
    printf(
        "\n"
        "    VIEW CALORIE INFO\n\n"
    );
}