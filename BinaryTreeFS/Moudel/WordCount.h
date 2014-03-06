#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>

#define RED 0
#define BLACK 1
#define READ 2
#define UNREAD 3
#define MAX 30

typedef struct Node {
    int key;
    int color;
    int state;
    char keywords[MAX];
    struct Node * left;
    struct Node * right;
    struct Node * parent;
}Node;

typedef struct LNode{
    struct  LNode *next;
    char    keywords[MAX];
    int     key;

}LNode;

char *stopten[10];
int   itopten[10];
LNode *Head;
Node  *Root;
Node  *NullNode;
extern LNode *CreateLNode(char *word);
extern void  CreateLinkTabel(char *word);

extern void  ReadWords(FILE *fp, char *type);
extern Node  *NULLNODE();
extern Node  *CreateRoot(Node *node, char *keywords);
extern Node  *CreateNode(Node *pnode, char *keywords);
extern void  LeftRotate(Node *node);
extern void  RightRotate(Node *node);
extern void  InsertFixUp(Node *node);
extern void  TreeInsert(char *keywords);
extern void  CreateTree();
extern Node  *TravNode(Node *node);
extern void  getRBInfo();
extern void  BullbeSort();
extern void  Print();

#endif
