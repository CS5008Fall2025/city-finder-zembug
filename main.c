#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "load_city_data.h"

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
    printf("*******************************************************\n");
}

void handle_list_command(const char *filename) {
    int num_cities;
    char **city_names = load_cities(filename, &num_cities);

    if (city_names) {
        print_city_list(city_names, num_cities);
        free_city_list(city_names, num_cities);
    } else {
        printf("No cities loaded.\n");
    }
}

int main(int argc, char *argv[]) {
    const char *filename = "vertices.txt"; // default file name
    if (argc > 1) filename = argv[1];      // override if provided

    char input[137];
    print_splash_message();

    while (1) {
        printf("Where do you want to go today? ");

        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        } else if (strcmp(input, "help") == 0) {
            print_scroll_of_guidance();
        } else if (strcmp(input, "list") == 0) {
            handle_list_command(filename);
        } else {
            printf("Invalid Command\n");
            print_scroll_of_guidance();
        }
    }

    return 0;
}