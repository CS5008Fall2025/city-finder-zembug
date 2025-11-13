#include "load_city_data.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/**
 * Loads city names from a specified file.
 * @param filename    Path to the file containing city names.
 * @param num_cities  Pointer to an integer to store the number of cities loaded.
 */
char **load_cities(const char *filename, int *num_cities) {
    FILE *file = fopen(filename, "r"); // open file for reading
    if (file == NULL) {
        printf("Error: could not open %s\n", filename);
        *num_cities = 0; // set number of cities to 0 on error
        return NULL;
    }

    char line[100]; // buffer for reading lines
    char **cities = malloc(100 * sizeof(char*)); // up to 100 cities max
    int count = 0; // number of cities loaded

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // remove newline

        // allocate space for this city and copy the name
        cities[count] = malloc(strlen(line) + 1);
        strcpy(cities[count], line); // copy city name
        count++; // increment city count
    }

    fclose(file);
    *num_cities = count; // set number of cities loaded
    return cities;
}


/**
 * Prints the list of city names.
 * @param city_names  Array of city name strings.
 * @param num_cities  Number of cities in the array.
 */
void print_city_list(char **city_names, int num_cities) {
    for (int i = 0; i < num_cities; i++) {
        printf("%s\n", city_names[i]);
    }
}

/** Frees the memory allocated for city names.
 * @param cities  Array of city name strings.
 * @param count   Number of cities in the array.
 */
void free_city_list(char **cities, int count) {
    for (int i = 0; i < count; i++) {
        free(cities[i]);
    }
    free(cities);
}
