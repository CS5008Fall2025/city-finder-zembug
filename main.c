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
    print_splash_message();

    char input[137];
    //char city1[69], city2[69];

    while (1) {
        printf("Where do you want to go today? ");
        fgets(input, sizeof(input), stdin);

        if (strcmp(input, "exit") == 0) {
            printf("Farewell, traveler. May the trees guide your path and the wind speak your story.\n");
            break;
        } 
        else if (strcmp(input, "help") == 0) {
            print_scroll_of_guidance();
        }
        else if (strcmp(input, "list") == 0) {
            int num_cities;
            char **city_names = load_cities("vertices.txt", &num_cities);
            if (city_names) {
                print_city_list(city_names, num_cities);
                // Free allocated memory
                for (int i = 0; i < num_cities; i++) {
                    free(city_names[i]);
                }
                free(city_names);
            } else {
                printf("No cities loaded.\n");
            }
        }
        else {
            printf("Invalid Command\n");
            print_scroll_of_guidance();
        }
    }
    return 0;
}
    
   
    

    //int num_cities;
    //char **city_names = load_cities("vertices.txt", &num_cities);
    //printf("Loaded %d cities.\n", num_cities);












