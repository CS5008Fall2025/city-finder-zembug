#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "load_data.h"


void print_splash_message() {
    printf("Commands:\n");
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
}

void print_scroll_of_guidance() {
    printf("Commands:\n");
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
    printf("\tWhere do you want to go today?");
}

int main() {
    char input[137];
    char city1[69], city2[69];

    if (isatty(fileno(stdin))) {
        print_splash_message();
    }

    int num_cities;
    char **city_names = load_cities("vertices.txt", &num_cities);

    while (1) {


        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // Exit if no input is received
        }

        input[strcspn(input, "\n")] = 0;  // Strip newline

        if (strcmp(input, "exit") == 0) {
            printf("Farewell, traveler. May the trees guide your path and the wind speak your story.\n");
            break;
        } else if (strcmp(input, "help") == 0) {
            print_scroll_of_guidance();
        } else if (strcmp(input, "list") == 0) {
            print_city_list(city_names, num_cities);
        } else if (sscanf(input, "%s %s", city1, city2) == 2) {
            printf("Seeking the swiftest path from %s to %s...\n", city1, city2);
        } else {
            printf("Alas, that command is unknown in these lands.\n");
            print_scroll_of_guidance();
        }
    }

    return 0;
}




