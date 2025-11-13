#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load_distance_data.h"


/* Loads connections (edges) between cities from file.
 * @param filename (Path to the file containing distance data)
 * @param num_distances (Pointer to an integer to store number of distances loaded)
 */
Distance *load_distances(const char *filename, int *num_distances) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open %s\n", filename);
        *num_distances = 0; // set number of distances to 0 on error
        return NULL;
    }

    Distance *distances = malloc(1000 * sizeof(Distance)); // up to 1000 edges
    int count = 0; // number of distances loaded
    char src[100], dest[100]; // buffers for source and destination
    int dist; // buffer for distance

    // read each line and parse source, destination, and distance
    while (fscanf(file, "%s %s %d", src, dest, &dist) == 3) {
        strcpy(distances[count].source, src); // copy source city name
        strcpy(distances[count].destination, dest); // copy destination city name
        distances[count].distance = dist; // set distance
        count++; // increment count
    }

    fclose(file);
    *num_distances = count; // set number of distances loaded
    return distances;
}

/* Prints the list of distances.
 * @param distances (Array of Distance structs)
 * @param count (Number of distances in the array)
 */
void print_distances(Distance *distances, int count) {
    for (int i = 0; i < count; i++) {
        // prints in format: source -> destination : distance
        printf("%s -> %s : %d\n", distances[i].source, distances[i].destination, distances[i].distance);
    }
}

/* Frees the memory allocated for distances.
 * @param distances (Array of Distance structs)
 */
void free_distances(Distance *distances) {
    free(distances);
}