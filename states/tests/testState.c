#include "state.h"
#include <assert.h>
#include <stdio.h>

static void testStateInit() {
    State s;
    stateInit(&s);

    assert(s.cities != NULL);
    assert(s.count == 0);
    assert(s.capacity == 10);

    stateFree(&s);
    printf("testStateInit passed!\n");
}

static void testStateAddCity() {
    State s;
    stateInit(&s);

    stateAddCity(&s, 5);
    assert(s.count == 1);
    assert(s.cities[0] == 5);

    stateAddCity(&s, 3);
    assert(s.count == 2);
    assert(s.cities[1] == 3);

    stateFree(&s);
    printf("testStateAddCity\n");
}

static void testStateSortCities() {
    State s;
    stateInit(&s);

    stateAddCity(&s, 5);
    stateAddCity(&s, 1);
    stateAddCity(&s, 8);
    stateAddCity(&s, 3);

    stateSortCities(&s);

    assert(s.cities[0] == 1);
    assert(s.cities[1] == 3);
    assert(s.cities[2] == 5);
    assert(s.cities[3] == 8);

    stateFree(&s);
    printf("testStateSortCities passed!\n");
}

int main() {
    printf("Running state tests...\n");
    testStateInit();
    testStateAddCity();
    testStateSortCities();
    printf("All state tests passed!\n");
    return 0;
}