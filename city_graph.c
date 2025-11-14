#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city_graph.h"


/**
 * Creates a new edge node representing a connection to a city.
 * @param v       Index of the destination city (vertex).
 * @param weight  Weight or distance of the edge.
 * @return Pointer to the newly created edge node.
 */
city_edge_t *create_node(int v, int weight)
{
    city_edge_t *new_node = (city_edge_t *)malloc(sizeof(city_edge_t)); // allocate memory for new edge
    new_node->vertex = v;       // set destination city index
    new_node->weight = weight;  // set distance
    new_node->next = NULL;      // initialize next pointer to NULL
    return new_node;
}

/**
 * Initializes a new graph with a specified number of cities.
 * @param num_vertices  Number of cities (vertices) in the graph.
 * @return Pointer to the newly created CityGraph structure.
 */
CityGraph *create_graph(int num_vertices)
{
    CityGraph *graph = (CityGraph *)malloc(sizeof(CityGraph)); // allocate memory for graph
    graph->size = num_vertices; // set number of cities in graph
    // allocate array for adjacency lists
    graph->adj_lists = (city_edge_t **)malloc(num_vertices * sizeof(city_edge_t *)); 
    for (int i = 0; i < num_vertices; i++) // initialize each adjacency list
    {
        graph->adj_lists[i] = NULL;  // no connections yet
    }
    return graph;
}

/**
 * Frees all dynamically allocated memory used by the graph.
 * @param graph  Pointer to the CityGraph structure to be deallocated.
 */
void free_graph(CityGraph *graph)
{
    for (int i = 0; i < graph->size; i++) // iterate through each city's edge list
    {
        city_edge_t *curr = graph->adj_lists[i]; // get head of edge list

        while (curr != NULL) // free each edge in the list
        {
            city_edge_t *tmp = curr; // store current node
            curr = curr->next; // move to next node
            free(tmp);  // free current node
        }
    }
    free(graph->adj_lists);  // free the list of cities
    free(graph); // free the graph structure
}

/**
 * Adds an undirected edge between two cities with a given weight.
 * @param graph   Pointer to the graph.
 * @param src     Index of the source city.
 * @param dest    Index of the destination city.
 * @param weight  Weight or distance of the connection.
 */
void add_edge(CityGraph *graph, int src, int dest, int weight)
{
    city_edge_t *new_node = create_node(dest, weight); // create edge from src to dest
    new_node->next = graph->adj_lists[src]; // insert at the beginning of src edge list
    graph->adj_lists[src] = new_node; // update head of src list

    // Since the graph is undirected, add an edge from dest to src as well
    city_edge_t *reverse_node = create_node(src, weight); 
    reverse_node->next = graph->adj_lists[dest]; // insert at the beginning of dest edge list
    graph->adj_lists[dest] = reverse_node; // update head of dest list
}

/**
 * Prints the adjacency list of each city in the graph.
 * @param graph       Pointer to the graph.
 * @param city_names  Array of city names indexed by city position.
 */
void print_graph(CityGraph *graph, char **city_names)
{
    for (int i = 0; i < graph->size; i++) // iterate through each city
    {
        printf("%s: ", city_names[i]);  // print city name

        city_edge_t *curr = graph->adj_lists[i]; // get list of connections
        if (curr == NULL) // no connections, skip to next city
            continue;

        while (curr != NULL) // iterate through connections and print them
        {
            printf("(%d, %d) -> ", curr->vertex, curr->weight); // print connected city index and distance
            curr = curr->next; // move to next connection
        }
        printf("NULL\n"); // end of connections for this city
    }
}

/**
 * Prints each city's index and name for debugging purposes.
 * @param graph       Pointer to the graph.
 * @param city_names  Array of city names indexed by city ID.
 */
void debug_graph(CityGraph *graph, char **city_names)
{
    printf("Graph has %d cities:\n", graph->size); // print number of cities
    for (int i = 0; i < graph->size; i++) // iterate through each city
    {
        printf("[%d] %s\n", i, city_names[i]);  // show index and name
    }
}

/**
 * Builds a graph from city names and distance data.
 * @param city_names     Array of city names.
 * @param num_cities     Number of cities.
 * @param distances      Array of Distance structs representing connections.
 * @param num_distances  Number of distances in the array.
 * @return Pointer to the constructed CityGraph.
 */
CityGraph *build_graph(char **city_names, int num_cities, Distance *distances, int num_distances) {
    CityGraph *graph = create_graph(num_cities); // create empty graph with given number of cities
    // Loop through each distance entry to add edges to the graph
    for (int i = 0; i < num_distances; i++) {
        int src = -1, dest = -1; // indices of source and destination cities

        // Create space to store cleaned versions of the city names
        // Temp buffers used to clean up the names before comparing them
        char src_clean[100], dest_clean[100]; 
        // Copy the source and destination city names from distances array into temp buffers
        strcpy(src_clean, distances[i].source); // copy source city to src_clean
        strcpy(dest_clean, distances[i].destination); // copy destination city to dest_clean

        // Remove trailing newline or carriage return characters
        src_clean[strcspn(src_clean, "\r\n")] = '\0';
        dest_clean[strcspn(dest_clean, "\r\n")] = '\0';

        // Loop thru city names to find matching indices of source and destination cities
        for (int j = 0; j < num_cities; j++) {
            char city_clean[100]; // temp buffer to hold clean city name
            strcpy(city_clean, city_names[j]); // copy city name to city_clean
            city_clean[strcspn(city_clean, "\r\n")] = '\0'; // clean up city name
            // Compare cleaned city name to the cleaned source and destination names
            // If matches, store the index
            if (strcmp(city_clean, src_clean) == 0) src = j;
            if (strcmp(city_clean, dest_clean) == 0) dest = j;
        }

        // If both cities were found, add the edge between them
        if (src != -1 && dest != -1) {
            add_edge(graph, src, dest, distances[i].distance); // add undirected edge
        } else {
            // If either city was not found, print warning message for
            printf("Listen! Could not find indices for %s -> %s\n", distances[i].source, distances[i].destination);
        }
    }

    return graph;
}
