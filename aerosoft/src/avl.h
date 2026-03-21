#ifndef AVL_H
#define AVL_H

#include <stdio.h>

typedef struct Node {
    char *code;
    char *name;
    int height; //высота поддерева
    struct Node *left;
    struct Node *right;
} Node;

Node* avlInsert(Node *root, const char *code, const char *name);
Node* avlDelete(Node *root, const char *code);
Node* avlFind(Node *root, const char *code);
void avlFree(Node *root);
void avlSave(Node *root, FILE *out); 
int avlCount(Node *root); 

#endif 



