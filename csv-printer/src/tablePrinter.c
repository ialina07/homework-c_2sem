#include "csvPrinter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Определяем типы колонок и максимальную ширину
void analyzeTable(CSVTable* t)
{
    t->isNumber = (int*)malloc(sizeof(int) * t->cols);
    t->colWidths = (int*)malloc(sizeof(int) * t->cols);

    // инициализация: считаем все колонки числовыми, ширина 0
    for (int j = 0; j < t->cols; j++) {
        t->isNumber[j] = 1;
        t->colWidths[j] = 0;
    }

    // проходим по всем строкам, начиная с данных (индекс 1, если есть заголовок)
    for (int i = 1; i < t->rows; i++) {
        for (int j = 0; j < t->cols; j++) {
            int len = (int)strlen(t->data[i][j]);
            if (len > t->colWidths[j])
                t->colWidths[j] = len;

            // Хоть одна ячейка не число, тогда колонка перестаёт быть числовой
            if (t->isNumber[j] && !isNumber(t->data[i][j]))
                t->isNumber[j] = 0;
        }
    }

    // Учитываем заголовок
    for (int j = 0; j < t->cols; j++) {
        int headerLen = (int)strlen(t->data[0][j]);
        if (headerLen > t->colWidths[j])
            t->colWidths[j] = headerLen;
    }
}

// вывод таблицы в файл
void printTable(const CSVTable* t, const char* filename)
{
    FILE* out = fopen(filename, "w");
    if (!out) {
        fprintf(stderr, "Ошибка: не удалось создать выходной файл %s\n", filename);
        return;
    }

    // Верхняя граница
    fprintf(out, "+");
    for (int j = 0; j < t->cols; j++) {
        for (int k = 0; k < t->colWidths[j] + 2; k++)
            fprintf(out, "=");
        fprintf(out, "+");
    }
    fprintf(out, "\n");

    // Заголовок
    fprintf(out, "|");
    for (int j = 0; j < t->cols; j++) {
        fprintf(out, " %-*s |", t->colWidths[j], t->data[0][j]);
    }
    fprintf(out, "\n");

    // Разделитель после заголовка
    fprintf(out, "+");
    for (int j = 0; j < t->cols; j++) {
        for (int k = 0; k < t->colWidths[j] + 2; k++)
            fprintf(out, "=");
        fprintf(out, "+");
    }
    fprintf(out, "\n");

    // Данные
    for (int i = 1; i < t->rows; i++) {
        fprintf(out, "|");
        for (int j = 0; j < t->cols; j++) {
            if (t->isNumber[j]) {
                // числа вправо
                fprintf(out, " %*s |", t->colWidths[j], t->data[i][j]);
            } else {
                // текст влево
                fprintf(out, " %-*s |", t->colWidths[j], t->data[i][j]);
            }
        }
        fprintf(out, "\n");

        // Разделитель между строками (кроме последней)
        if (i < t->rows - 1) {
            fprintf(out, "+");
            for (int j = 0; j < t->cols; j++) {
                for (int k = 0; k < t->colWidths[j] + 2; k++)
                    fprintf(out, "-");
                fprintf(out, "+");
            }
            fprintf(out, "\n");
        }
    }

    fclose(out);
}

void freeTable(CSVTable* t)
{
    for (int i = 0; i < t->rows; i++) {
        for (int j = 0; j < t->cols; j++)
            free(t->data[i][j]);
        free(t->data[i]);
    }
    free(t->data);
    free(t->isNumber);
    free(t->colWidths);
    free(t);
}
