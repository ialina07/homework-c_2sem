#include "dfa.h"
#include <stdio.h>
#include <string.h>

int main() {
    // состояния: 0-7 (добавилось состояние проверки на -)
    int acceptingStates[] = {2, 4, 7};
    int numAccepting = 3;

    Transition transitions[] = {{0, 'd', 2}, {0, '-', 1}, {0, '.', 3}, {1, 'd', 2},
                                {1, '.', 3}, {2, 'd', 2}, {2, '.', 3}, {2, 'E', 5},
                                {3, 'd', 4}, {4, 'd', 4}, {4, 'E', 5}, {5, 'd', 7},
                                {5, '+', 6}, {5, '-', 6}, {6, 'd', 7}, {7, 'd', 7}};

    int numTransitions = sizeof(transitions) / sizeof(transitions[0]);

    DfaError error;
    Dfa* dfa = dfaCreate(8, transitions, numTransitions, acceptingStates, numAccepting, 0, &error);

    if (dfa == NULL) {
        printf("Ошибка создания DFA: %s\n", dfaErrorString(error));
        return 1;
    }

    printf("Введите строку ");

    char input[256];
    if (fgets(input, sizeof(input), stdin)) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        DfaError checkError;
        bool result = dfaCheck(dfa, input, &checkError);

        if (checkError != DFA_OK) {
            printf("Ошибка: %s\n", dfaErrorString(checkError));
        } else if (result) {
            printf("Это число!\n");
        } else {
            printf("Это не число :(:(\n");
        }
    }

    dfaDestroy(dfa);
    return 0;
}