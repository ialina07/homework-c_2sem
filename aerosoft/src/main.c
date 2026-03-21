#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

// разбор строки из файла airports.txt
static void parseLine(const char* line, char* code, char* name) {
    const char* colon = strchr(line, ':');
    if (colon == NULL) {
        code[0] = '\0';
        name[0] = '\0';
        return;
    }
    size_t codeLen = colon - line;
    strncpy(code, line, codeLen);
    code[codeLen] = '\0';
    strcpy(name, colon + 1);
    // удаляем '\n' в конце name
    char* newline = strchr(name, '\n');
    if (newline)
        *newline = '\0';
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <airports.txt>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return 1;
    }

    Node* root = NULL;
    char line[MAX_LINE];
    int count = 0;

    // загрузка данных
    while (fgets(line, sizeof(line), file)) {
        char code[10], name[256];
        parseLine(line, code, name);
        if (code[0] == '\0')
            continue; // пропускаем некорректные строки
        root = avlInsert(root, code, name);
        count++;
    }
    fclose(file);

    printf("Загружено %d аэропортов. Система готова к работе.\n", count);

    char cmd[MAX_LINE];
    while (1) {
        printf("> ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
            break;
        // удаляем символ новой строки
        cmd[strcspn(cmd, "\n")] = '\0';

        if (strncmp(cmd, "find ", 5) == 0) {
            const char* code = cmd + 5;
            Node* node = avlFind(root, code);
            if (node)
                printf("%s → %s\n", node->code, node->name);
            else
                printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
        } else if (strncmp(cmd, "add ", 4) == 0) {
            const char* arg = cmd + 4;
            char* colon = strchr(arg, ':');
            if (!colon) {
                printf("Неверный формат. Используйте: add <код>:<название>\n");
                continue;
            }
            char code[10];
            size_t codeLen = colon - arg;
            if (codeLen >= sizeof(code)) {
                printf("Код слишком длинный.\n");
                continue;
            }
            strncpy(code, arg, codeLen);
            code[codeLen] = '\0';
            const char* name = colon + 1;

            root = avlInsert(root, code, name);
            printf("Аэропорт '%s' добавлен в базу.\n", code);
        } else if (strncmp(cmd, "delete ", 7) == 0) {
            const char* code = cmd + 7;
            Node* node = avlFind(root, code);
            if (!node) {
                printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
            } else {
                root = avlDelete(root, code);
                printf("Аэропорт '%s' удалён из базы.\n", code);
            }
        } else if (strcmp(cmd, "save") == 0) {
            FILE* out = fopen(argv[1], "w");
            if (!out) {
                perror("Ошибка сохранения");
                continue;
            }
            avlSave(root, out);
            fclose(out);
            int newCount = avlCount(root);
            printf("База сохранена: %d аэропортов.\n", newCount);
        } else if (strcmp(cmd, "quit") == 0) {
            break;
        } else if (cmd[0] == '\0') {
            // если строка пустая, игнорируем
            continue;
        } else {
            printf("Неизвестная команда. Доступные: find <код>, add <код>:<название>, delete "
                   "<код>, save, quit\n");
        }
    }

    avlFree(root);
    return 0;
}
