#include "load_data.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LINE_LEN 256 // Maximum length for a single line (city name or distance)

/**
 * Loads city names from a file into a dynamically allocated array.
 * Each line in the file is assumed to contain one city name.
 * The function assigns each city an index based on its line number.
 *
 * @param filename     The name of the file to read from.
 * @param num_cities   Pointer to an integer that will be set to the number of cities loaded.
 * @return             A dynamically allocated array of city name strings. NULL if an error occurs.
 **/
char **load_cities(const char *filename, int *num_cities) {
    printf("Loading cities from file: %s\n", filename);

    FILE *file = fopen(filename, "r"); // open file for reading
    if (file == NULL) { // check if file opened successfully
        fprintf(stderr, "Could not open file: %s\n", filename); // error message
        return NULL;
    }

    int capacity = 10; // start with space for 10 cities
    int count = 0;
    // Allocate initial memory for array of city names
    char **city_names = malloc(capacity * sizeof(char *)); 
    if (city_names == NULL) { // check for allocation failure
        fprintf(stderr, "Memory allocation failed for city names.\n");
        fclose(file);
        return NULL;
    }

    char line[MAX_LINE_LEN]; // create a buffer for each line from file

    while (fgets(line, MAX_LINE_LEN, file)) { // read each line until end of file
        line[strcspn(line, "\n")] = '\0'; // remove newline at end of line

        // if necessary, resize the array to hold more city names
        if (count >= capacity) {
            capacity *= 2; // double the capacity
            // reallocate more space for city names
            char **temp = realloc(city_names, capacity * sizeof(char *)); 
            if (temp == NULL) {
                // if reallocation fails
                fprintf(stderr, "Memory reallocation failed for city names.\n");
                break;
            }
            // update pointer to new memory
            city_names = temp;
        }
        // copy line into new string and store in array
        city_names[count++] = strdup(line);
    }
    fclose(file); // close the file

    *num_cities = count; // set the number of cities loaded
    printf("Loaded %d cities from file.\n", count); 
    return city_names; // return the array of city names
}