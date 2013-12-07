#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>

typedef struct TreeNode {
    struct   TreeNode * left;
    struct   TreeNode * right;
    void     * data;
    int      Num;
}TreeNode;

typedef struct Linktable {
    struct  Linktable *next;
    char    data[20];
    int     Num;
}Linktable;

void CreateTree();

void GetInfo();

FILE * OpenTxt();
#endif

