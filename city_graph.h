#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "load_distance_data.h"

// This struct represents one connection (edge) between cities.
// Each edge stores:
// - the index of the connected city (vertex)
// - the distance (weight) of the connection
// - a pointer to the next edge in the list
typedef struct city_edge
{
    int vertex; // index of the city this edge connects to
    int weight; // distance of the connection
    struct city_edge* next; // pointer to the next edge in the list
} city_edge_t;


// This struct represents the entire graph of cities.
// It stores:
// - the total number of cities
// - an array of pointers, where each pointer leads to a list of edges
typedef struct city_graph
{
    int size; // number of cities (vertices)
    city_edge_t **adj_lists; // array of edge lists (one per city)
} CityGraph;


// Creates node with a given destination and weight
city_edge_t *create_node(int v, int weight);
// Creates graph with a given number of cities
CityGraph *create_graph(int num_vertices);
// Frees memory allocated for the graph
void free_graph(CityGraph *graph);
// Adds undirected connection between two cities with weight
void add_edge(CityGraph *graph, int src, int dest, int weight);
// Prints readable graph
// Shows each city and its connections
void print_graph(CityGraph *graph, char **city_names);
// Debug to print each city with its index
void debug_graph(CityGraph *graph, char **city_names);
// Builds graph from city names and distance data
CityGraph *build_graph(char **city_names, int num_cities, Distance *distances, int num_distances);


#endif 