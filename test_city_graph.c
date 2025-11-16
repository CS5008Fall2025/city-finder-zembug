#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load_city_data.h"
#include "load_distance_data.h"
#include "city_graph.h"


// Test the graph building, printing
int main() {
    int num_cities = 0, num_distances = 0;

    // Load city names from file
    char **cities = load_cities("vertices.txt", &num_cities);
    if (!cities) {
        printf("Failed to load cities.\n");
        return 1;
    }

    // Load distance data
    Distance *distances = load_distances("distances.txt", &num_distances);
    if (!distances) {
        printf("Failed to load distances.\n");
        free_city_list(cities, num_cities);
        return 1;
    }

    // Build the graph
    CityGraph *graph = build_graph(cities, num_cities, distances, num_distances);

    // Print the graph structure
    printf("Graph structure:\n");
    print_graph(graph, cities);

    // Cleanup
    free_graph(graph);
    free_city_list(cities, num_cities);
    free_distances(distances);

    return 0;
}
