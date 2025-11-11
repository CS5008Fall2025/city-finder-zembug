#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "city_graph.h"

// Loads city names from file
char **load_cities(const char *filename, int *num_cities);

// Loads connections (edges) between cities from file
void load_distances(CityGraph *graph, const char *filename, char **city_names, int num_cities);

// Finds the index of a city name in the city_names list
int get_city_index(const char *city_name, char **city_names, int num_cities);

// Prints the list of city names
void print_city_list(char **city_names, int num_cities);


#endif