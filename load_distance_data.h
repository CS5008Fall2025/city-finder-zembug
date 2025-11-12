#ifndef LOAD_DISTANCE_DATA_H
#define LOAD_DISTANCE_DATA_H

// This struct represents a distance entry between two cities.
// It stores:
// - the source city name
// - the destination city name
// - the distance between them
typedef struct {
    char source[100];
    char destination[100];
    int distance;
} Distance;

// Loads connections (edges) between cities from file
Distance *load_distances(const char *filename, int *num_distances);

// Prints the list of distances
void print_distances(Distance *distances, int count);

// Frees the memory allocated for distances
void free_distances(Distance *distances);

#endif