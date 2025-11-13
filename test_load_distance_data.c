#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load_distance_data.h"

int main() {
    int num_distances = 0;

    // Load distances from file
    Distance *distances = load_distances("distances.txt", &num_distances);
    if (!distances) {
        printf("Failed to load distances.\n");
        return 1;
    }

    // Print the loaded distances
    printf("Loaded %d distances:\n", num_distances);
    print_distances(distances, num_distances);

    // Free allocated memory
    free_distances(distances);

    return 0;
}
