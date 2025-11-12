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

char **load_cities(const char *filename, int *num_cities);
//int find_shortest_path(const char *city1, const char *city2); // your real function

// Helper function to print all loaded cities
void list_cities(char **cities, int num_cities) {
    for (int i = 0; i < num_cities; i++) {
        printf("%s\n", cities[i]);
    }
}

int main(void) {
    char input[100];
    char city1[50], city2[50];
    int num_cities = 0;
    char **cities = NULL;

    print_splash_message();

    cities = load_cities("cities.txt", &num_cities);

    if (cities == NULL || num_cities == 0) {
        printf("Error: could not load cities.\n");
        // still allow program to continue so user can type help/exit
    }

    while (1) {
        printf("Where do you want to go today? ");
        
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        if (strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        } 
        else if (strcmp(input, "help") == 0) {
            print_scroll_of_guidance();
        } 
        else if (strcmp(input, "list") == 0) {
            if (cities && num_cities > 0)
                for (int i = 0; i < num_cities; i++)
                    printf("%s\n", cities[i]);
            else
                printf("No cities loaded.\n");
        } 
        else if (sscanf(input, "%s %s", city1, city2) == 2) {
            find_shortest_path(city1, city2);
        } 
        else {
            printf("Invalid Command\n");
            print_scroll_of_guidance();
        }
    }

    if (cities) {
        for (int i = 0; i < num_cities; i++)
            free(cities[i]);
        free(cities);
    }

    return 0;
}


    
   
    













