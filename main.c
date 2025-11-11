#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "load_data.h"

void print_scroll_of_guidance() {
    printf("Commands:\n");
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
    
}

void print_splash_message() {
    printf("***** Welcome to the shortest path finder! ******\n");
    print_scroll_of_guidance();
    printf("\n*******************************************************\n");
}



int main() {
    char input[137];

    // Read first line before printing anything
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0; // No input, exit quietly
    }

    input[strcspn(input, "\n")] = '\0';

    // If input is not a known command, show splash
    if (!(strcmp(input, "list") == 0 || strcmp(input, "help") == 0 || strcmp(input, "exit") == 0)) {
        print_splash_message();
    }

    while (1) {
        // Process the first input, then continue reading
        if (strcmp(input, "exit") == 0) {
            printf("Farewell, traveler. May the trees guide your path and the wind speak your story.\n");
            break;
        } else if (strcmp(input, "help") == 0) {
            print_scroll_of_guidance();
        } else if (strcmp(input, "list") == 0) {
            int num_cities;
            char **city_names = load_cities("vertices.txt", &num_cities);
            if (city_names) {
                print_city_list(city_names, num_cities);
                free_city_list(city_names, num_cities);
            } else {
                printf("No cities loaded.\n");
            }
        } else {
            printf("Invalid Command\n");
            print_scroll_of_guidance();
        }

        // Prompt for next input
        printf("Where do you want to go today?\n");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';
    }

    return 0;
}

    
   
    













