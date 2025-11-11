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
    char city1[69], city2[69];

    while (1) {
        printf("Where do you want to go today? ");
        fgets(input, sizeof(input), stdin);

        if (strcomp(input, "exit") == 0) {
            printf("Farewell, traveler. May the trees guide your path and the wind speak your story.\n");
            break;
        } 
        else if (strcmp(input, "help") == 0) {
            print_scroll_of_guidance();
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







    /**
   while (1) {
        
        printf("Where do you want to go today? ");
        

        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Don't print anything — just exit silently
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            if (isatty(fileno(stdin))) {
                printf("Farewell, traveler. May the trees guide your path and the wind speak your story.\n");
            }
            break;
        } else if (strcmp(input, "help") == 0) {
            print_scroll_of_guidance();
        } else if (strcmp(input, "list") == 0) {
            print_city_list(city_names, num_cities);

        } else if (sscanf(input, "%s %s", city1, city2) == 2) {
            printf("Seeking the swiftest path from %s to %s...\n", city1, city2);
        } else {
            printf("Invalid Command\n");
            print_scroll_of_guidance();
        }
    }

    return 0;
} */




