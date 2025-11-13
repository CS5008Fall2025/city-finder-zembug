#include <stdio.h>
#include "load_city_data.h"

int main() {
    int num_cities = 0;

    // Load cities from file
    char **cities = load_cities("vertices.txt", &num_cities);
    if (!cities) {
        printf("Failed to load cities.\n");
        return 1;
    }

    // Print the loaded cities
    printf("Loaded %d cities:\n", num_cities);
    print_city_list(cities, num_cities);

    // Free allocated memory
    free_city_list(cities, num_cities);

    return 0;
}
