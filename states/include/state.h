#pragma once

typedef struct {
    int* cities;
    int count;
    int capacity;
} State;

// инициализация государства
void stateInit(State* state);

// добавление грода в государство
void stateAddCity(State* state, int city);

// освобождение памяти
void stateFree(State* state);

// сортировка городов государства
void stateSortCities(State* state);
