#include "graph.h"
#include <limits.h>
#include <stdio.h>

void graphInit(Graph* graph, int n) {
    graph->n = n;
    graph->edgeCount = 0;
    for (int i = 0; i < n; i++) {
        graph->head[i] = -1;
    }
}

void graphAddEdge(Graph* graph, int from, int to, int length) {
    // добавляем ребро from->to
    graph->edges[graph->edgeCount].to = to;
    graph->edges[graph->edgeCount].length = length;
    graph->edges[graph->edgeCount].next = graph->head[from];
    graph->head[from] = graph->edgeCount++;

    // добавляем обратное ребро to->from
    graph->edges[graph->edgeCount].to = from;
    graph->edges[graph->edgeCount].length = length;
    graph->edges[graph->edgeCount].next = graph->head[to];
    graph->head[to] = graph->edgeCount++;
}

int graphGetDistance(Graph* graph, int from, int to) {
    for (int e = graph->head[from]; e != -1; e = graph->edges[e].next) {
        if (graph->edges[e].to == to) {
            return graph->edges[e].length;
        }
    }
    return INT_MAX;
}