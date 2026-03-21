#ifndef CSV_PRINTER_H
#define CSV_PRINTER_H

typedef struct {
    char*** data;
    int rows;       // количество строк
    int cols;       // количество столбцов
    int* isNumber;  // флаги: 1 если колонка числовая
    int* colWidths; // ширина каждого столбца
} CSVTable;

// Основные функции
CSVTable* readCsv(const char* filename);
void analyzeTable(CSVTable* table);
void printTable(const CSVTable* table, const char* filename);
void freeTable(CSVTable* table);
int isNumber(const char* str);

#endif
