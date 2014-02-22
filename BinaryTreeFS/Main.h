#ifndef MAIN_H
#define MAIN_H

#define RED -1
#define BLACK -2

typedef struct Node {
    int color;
    int key;
    char keywords[100];
    struct Node * left;
    struct Node * right;
    struct Node * parent;
}Node;

struct Node *NullNode;
struct Node *Root;
void InsertTree();

#endif
