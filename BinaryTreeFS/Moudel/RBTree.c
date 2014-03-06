#include "WordCount.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Node * NULLNODE() {
    Node *nullnode = (Node *)malloc(sizeof(struct Node));
    nullnode->color = BLACK;
    nullnode->key = 0;
    nullnode->state = UNREAD;
    nullnode->left = NULL;
    nullnode->right = NULL;
    nullnode->parent = NULL;
    return nullnode;
}

Node * CreateRoot(Node *node, char *keywords) {
    printf("now, you are using red-black tree.\n");
    struct Node *pnode = (struct Node *)malloc(sizeof(struct Node));
    pnode->color = BLACK;
    pnode->key = 1;
    pnode->state = UNREAD;
    strcpy(pnode->keywords, keywords);
    pnode->left = NullNode;
    pnode->right = NullNode;
    pnode->parent = NULL;
    return pnode;
}

Node * CreateNode(Node *pnode, char keywords[]) {
    struct Node *node = (Node *)malloc(sizeof(struct Node));
    node->color = RED;
    node->key = 1;
    node->state = UNREAD;
    strcpy(node->keywords, keywords);
    node->left = NullNode;
    node->right = NullNode;
    node->parent = pnode;
    return node;
}

void LeftRotate(Node *node) {
    struct Node *tNode = node->right;
    node->right = tNode->left;
    if (tNode->left != NullNode)
        tNode->left->parent = node;
    tNode->parent = node->parent;
    if (node->parent == NULL) {
        Root = tNode;
        Root->parent = NULL;
    }
    else if (node->parent->left == node)
        node->parent->left = tNode;
    else
        node->parent->right = tNode;
    tNode->left = node;
    node->parent = tNode;
}


void RightRotate(Node *node) {
    struct Node *tNode = node->left;
    node->left = tNode->right;
    if (tNode->right != NullNode)
        tNode->right->parent = node;
    tNode->parent = node->parent;
    if (node->parent == NULL) {
        Root = tNode;
        Root->parent = NULL;
    }
    else if (node->parent->right == node)
        node->parent->right = tNode;
    else
        node->parent->left = tNode;
    tNode->right = node;
    node->parent = tNode;
}

void InsertFixUp(Node * node) {
    struct Node *pnode = node;
    struct Node *tNode = NULL;
    while (pnode->parent != NULL && pnode->parent->color == RED) {
        if (pnode->parent != NULL && pnode->parent->parent != NULL) {
            if (pnode->parent->parent->left == pnode->parent) {
                tNode = pnode->parent->parent->right;
                if (tNode->color == RED) {
                    tNode->color = BLACK;
                    pnode->parent->color = BLACK;
                    pnode->parent->parent->color = RED;
                    pnode = pnode->parent->parent;
                } else if(tNode->color == BLACK) {
                    if (pnode->parent->right == pnode) {
                        pnode = pnode->parent;
                        LeftRotate(pnode);
                    } else {
                        pnode->parent->color = BLACK;
                        pnode->parent->parent->color = RED;
                        RightRotate(pnode->parent->parent);
                    }
                }
            } else {
                tNode = pnode->parent->parent->left;
                if (tNode->color == RED) {
                    tNode->color = BLACK;
                    pnode->parent->color = BLACK;
                    pnode->parent->parent->color = RED;
                    pnode = pnode->parent->parent;
                    if (pnode->parent == NULL)
                        break;
                } else if (tNode->color == BLACK) {
                    if (pnode->parent->left == pnode) {
                        pnode = pnode->parent;
                        RightRotate(pnode);
                    } else {
                        pnode->parent->color = BLACK;
                        pnode->parent->parent->color = RED;
                        LeftRotate(pnode->parent->parent);
                    }
                }
            }
        } else 
            break;
    }
    Root->color = BLACK;
}

void TreeInsert(char * keywords) {
    if (Root == NULL) {
        Root = CreateRoot(Root, keywords);
        return;
    }
    struct Node *node = NullNode;
    struct Node *pnode = NULL;
    node = Root;
    int flag = 1; /*0 is right child and 1 is left child*/
    while (node != NullNode) {
        if (strcmp(node->keywords, keywords) == 0) {
            node->key++;
            return;
        } else if (strcmp(node->keywords, keywords) < 0)  {
            pnode = node;
            node = node->right;
            flag = 0;
        } else {
            pnode = node;
            node = node->left;
            flag = 1;
        }
    }
    node = CreateNode(pnode, keywords);
    if (flag == 1)
        node->parent->left = node;
    else
        node->parent->right = node;
    InsertFixUp(node);
}


