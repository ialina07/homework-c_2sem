#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// получение высоты узла
static int getHeight(Node* node) {
    return node ? node->height : 0;
}

// вычисление фактора баланса
static int getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// обновление высоты узла
static void updateHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// создание нового узла
static Node* createNode(const char* code, const char* name) {
    Node* node = malloc(sizeof(Node));
    node->code = malloc(strlen(code) + 1);
    node->name = malloc(strlen(name) + 1);
    strcpy(node->code, code);
    strcpy(node->name, name);
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// правый поворот
static Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* t2 = x->right;

    x->right = y;
    y->left = t2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

// левый поворот
static Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* t2 = y->left;

    y->left = x;
    x->right = t2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

// балансируем узел
static Node* balanceNode(Node* node) {
    if (node == NULL)
        return NULL;
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    // перекос влево
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // перекос вправо
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// рекурсивная вставка узла
Node* avlInsert(Node* root, const char* code, const char* name) {
    if (root == NULL)
        return createNode(code, name);

    int cmp = strcmp(code, root->code);
    if (cmp < 0)
        root->left = avlInsert(root->left, code, name);
    else if (cmp > 0)
        root->right = avlInsert(root->right, code, name);
    else {
        // ключ уже существует, обновляем название
        free(root->name);
        root->name = malloc(strlen(name) + 1);
        strcpy(root->name, name);
    }
    return balanceNode(root);
}

// поиск минимального узла в поддереве, для удаления
static Node* findMinNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// удаление узла
Node* avlDelete(Node* root, const char* code) {
    if (root == NULL)
        return NULL;

    int cmp = strcmp(code, root->code);
    if (cmp < 0)
        root->left = avlDelete(root->left, code);
    else if (cmp > 0)
        root->right = avlDelete(root->right, code);
    else {
        // нашли удаляемый узел
        if (!root->left || !root->right) {
            // один потомок или ни одного
            Node* temp = root->left ? root->left : root->right;
            if (temp) {
                // копируем данные из потомка в текущий узел
                free(root->code);
                free(root->name);
                *root = *temp; // копируем структуру
                free(temp);
            } else {
                // нет потомков
                free(root->code);
                free(root->name);
                free(root);
                return NULL;
            }
        } else {
            // узел с двумя потомками: находим минимальный в правом поддереве
            Node* temp = findMinNode(root->right);
            // копируем данные из temp в root
            free(root->code);
            free(root->name);
            root->code = malloc(strlen(temp->code) + 1);
            root->name = malloc(strlen(temp->name) + 1);
            strcpy(root->code, temp->code);
            strcpy(root->name, temp->name);
            // удаляем temp из правого поддерева
            root->right = avlDelete(root->right, temp->code);
        }
    }
    return balanceNode(root);
}

// поиск узла по ключу
Node* avlFind(Node* root, const char* code) {
    if (root == NULL)
        return NULL;
    int cmp = strcmp(code, root->code);
    if (cmp < 0)
        return avlFind(root->left, code);
    else if (cmp > 0)
        return avlFind(root->right, code);
    else
        return root;
}

// освобождение памяти дерева
void avlFree(Node* root) {
    if (root == NULL)
        return;
    avlFree(root->left);
    avlFree(root->right);
    free(root->code);
    free(root->name);
    free(root);
}

// сохраняем все записи в файл
void avlSave(Node* root, FILE* out) {
    if (root == NULL)
        return;
    avlSave(root->left, out);
    fprintf(out, "%s:%s\n", root->code, root->name);
    avlSave(root->right, out);
}

// подсчет количества узлов
int avlCount(Node* root) {
    if (root == NULL)
        return 0;
    return 1 + avlCount(root->left) + avlCount(root->right);
}