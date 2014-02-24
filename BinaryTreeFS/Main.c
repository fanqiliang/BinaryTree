#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct LNode *CreateLNode(LNode *node, char *word) {
    node = (LNode *)malloc(sizeof(struct LNode));
    node->next = NULL;
    node->key = 1;
    strcpy(node->keywords, word);
    return node;
}

void ReadWordInfo(char *word) {
    struct LNode *node = NULL;
    if (Head != NULL) {
        Head = (LNode *)malloc(sizeof(struct LNode));
        strcpy(Head->keywords, word);
        Head->key = 1;
        Head->next = NULL;
    }
    node = Head;
    while (node != NULL) {
        if (strcmp(node->keywords, word) == 0)
            node->key++;
        else {
            if (node->next == NULL)
                node = CreateLNode(node, word);
            else
                node = node->next;
        }
    }
}

void ReadWords(FILE *fp) {
    char *word;
    char ch;
    int i = 0;

    ch = fgetc(fp);
    while(ch != EOF) {
        while (!(isalnum(ch))) {
            if (ch == EOF)
                return;
            ch = fgetc(fp);
        }
        if (ch == EOF)
            return;
        word[i] = ch;
        i++;
        ch = fgetc(fp);
        if (!(isalnum(ch))) {
            word[i] = '\0';
            ReadWordInfo(word);
        }
    }
    return;
}

Node * NULLNODE() {
    Node *nullnode = (Node *)malloc(sizeof(struct Node));
    nullnode->color = BLACK;
    nullnode->key = 0;
    nullnode->left = NULL;
    nullnode->right = NULL;
    nullnode->parent = NULL;
    return nullnode;
}
Node * CreateRoot(char keywords[]) {
    Root = (struct Node *)malloc(sizeof(struct Node));
    Root->color = BLACK;
    Root->key = 1;
    strcpy(Root->keywords, keywords);
    Root->left = NullNode;
    Root->right = NullNode;
    Root->parent = NullNode;
    return Root;
}

Node * CreateNode(Node *pnode, char keywords[]) {
    struct Node *node = (Node *)malloc(sizeof(struct Node));
    node->color = RED;
    node->key = 1;
    strcpy(node->keywords, keywords);
    node->left = NullNode;
    node->right = NullNode;
    node->right = pnode;
    return node;
}

void LeftRotate(Node *Root, Node *node) {
    struct Node *tNode = node->right;
    node->right = tNode->left;
    if (tNode->left != NullNode)
        tNode->left->parent = node;
    tNode->parent = node->parent;
    if (node->parent == NULL)
        Root = tNode;
    else if (node->parent->left == node)
        node->parent->left = tNode;
    else
        node->parent->right = tNode;
    tNode->left = node;
    node->parent = tNode;
}


void RightRotate(Node *Root, Node *node) {
    struct Node *tNode = node->left;
    node->left = tNode->right;
    if (tNode->right != NullNode)
        tNode->right->parent = node;
    tNode->parent = node->parent;
    if (node->parent == NULL)
        Root = tNode;
    else if (node->parent->right == node)
        node->parent->right = tNode;
    else
        node->parent->left = tNode;
    tNode->right = node;
    node->parent = tNode;
}

void InsertFixup(Node * Root, Node * node) {
    struct Node *pnode = node;
    while (pnode->parent->color == RED) {
        if (pnode->parent != NULL && pnode->parent->parent != NULL) {
            if (pnode->parent->parent->left == pnode->parent) {
                struct Node *tNode = pnode->parent->parent->right;
                if (tNode->color == RED) {
                    tNode->color = BLACK;
                    pnode->parent->color = BLACK;
                    pnode->parent->parent->color = RED;
                    pnode = pnode->parent->parent;
                } else if (pnode->parent->right == pnode) {
                    pnode = pnode->parent;
                    LeftRotate(Root, pnode);
                }
                pnode->parent->color = BLACK;
                pnode->parent->parent->color = RED;
                RightRotate(Root, node);
            } else {
                struct Node *tNode = pnode->parent->parent->left;
                if (tNode->color == RED) {
                    tNode->color = BLACK;
                    pnode->parent->color = BLACK;
                    pnode->parent->parent->color = RED;
                    pnode = pnode->parent->parent;
                } else if (pnode->parent->left == pnode) {
                    pnode = pnode->parent;
                    RightRotate(Root, pnode);
                }
                pnode->parent->color = BLACK;
                pnode->parent->parent->color = RED;
                LeftRotate(Root, node);
            }
        }
    }
    Root->color = BLACK;
}

Node * TreeMinimum(Node *node) {
    while (node->left != NullNode)
        node = node->left;
    return node;
}

Node * TreeSuccessor(Node *node) {
    struct Node *tNode = NULL;
    if (node->right != NullNode)
        return TreeMinimum(node->right);
    tNode = node->parent;
    while (tNode != NULL && node == tNode->right) {
        node = tNode;
        tNode = node->parent;
    }
    return tNode;
}

void DeleteFixUp(Node *Root, Node *node) {
    struct Node * wNode = NULL;
    while (node != Root && node->color == BLACK) {
        if (node->parent->left == node) {
            wNode = node->parent->right;
            if (wNode->color == RED) {
                wNode->color = BLACK;
                node->parent->color = RED;
                LeftRotate(Root, node->parent);
                wNode = node->parent->right;
            }
            if (wNode->left->color == BLACK && 
                    wNode->right->color == BLACK) {
                wNode->color = RED;
                node = node->parent;
            } else if (wNode->right->color == BLACK) {
                wNode->left->color = BLACK;
                wNode->color = RED;
                RightRotate(Root, wNode);
                wNode = node->parent->right;
            }
            wNode->color = node->parent->color;
            node->parent->color = BLACK;
            wNode->right->color = BLACK;
            LeftRotate(Root, node->parent);
            Root = node;
        } else {
            wNode = node->parent->left;
            if (wNode->color == RED) {
                wNode->color = BLACK;
                node->parent->color = RED;
                RightRotate(Root, node->parent);
                wNode = node->parent->left;
            }
            if (wNode->right->color == BLACK && 
                    wNode->left->color == BLACK) {
                wNode->color = RED;
                node = node->parent;
            } else if (wNode->left->color == BLACK) {
                wNode->right->color = BLACK;
                wNode->color = RED;
                LeftRotate(Root, wNode);
                wNode = node->parent->left;
            }
            wNode->color = node->parent->color;
            node->parent->color = BLACK;
            wNode->left->color = BLACK;
            RightRotate(Root, node->parent);
            Root = node;
        }
    }
    node->color = BLACK;
}

void DeleteNode(Node *Root, Node *node) {
    struct Node *tNode = NULL;
    struct Node *pNode = NULL;
    if (node->left == NullNode || node->right == NullNode)
        tNode = node;
    else
        tNode = TreeSuccessor(node);
    if (tNode->left != NullNode)
        pNode = tNode->left;
    else
        pNode = tNode->right;
    pNode->parent = tNode->parent;
    if (tNode->parent == NULL)
        Root = pNode;
    else if (tNode->parent->left == tNode)
        pNode = tNode->parent->left;
    else
        pNode = tNode->parent->right;
    if (tNode != node)
        strcpy(node->keywords, tNode->keywords);
    if (tNode->color == BLACK)
        DeleteFixUp(Root, pNode);
}

void TreeInsert(Node *Root, char keywords[]) {
    NullNode = NULLNODE();
    struct Node *pnode = NullNode;
    if (Root == NullNode) {
        Root = CreateRoot(keywords);
        return;
    }
    pnode = Root;
    while (pnode != NullNode) {
        if (strcmp(keywords, pnode->keywords)) {
            pnode->key++;
            return;
        }
        int i;
        for (i = 0; pnode->keywords[i] != '\0' 
                && keywords[i] != '\0'; i++) {
            if (keywords[i] < pnode->keywords[i]) {
                if (pnode->left == NullNode) {
                    pnode->left = CreateNode(pnode, keywords);
                    return;
                }
                pnode = pnode->left;
            }
            else if (keywords[i] > pnode->keywords[i]) {
                if (pnode->right == NullNode) {
                    pnode->right = CreateNode(pnode, keywords);
                    return;
                }
                pnode = pnode->right;
            }
        }
        if (keywords[i] != '\0') {
            if (pnode->left == NullNode) {
                pnode->left = CreateNode(pnode, keywords);
                return;
            }
            pnode = pnode->left;
        } else {
            if (pnode->right == NullNode) {
                pnode->right = CreateNode(pnode, keywords);
                return;
            }
            pnode = pnode->right;
        }
    }
}


int main(int argc, char *argv[]) {
    FILE *fp;
    fp = fopen(argv[1], "rt");
    if (fp == NULL) {
        printf("The file does't exit.\n");
        exit(0);
    }
    ReadWords(fp);
    fclose(fp);
    return 0;
}
