#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "load_city_data.h"
#include "load_distance_data.h"
#include "path_finder.h"


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

void handle_list_input(const char *vertices_filename) {
    int num_cities;
    char **city_names = load_cities(vertices_filename, &num_cities);

    if (city_names) {
        print_city_list(city_names, num_cities);
        free_city_list(city_names, num_cities);
    } else {
        printf("No cities loaded.\n");
    }
}

void handle_path_input(const char *city1, const char *city2, const char *vertices_filename, const char *distances_filename) {
    int num_cities = 0, num_distances = 0;
    char **city_names = load_cities(vertices_filename, &num_cities);
    Distance *distances = load_distances(distances_filename, &num_distances);

    if (!city_names || !distances) {
        printf("Failed loading city or distance data.\n");
        return;
    }
    CityGraph *graph = build_graph(city_names, num_cities, distances, num_distances);

    int src = -1, dest = -1;
    for (int i = 0; i < num_cities; i++) {
        char clean[100];
        strcpy(clean, city_names[i]);
        clean[strcspn(clean, "\r\n")] = '\0'; // remove newline if present
        if (strcmp(clean, city1) == 0) src = i;
        if (strcmp(clean, city2) == 0) dest = i;
    }

    if (src == -1 || dest == -1) {
        printf("Invalid Command\n");
        free_graph(graph);
        free_city_list(city_names, num_cities);
        free_distances(distances);
        return;
    }
    int path_length = 0;
    int *path = shortest_path(graph, src, dest, &path_length);

    if (path) {
        printf("Path Found...\n");
        for (int i = 0; i < path_length; i++) {
            printf("\t%s\n", city_names[path[i]]);
        }
        free(path);
    } else {
        printf("Path Not Found...\n");
    }
    free_graph(graph);
    free_city_list(city_names, num_cities);
    free_distances(distances);
}


int main(int argc, char *argv[]) {
    const char *vertices_filename = "vertices.txt"; // default file name
    const char *distances_filename = "distances.txt"; // default distances file name
    
    if (argc > 1) vertices_filename = argv[1]; // override if provided
    if (argc > 2) distances_filename = argv[2]; // override if provided

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
            handle_list_input(vertices_filename);

        } else {
            char city1[64], city2[64];
            if (sscanf(input, "%63s %63s", city1, city2) != 2) {
                printf("Invalid Command\n");
                print_scroll_of_guidance();
                continue;
            }
            handle_path_input(city1, city2, vertices_filename, distances_filename);
        }
    }

    return 0;
}