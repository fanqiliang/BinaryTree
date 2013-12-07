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
    char    data[100];
    int     Num;
    int     key;

}Linktable;

int Partition(int list[][2], int low, int high);

void QuickSort(int list[][2], int low, int high);

void CreateTree();

void GetInfo(FILE *fp);

#endif

