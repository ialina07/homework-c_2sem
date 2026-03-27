#include "state.h"
#include <stdlib.h>

void stateInit(State* state) {
    state->capacity = 10;
    state->count = 0;
    state->cities = malloc(state->capacity * sizeof(int));
}

void stateAddCity(State* state, int city) {
    if (state->count >= state->capacity) {
        state->capacity *= 2;
        state->cities = realloc(state->cities, state->capacity * sizeof(int));
    }
    state->cities[state->count++] = city;
}

void stateFree(State* state) {
    if (state->cities != NULL) {
        free(state->cities);
        state->cities = NULL;
    }
    state->count = 0;
    state->capacity = 0;
}

void stateSortCities(State* state) {
    // сортировка пузырьком
    for (int i = 0; i < state->count - 1; i++) {
        for (int j = i + 1; j < state->count; j++) {
            if (state->cities[i] > state->cities[j]) {
                int temp = state->cities[i];
                state->cities[i] = state->cities[j];
                state->cities[j] = temp;
            }
        }
    }
}