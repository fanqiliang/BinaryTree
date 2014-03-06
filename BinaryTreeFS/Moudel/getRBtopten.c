#include "WordCount.h"
#include <stdio.h>

/*Read words according to its key order*/
Node * TravNode(Node *node) {
    if (node->right != NullNode) {
        node = node->right;
        while (node != NullNode) {
            if (node->left != NullNode)
                node = node->left;
            else
                break;
        }
        return node;
    } else {
        if (node->parent != NULL) {
            node = node->parent;
            while (node->state == READ) {
                node = node->parent;
                if (node == NULL)
                    return NULL;
            }
            return node;
        }
        else
            return NULL;
    }
}



void getRBInfo() {
    struct Node *node = NULL;
    struct Node *rnode = NULL;
    if (Root == NULL)
        printf("The file is null.");
    else {
        node = Root;
    }
    while (node != NullNode) {
        if (node->right != NullNode)
            node = node->right;
        else
            break;
    }
    rnode = node;
    node = Root;
    while (node != NullNode) {
        if (node->left != NullNode)
            node = node->left;
        else
            break;
    }
    int i = 0;
    itopten[i] = node->key;  /*itopten used to store top 10 words' times*/
    stopten[i] = node->keywords; /*stopten used to store top 10 words*/
    printf("The highest frequency of 10 words and the number of them appear:\n");
    while (node != rnode) {
        node->state = READ;
        node = TravNode(node);
        if (i < 9) {
            i++;
            itopten[i] = node->key;
            stopten[i] = node->keywords;
            BullbeSort(itopten, 0, i);
        } else {
            BullbeSort(itopten, 0, i);
            if (itopten[0] < node->key) {
                itopten[0] = node->key;
                stopten[0] = node->keywords;
            }
        }
    } 
    int t = 1; /*just for print 1,2,3,...,10*/
    for (int j = i; j >= 0; j--) {
        printf("The top %d is %s    %d\n", t++, stopten[j], itopten[j]);
    }
}
