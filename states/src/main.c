#include "distributor.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, k;
    scanf("%d %d", &n, &m);

    Graph graph;
    graphInit(&graph, n);

    // чтение дорог
    for (int i = 0; i < m; i++) {
        int from, to, len;
        scanf("%d %d %d", &from, &to, &len);
        from--;
        to--;
        graphAddEdge(&graph, from, to, len);
    }

    // чтение кол-ва столиц
    scanf("%d", &k);
    int* capitals = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        scanf("%d", &capitals[i]);
        capitals[i]--;
    }

    Distributor distributor;
    distributorInit(&distributor, n, k);
    distributorSetCapitals(&distributor, capitals, k);

    distributorDistributeAll(&distributor, &graph);

    distributorPrintResults(&distributor);

    distributorFree(&distributor);
    free(capitals);

    return 0;
}