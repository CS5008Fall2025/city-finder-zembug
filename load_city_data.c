#include "load_city_data.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define MAX_CITY_NAME_LEN 100
#define MAX_CITIES 1000

// Loads city names from a file
char **load_cities(const char *filename, int *num_cities) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening city file");
        *num_cities = 0;
        return NULL;
    }

    char **cities = malloc(MAX_CITIES * sizeof(char *));
    if (!cities) {
        perror("Memory allocation failed");
        fclose(file);
        *num_cities = 0;
        return NULL;
    }

    char buffer[MAX_CITY_NAME_LEN];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        //printf("Loaded city: '%s'\n", buffer);
        if (strlen(buffer) == 0) continue;

        cities[count] = malloc(strlen(buffer) + 1);
        if (!cities[count]) {
            perror("Memory allocation failed for city name");
            break;
        }

        strcpy(cities[count], buffer);
        count++;

        if (count >= MAX_CITIES) break;
    }

    fclose(file);
    *num_cities = count;
    return cities;
}



/**
 * Prints the list of city names.
 * 
 * @param city_names  Array of city name strings.
 * @param num_cities  Number of cities in the array.
 */
void print_city_list(char **city_names, int num_cities) {
    for (int i = 0; i < num_cities; i++) {
        printf("%s\n", city_names[i]);
    }
}

void free_city_list(char **cities, int count) {
    for (int i = 0; i < count; i++) {
        free(cities[i]);
    }
    free(cities);
}

