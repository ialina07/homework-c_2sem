#include "graph.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

static void testGraphInit() {
    Graph g;
    graphInit(&g, 5);

    assert(g.n == 5);
    assert(g.edgeCount == 0);
    for (int i = 0; i < 5; i++) {
        assert(g.head[i] == -1);
    }
    printf("testGraphInit passed!\n");
}

static void testGraphAddEdge() {
    Graph g;
    graphInit(&g, 4);

    graphAddEdge(&g, 0, 1, 10);
    graphAddEdge(&g, 2, 3, 25);

    assert(g.edgeCount == 4); // 2 ребра * 2 направления
    assert(g.head[0] != -1);
    assert(g.head[2] != -1);

    printf("testGraphAddEdge passed!\n");
}

static void testGraphGetDistance() {
    Graph g;
    graphInit(&g, 4);

    graphAddEdge(&g, 0, 1, 10);
    graphAddEdge(&g, 1, 2, 15);
    graphAddEdge(&g, 0, 3, 20);

    assert(graphGetDistance(&g, 0, 1) == 10);
    assert(graphGetDistance(&g, 1, 0) == 10);
    assert(graphGetDistance(&g, 1, 2) == 15);
    assert(graphGetDistance(&g, 2, 1) == 15);
    assert(graphGetDistance(&g, 0, 3) == 20);
    assert(graphGetDistance(&g, 3, 0) == 20);
    assert(graphGetDistance(&g, 0, 2) == INT_MAX);

    printf("testGraphGetDistance passed!\n");
}

int main() {
    printf("Running graph tests\n");
    testGraphInit();
    testGraphAddEdge();
    testGraphGetDistance();
    printf("All graph tests passed!\n");
    return 0;
}