#include <stdio.h>
#include <stdlib.h>
#include "path_finder.h"

// Test the shortest_path function
int main() {
    printf("Beginning journey through Middle-earth!\n");
    // Sample city names and distances
    char *city_names[] = {
        "Rivendell", "Minas Tirith", "Gondor", "Helm's Deep", "Isengard"
    };
    int num_cities = 5;

    // Sample distances between cities
    Distance distances[] = {
        {"Rivendell", "Minas Tirith", 13},
        {"Minas Tirith", "Gondor", 37},
        {"Gondor", "Helm's Deep", 69},
        {"Helm's Deep", "Isengard", 11},
        {"Rivendell", "Isengard", 3}
    };
    int num_distances = sizeof(distances) / sizeof(distances[0]);

    // Build the graph
    CityGraph *graph = build_graph(city_names, num_cities, distances, num_distances);

    // Find shortest path from Rivendell to Helm's Deep
    int path_length = 0;
    int total_distance = 0;
    int *path = shortest_path(graph, 0, 3, &path_length, &total_distance); // indices 0 = Rivendell, 3 = Helm's Deep
    
    // Print the path result
    if (path) {
        printf("Shortest path from %s to %s:\n", city_names[0], city_names[3]);
        for (int i = 0; i < path_length; i++) {
            printf("%s\n", city_names[path[i]]);
            }
        free(path);
    } else {
        printf("No path found from %s to %s.\n", city_names[0], city_names[3]);
    }
    free_graph(graph);
    
    printf("Journey complete. May your path always be swift.\n");

    return 0;
}
