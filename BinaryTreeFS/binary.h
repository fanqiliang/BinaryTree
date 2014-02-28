#ifndef BINARY_H
#define BINARY_H

#include <stdio.h>
#define MAX 100
#define RED -1
#define BLACK -2
#define READ -3
#define UNREAD -4

typedef struct Node {
    int color;
    int key;
    int state;
    char keywords[MAX];
    struct Node * left;
    struct Node * right;
    struct Node * parent;
}Node;

char *stopten[10];
int  itopten[10];
struct Node *NullNode;
struct Node *Root;
void ReadWords(FILE *fp);
Node *NULLNODE();
Node *CreateRoot(Node *node, char *keywords);
Node *CreateNode(Node *pnode, char *keywords);
void LeftRotate(Node *node);
void RightRotate(Node *node);
void InsertFixUp(Node *node);
void TreeInsert(char *keywords);
void CreateTree();
Node *TravNode(Node *node);
void Print();

#endif
