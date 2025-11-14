#include "path_finder.h"
#include <stdbool.h>
#include <limits.h>

// Macro to free all temporary arrays used during pathfinding
#define FREEPATH() do { free(distance); free(prev); free(visited); } while (0)

/* Finds the shortest path between src and dest in the given graph using Dijkstra's algorithm.
 * Returns an array of city indices representing the path, and sets path_length to the number of cities in the path.
 * If no path exists or an error occurs, returns NULL and sets path_length to 0.
*/
int *shortest_path(CityGraph *graph, int src, int dest, int *path_length){
    // Validate input:
    if (graph == NULL) { // graph must exist
        return NULL;
    }
    if (src < 0 || src >= graph->size) { // src must be valid city index
        return NULL;
    }
    if (dest < 0 || dest >= graph->size) { // dest must be valid city index
        return NULL;
    }

    // Allocate arrays for Dijkstra's algorithm:
    // holds the shortest known distance from src
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

    // If destination is still unreachable, no valid path
    if (distance[dest] == INT_MAX) {
        *path_length = 0;
        FREEPATH();
        return NULL;
    }
    
    // Count the path length
    // Trace the shortest path from dest to src and count how many cities it includes
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

    // Fill the path array in reverse order (so final result goes from src to dest)
    int path_index = count - 1; // start filling from the end of path[]
    int curr_city = dest; // begin tracing from the destination city
    while (curr_city != -1) { // follow the path back to the source
        path[path_index--] = curr_city; // store current city and move backward
        curr_city = prev[curr_city]; // step to the previous city on the path
    }

    *path_length = count; // set the number of cities in the path
        FREEPATH();
        return path; // return shortest path as array of city indices
}