#pragma once

#include "graph.h"
#include "state.h"

typedef struct {
    int* states;        // принадлежность городов государствам
    int* visited;       // распределен ли город
    State* stateCities; // списки городов
    int k;              // кол-во государств
    int n;              // кол-во городов
} Distributor;

// инициализация распределителя
void distributorInit(Distributor* dist, int n, int k);

// утсановка столиц
void distributorSetCapitals(Distributor* dist, int* capitals, int capitalCount);

// поиск ближайшего незанятого города
int distributorFindNearest(Distributor* dist, Graph* graph);

// распределение всех городов
void distributorDistributeAll(Distributor* dist, Graph* graph);

// вывод результатов
void distributorPrintResults(Distributor* dist);

// освобождение памяти
void distributorFree(Distributor* dist);