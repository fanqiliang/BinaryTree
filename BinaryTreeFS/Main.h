#ifndef MAIN_H
#define MAIN_H

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

typedef struct Words {
    int key;
    char keywords[MAX];
}Words;

typedef struct LNode {
    char keywords[MAX];
    int key;
    struct LNode *next;
}LNode;

struct LNode *Head;
struct Node *NullNode;
struct Node *Root;
struct LNode *CreateLNode(char *word);
void ReadWordInfo(char *word);
void ReadWords(FILE *fp);
Node *NULLNODE();
Node *CreateRoot(Node *node, int key, char *keywords);
Node *CreateNode(Node *pnode, int key, char *keywords);
void LeftRotate(Node *node);
void RightRotate(Node *node);
void InsertFixUp(Node *node);
Node *TreeSuccessor(Node *node);
Node *TreeMinimum(Node *node);
void DeleteFixUp(Node *node);
void DeleteNode(Node *node);
void TreeInsert(int key, char *keywords);
void CreateTree();
Node *TravNode(Node *node);
void Print();

#endif
