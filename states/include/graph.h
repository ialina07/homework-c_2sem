#pragma once

#define MAX_CITIES 1000
#define MAX_ROADS 1000

typedef struct {
    int to;
    int length;
    int next;
} Edge;

typedef struct {
    Edge edges[MAX_ROADS * 2];
    int head[MAX_CITIES];
    int edgeCount;
    int n; // количество городов
} Graph;

// инициализация графа
void graphInit(Graph* graph, int n);

// добавление ребра
void graphAddEdge(Graph* graph, int from, int to, int length);

// нахождение расстояния между двумя городами
int graphGetDistance(Graph* graph, int from, int to);
