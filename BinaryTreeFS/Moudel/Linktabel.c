#include "WordCount.h"
#include <string.h>
#include <stdlib.h>

LNode * CreateLNode(char *word) {
    LNode *node = (LNode *)malloc(sizeof(struct LNode));
    node->key = 1;
    strcpy(node->keywords, word);
    node->next = NULL;
    return node;
}

void CreateLinkTabel(char *word) {
    LNode *tnode = NULL;
    if (Head == NULL) {
        printf("now , you are using Linktabel\n");
        Head = CreateLNode(word);
        return;
    }
    LNode *node = Head;
    while (node != NULL) {
        if (strcmp(node->keywords, word) == 0) {
            node->key++;
            return;
        }
        tnode = node;
        node = node->next;
    }
    node = CreateLNode(word);
    tnode->next = node;
    return;
}

