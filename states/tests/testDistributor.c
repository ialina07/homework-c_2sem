#include "distributor.h"
#include "graph.h"
#include "state.h"
#include <assert.h>
#include <stdio.h>

static void testDistributorInit() {
    Distributor d;
    distributorInit(&d, 10, 3);

    assert(d.n == 10);
    assert(d.k == 3);
    assert(d.states != NULL);
    assert(d.visited != NULL);
    assert(d.stateCities != NULL);

    distributorFree(&d);
    printf("testDistributorInit passed!\n");
}

static void testSetCapitals() {
    Distributor d;
    distributorInit(&d, 5, 2);

    int capitals[] = {0, 3};
    distributorSetCapitals(&d, capitals, 2);

    assert(d.states[0] == 0);
    assert(d.states[3] == 1);
    assert(d.visited[0] == 1);
    assert(d.visited[3] == 1);

    distributorFree(&d);
    printf("testSetCapitals passed!\n");
}

static void testDistributeSimple() {
    Graph g;
    graphInit(&g, 4);
    graphAddEdge(&g, 0, 1, 10);
    graphAddEdge(&g, 1, 2, 10);
    graphAddEdge(&g, 2, 3, 10);

    Distributor d;
    distributorInit(&d, 4, 2);

    int capitals[] = {0, 3};
    distributorSetCapitals(&d, capitals, 2);

    distributorDistributeAll(&d, &g);

    for (int i = 0; i < 4; i++) {
        assert(d.visited[i] == 1);
        assert(d.states[i] != -1);
    }

    distributorFree(&d);
    printf("testDistributeSimple passed!\n");
}

int main() {
    printf("Running distributor tests\n");
    testDistributorInit();
    testSetCapitals();
    testDistributeSimple();
    printf("All distributor tests passed!\n");
    return 0;
}