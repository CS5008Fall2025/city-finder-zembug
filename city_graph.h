#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include <stdio.h>
#include <stdlib.h>


typedef struct city_edge
{
    int vertex;
    int weight;
    struct city_edge* next;
} city_edge_t;

typedef struct city_graph
{
    int size;
    city_edge_t **adj_lists;
} CityGraph;


city_edge_t *create_node(int v, int weight);
CityGraph *create_graph(int num_vertices);
void free_graph(CityGraph *graph);
void add_edge(CityGraph *graph, int src, int dest, int weight);
void print_graph(CityGraph *graph);
int get_city_index(const char *city_name, char **city_names, int city_count);
void debug_graph(CityGraph *graph, char **city_names);

#endif