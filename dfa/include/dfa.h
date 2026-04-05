#ifndef DFA_H
#define DFA_H

#include <stdbool.h>

// коды ошибок
typedef enum {
    DFA_OK = 0,
    DFA_ERROR_INVALID_SYMBOL,
    DFA_ERROR_NULL_POINTER,
    DFA_ERROR_EMPTY_STRING,
    DFA_ERROR_TRANSITION
} DfaError;

// структура перехода
typedef struct {
    int fromState;
    char symbol;
    int toState;
} Transition;

// структура ДКА (хранит все состояния, переходы и правила)
typedef struct {
    int numStates;
    Transition* transitions;
    int numTransitions;
    int* acceptingStates;
    int numAccepting;
    int startState;
} Dfa;

// создает новый ДКА
Dfa* dfaCreate(int numStates, Transition* transitions, int numTransitions, int* acceptingStates,
               int numAccepting, int startState, DfaError* error);

// удаляет ДКА и освобождает память
void dfaDestroy(Dfa* dfa);

// проверяет, соответствует ли строка правилам ДКА
bool dfaCheck(Dfa* dfa, const char* input, DfaError* error);

// возвращает описание ошибки по ее коду
const char* dfaErrorString(DfaError error);

#endif