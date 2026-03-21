#include "csvPrinter.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "использование: %s <input.csv> <output.txt>\n", argv[0]);
        return 1;
    }

    CSVTable* table = readCsv(argv[1]);
    if (!table) {
        return 1;
    }

    analyzeTable(table);
    printTable(table, argv[2]);
    freeTable(table);

    printf("Сделано. Результат записан в %s\n", argv[2]);
    return 0;
}
