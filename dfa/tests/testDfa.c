#include "dfa.h"
#include <stdio.h>

static void runTest(const char* input, bool expected) {
    int acceptingStates[] = {2, 4, 7};
    Transition transitions[] = {{0, 'd', 2}, {0, '-', 1}, {0, '.', 3}, {1, 'd', 2},
                                {1, '.', 3}, {2, 'd', 2}, {2, '.', 3}, {2, 'E', 5},
                                {3, 'd', 4}, {4, 'd', 4}, {4, 'E', 5}, {5, 'd', 7},
                                {5, '+', 6}, {5, '-', 6}, {6, 'd', 7}, {7, 'd', 7}};
    int numTransitions = sizeof(transitions) / sizeof(transitions[0]);

    DfaError error;
    Dfa* dfa = dfaCreate(8, transitions, numTransitions, acceptingStates, 3, 0, &error);

    DfaError checkError;
    bool result = dfaCheck(dfa, input, &checkError);

    printf("Test '%s': %s (expected %s)\n", input, result ? "PASS" : "FAIL",
           expected ? "PASS" : "FAIL");

    dfaDestroy(dfa);
}

int main() {
    runTest("123", true);
    runTest("-123", true);
    runTest(".591", true);
    runTest("-.591", true);
    runTest("123.45E-6", true);
    runTest("38.871E5", true);
    runTest("823.16.10", false);
    runTest("А я число?", false);
    runTest(".E5", false);
    runTest("", false);
    runTest("abc", false);

    return 0;
}