#include "city_graph.h"

city_edge_t *create_node(int v, int weight)
{
    city_edge_t *new_node = (city_edge_t *)malloc(sizeof(city_edge_t));
    new_node->vertex = v;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

CityGraph *create_graph(int num_vertices)
{
    CityGraph *graph = (CityGraph *)malloc(sizeof(CityGraph));
    graph->size = num_vertices;
    graph->adj_lists = (city_edge_t **)malloc(num_vertices * sizeof(city_edge_t *));
    for (int i = 0; i < num_vertices; i++)
    {
        graph->adj_lists[i] = NULL;
    }
    return graph;
}

void free_graph(CityGraph *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        city_edge_t *curr = graph->adj_lists[i];
        while (curr != NULL)
        {
            city_edge_t *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(graph->adj_lists);
    free(graph);
}

void add_edge(CityGraph *graph, int src, int dest, int weight)
{
    city_edge_t *new_node = create_node(dest, weight);
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;

    city_edge_t *reverse_node = create_node(src, weight);
    reverse_node->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = reverse_node;
}

void print_graph(CityGraph *graph, char **city_names)
{
    for (int i = 0; i < graph->size; i++)
    {
        printf("%s: ", city_names[i]);

        city_edge_t *curr = graph->adj_lists[i];
        if (curr == NULL)
            continue;
        while (curr != NULL)
        {
            printf("(%d, %d) -> ", curr->vertex, curr->weight);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}
   