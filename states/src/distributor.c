#include "distributor.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void distributorInit(Distributor* dist, int n, int k) {
    dist->n = n;
    dist->k = k;
    dist->states = malloc(n * sizeof(int));
    dist->visited = malloc(n * sizeof(int));
    dist->stateCities = malloc(k * sizeof(State));

    for (int i = 0; i < n; i++) {
        dist->states[i] = -1;
        dist->visited[i] = 0;
    }

    for (int i = 0; i < k; i++) {
        stateInit(&dist->stateCities[i]);
    }
}

void distributorSetCapitals(Distributor* dist, int* capitals, int capitalCount) {
    for (int i = 0; i < capitalCount; i++) {
        int capital = capitals[i];
        dist->states[capital] = i;
        dist->visited[capital] = 1;
        stateAddCity(&dist->stateCities[i], capital);
    }
}

int distributorFindNearest(Distributor* dist, Graph* graph) {
    int minDistance = INT_MAX;
    int bestCity = -1;
    int bestState = -1;

    for (int city = 0; city < dist->n; city++) {
        if (dist->visited[city])
            continue;

        int minDistToAnyState = INT_MAX;
        int stateForCity = -1;

        // ищем минимальное расстояние до любого государства
        for (int s = 0; s < dist->k; s++) {
            if (dist->stateCities[s].count == 0)
                continue;

            // проверяем все города этого государства
            for (int i = 0; i < dist->stateCities[s].count; i++) {
                int stateCity = dist->stateCities[s].cities[i];
                int distToCity = graphGetDistance(graph, city, stateCity);

                if (distToCity < minDistToAnyState) {
                    minDistToAnyState = distToCity;
                    stateForCity = s;
                }
            }
        }

        if (stateForCity != -1 && minDistToAnyState < minDistance) {
            minDistance = minDistToAnyState;
            bestCity = city;
            bestState = stateForCity;
        }
    }

    if (bestCity != -1) {
        dist->states[bestCity] = bestState;
        dist->visited[bestCity] = 1;
        stateAddCity(&dist->stateCities[bestState], bestCity);
        return bestCity;
    }

    return -1;
}

void distributorDistributeAll(Distributor* dist, Graph* graph) {
    int totalAssigned = dist->k;
    while (totalAssigned < dist->n) {
        int assigned = distributorFindNearest(dist, graph);
        if (assigned != -1) {
            totalAssigned++;
        }
    }
}

void distributorPrintResults(Distributor* dist) {
    for (int i = 0; i < dist->k; i++) {
        // сортируем города
        stateSortCities(&dist->stateCities[i]);

        printf("State %d: ", i + 1);
        for (int j = 0; j < dist->stateCities[i].count; j++) {
            printf("%d", dist->stateCities[i].cities[j] + 1);
        }
        printf("\n");
    }
}

void distributorFree(Distributor* dist) {
    if (dist->states != NULL) {
        free(dist->states);
        dist->states = NULL;
    }

    if (dist->visited != NULL) {
        free(dist->visited);
        dist->visited = NULL;
    }

    if (dist->stateCities != NULL) {
        for (int i = 0; i < dist->k; i++) {
            stateFree(&dist->stateCities[i]);
        }
        free(dist->stateCities);
        dist->stateCities = NULL;
    }
}