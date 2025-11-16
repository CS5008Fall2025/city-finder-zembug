#include "path_finder.h"
#include <stdbool.h>
#include <limits.h>

// Macro to free all temporary arrays used during pathfinding
#define FREEPATH() do {free(distance); free(prev); free(visited);} while (0)

/**
 * Finds the shortest path between source city and destination city in the given graph using Dijkstra's algorithm.
 * @param graph Pointer to the CityGraph structure representing the graph.
 * @param src Index of the source city.
 * @param dest Index of the destination city.
 * @param path_length Pointer to an integer where the function will store the number of cities in the path.
 * @return An array of city indices representing the shortest path from source to destination.
 */

int *shortest_path(CityGraph *graph, int src, int dest, int *path_length, int *total_distance){
    // Validate input:
    if (graph == NULL) { // graph must exist
        return NULL;
    }
    if (src < 0 || src >= graph->size) { // source must be valid city index
        return NULL;
    }
    if (dest < 0 || dest >= graph->size) { // destination must be valid city index
        return NULL;
    }

    // Allocate arrays for Dijkstra's algorithm:
    // holds the shortest known distance from source
    int *distance = malloc(graph->size * sizeof(int));
    // holds the previous city on the shortest path
    int *prev = malloc(graph->size * sizeof(int));
    // tracks which cities have been visited
    bool *visited = malloc(graph->size * sizeof(bool));

    // If allocation failed, clean up and exit
    if (!distance || !prev || !visited) {
        FREEPATH();
        return NULL;
    }

    // Before pathfinding begins: prepare arrays for Dijkstra's algorithm
    for (int i = 0; i < graph->size; i ++) {
        // all cities unreachable (distance = infinity)
        distance[i] = INT_MAX;
        // no previous city on path
        prev[i] = -1;
        // no cities have been visited
        visited[i] = false;
    }
    distance[src] = 0; // source city to itself has distance 0

    // Main loop of Dijkstra's algorithm: repeat for each city in the graph
    for (int i = 0; i < graph->size; i++) {
        int min_distance = INT_MAX; // smallest known distance found so far
        int curr_city = -1; // index of closest unvisited city
        for (int j = 0; j < graph->size; j++) {
            // find the unvisited city with the smallest known distance
            if (!visited[j] && distance[j] < min_distance) {
                min_distance = distance[j]; // update smallest known distance
                curr_city = j; // update closest unvisited city
            }
        }
        if (curr_city == -1) { // no more reachable unvisited cities
            break;
        }
        visited[curr_city] = true; // mark current city as visited

        // Explore all neighbors connected to current city
        city_edge_t *neighbor_edge = graph->adj_lists[curr_city]; 
        for (; neighbor_edge != NULL; neighbor_edge = neighbor_edge->next) {
            int next_city = neighbor_edge->vertex; // city this edge leads to
            // Calculate alternative distance through current city
            int alt_distance = distance[curr_city] + neighbor_edge->weight;
            // If alternative distance is shorter, update distance and previous city
            if (alt_distance < distance[next_city]) {
                distance[next_city] = alt_distance;
                prev[next_city] = curr_city;
            }
        }
    }

    // If destination is still unreachable, no valid path
    if (distance[dest] == INT_MAX) {
        *path_length = 0; // no cities in path
        FREEPATH();
        return NULL;
    }
    
    // Count the path length
    // Trace the shortest path from destination to source and count how many cities it includes
    int count = 0; // path length in cities
    for (int city = dest; city != -1; city = prev[city]) {
        count++; // each step follows the path backward through prev[]
    }

    // Allocate array to hold the shortest path
    int *path = malloc(count * sizeof(int));
    if (!path) {
        FREEPATH();
        return NULL;
    }

    // Fill the path array in reverse order (so final result goes from source to destination)
    int path_index = count - 1; // start filling from the end of path[]
    int curr_city = dest; // begin tracing from the destination city
    while (curr_city != -1) { // follow the path back to the source
        path[path_index--] = curr_city; // store current city and move backward
        curr_city = prev[curr_city]; // step to the previous city on the path
    }

    *path_length = count; // set the number of cities in the path
    *total_distance = distance[dest]; // set the total distance of the path 
    FREEPATH();
    return path; // return shortest path as array of city indices
}