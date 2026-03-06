#include "csvPrinter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024
#define MAX_COLS 100
#define MAX_ROWS 1000

// Проверяем, является ли строка числом
int isNumber(const char* str)
{
    if (str == NULL || *str == '\0')
        return 0;
    char* endptr;
    strtod(str, &endptr);
    // если после числа ничего нет, то это число
    return *endptr == '\0';
}

// Чтение CSV-файла и заполнение таблицы
CSVTable* readCsv(const char* filename)
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Cannot open input file %s\n", filename);
        return NULL;
    }

    CSVTable* t = (CSVTable*)malloc(sizeof(CSVTable));
    t->data = (char***)malloc(sizeof(char**) * MAX_ROWS);
    t->rows = 0;
    t->cols = 0;

    char line[MAX_LINE_LEN];
    int row = 0;

    while (fgets(line, sizeof(line), f) && row < MAX_ROWS) {
        line[strcspn(line, "\n")] = '\0';

        // Пропуск пустых строк
        if (line[0] == '\0')
            continue;

        // Разделяем на колонки по запятой
        char* token = strtok(line, ",");
        int col = 0;
        t->data[row] = (char**)malloc(sizeof(char*) * MAX_COLS);

        while (token && col < MAX_COLS) {
            t->data[row][col] = (char*)malloc(strlen(token) + 1);
            strcpy(t->data[row][col], token);
            col++;
            token = strtok(NULL, ",");
        }

        // Если в первой строке определили количество колонок
        if (row == 0) {
            t->cols = col;
        } else {
            // Если в текущей строке меньше колонок, остаток заполняем пустыми строками
            while (col < t->cols) {
                t->data[row][col] = (char*)malloc(1);
                t->data[row][col][0] = '\0';
                col++;
            }
        }
        row++;
    }
    t->rows = row;
    fclose(f);
    return t;
}
