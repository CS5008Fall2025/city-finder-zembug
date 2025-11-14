#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "city_graph.h"


int *shortest_path(CityGraph *graph, int src, int dest, int *path_length, int *total_distance);

#endif
