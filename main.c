#include <stdio.h>
#include <string.h>
#include "load_data.h"


void print_splash_message() {
    printf("Commands:\n");
    printf("  list - list all cities\n");
    printf("  <city1> <city2> - find the shortest path between two cities\n");
    printf("  help - print this help message\n");
    printf("  exit - exit the program\n");
}

void print_scroll_of_guidance() {
    printf("Commands:\n");
    printf("  list - list all cities\n");
    printf("  <city1> <city2> - find the shortest path between two cities\n");
    printf("  help - print this help message\n");
    printf("  exit - exit the program\n");
}

int main() {
    char input[137];
    char city1[69], city2[69];

    print_splash_message();
    
    while (1) {
        printf("Speak now, wanderer. Where shall your feet carry you?\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  // remove newline character

        if (strcmp(input, "exit") == 0) {
            printf("Farewell, traveler. May the trees guide your path and the wind speak your story.\n");
            break;
        } else if (strcmp(input, "help") == 0) {
            print_scroll_of_guidance();
        } else if (strcmp(input, "list") == 0) {
            printf("The cities of the realm are:\n");
            // Here you would call a function to list cities from your graph
        } else if (sscanf(input, "%s %s", city1, city2) == 2) {
            printf("Seeking the swiftest path from %s to %s...\n", city1, city2);
            // Here you would call a function to find and print the shortest path
        } else {
            printf("Alas, that command is unknown in these lands.\n");
            print_scroll_of_guidance();
        }
    }
   
    return 0;
}

