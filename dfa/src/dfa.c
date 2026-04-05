#include "dfa.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// проверяет, является ли символ цифрой
static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// проверяет, входит ли состояние в список допустимых
static bool isAccepting(Dfa* dfa, int state) {
    for (int i = 0; i < dfa->numAccepting; i++) {
        if (dfa->acceptingStates[i] == state) {
            return true;
        }
    }
    return false;
}

// ищет переход для состояния и символа
static int findTransition(Dfa* dfa, int state, char symbol) {
    for (int i = 0; i < dfa->numTransitions; i++) {
        Transition* t = &dfa->transitions[i];
        if (t->fromState == state) {
            if (t->symbol == 'd' && isDigit(symbol)) {
                return t->toState;
            }
            if (t->symbol == symbol) {
                return t->toState;
            }
        }
    }
    return -1;
}

// создаёт новый ДКА
Dfa* dfaCreate(int numStates, Transition* transitions, int numTransitions, int* acceptingStates,
               int numAccepting, int startState, DfaError* error) {

    if (error)
        *error = DFA_OK;

    // проверка входных данных
    if (numStates <= 0 || transitions == NULL || numTransitions <= 0 || acceptingStates == NULL ||
        numAccepting <= 0) {
        if (error)
            *error = DFA_ERROR_TRANSITION;
        return NULL;
    }

    Dfa* dfa = (Dfa*)malloc(sizeof(Dfa));
    if (dfa == NULL) {
        if (error)
            *error = DFA_ERROR_TRANSITION;
        return NULL;
    }

    dfa->numStates = numStates;
    dfa->numTransitions = numTransitions;
    dfa->numAccepting = numAccepting;
    dfa->startState = startState;

    dfa->transitions = (Transition*)malloc(sizeof(Transition) * numTransitions);
    if (dfa->transitions == NULL) {
        free(dfa);
        if (error)
            *error = DFA_ERROR_TRANSITION;
        return NULL;
    }

    // копируем переходы
    for (int i = 0; i < numTransitions; i++) {
        dfa->transitions[i].fromState = transitions[i].fromState;
        dfa->transitions[i].symbol = transitions[i].symbol;
        dfa->transitions[i].toState = transitions[i].toState;
    }

    dfa->acceptingStates = (int*)malloc(sizeof(int) * numAccepting);
    if (dfa->acceptingStates == NULL) {
        free(dfa->transitions);
        free(dfa);
        if (error)
            *error = DFA_ERROR_TRANSITION;
        return NULL;
    }

    // копируем допустимые состояния
    for (int i = 0; i < numAccepting; i++) {
        dfa->acceptingStates[i] = acceptingStates[i];
    }

    return dfa;
}

// удаляет ДКА и освобождает память
void dfaDestroy(Dfa* dfa) {
    if (dfa != NULL) {
        if (dfa->transitions != NULL) {
            free(dfa->transitions);
        }
        if (dfa->acceptingStates != NULL) {
            free(dfa->acceptingStates);
        }
        free(dfa);
    }
}

// проверяет строку на принадлежность языку
bool dfaCheck(Dfa* dfa, const char* input, DfaError* error) {
    if (error)
        *error = DFA_OK;

    if (dfa == NULL || input == NULL) {
        if (error)
            *error = DFA_ERROR_NULL_POINTER;
        return false;
    }

    if (input[0] == '\0') {
        if (error)
            *error = DFA_ERROR_EMPTY_STRING;
        return false;
    }

    int currentState = dfa->startState;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (c == 'e' || c == 'E') {
            c = 'E';
        }

        if (!isDigit(c) && c != '.' && c != 'E' && c != '+' && c != '-') {
            if (error)
                *error = DFA_ERROR_INVALID_SYMBOL;
            return false;
        }

        // ищем переход
        int nextState = findTransition(dfa, currentState, c);
        if (nextState == -1) {
            if (error)
                *error = DFA_ERROR_INVALID_SYMBOL;
            return false;
        }

        currentState = nextState;
    }

    // проверяем, допустимое ли конечное состояние
    return isAccepting(dfa, currentState);
}

// возвращает текст ошибки
const char* dfaErrorString(DfaError error) {
    switch (error) {
    case DFA_OK:
        return "OK";
    case DFA_ERROR_INVALID_SYMBOL:
        return "Invalid symbol in input";
    case DFA_ERROR_NULL_POINTER:
        return "Null pointer provided";
    case DFA_ERROR_EMPTY_STRING:
        return "Empty string";
    case DFA_ERROR_TRANSITION:
        return "Transition creation error";
    default:
        return "Unknown error";
    }
}