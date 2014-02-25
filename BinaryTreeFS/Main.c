#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct LNode *CreateLNode(char *word) {
    struct LNode *node = (LNode *)malloc(sizeof(struct LNode));
    node->next = NULL;
    node->key = 1;
    strcpy(node->keywords, word);
    return node;
}

void ReadWordInfo(char *word) {
    struct LNode *node = NULL;
    if (Head == NULL) {
        Head = (LNode *)malloc(sizeof(struct LNode));
        strcpy(Head->keywords, word);
        Head->key = 1;
        Head->next = NULL;
        return;
    }
    node = Head;
    while (node != NULL) {
        if (strcmp(node->keywords, word) == 0) {
            node->key++;
            return;
        }
        else {
            if (node->next == NULL) {
                node->next = CreateLNode(word);
                return;
            } else 
                node = node->next;
        }
    }
}

void ReadWords(FILE *fp) {
    char word[MAX];
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
            i = 0;
            ch = fgetc(fp);
            ReadWordInfo(word);
        }
    }
    return;
}

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

Node * CreateRoot(Node *node, int key, char *keywords) {
    struct Node *pnode = (struct Node *)malloc(sizeof(struct Node));
    pnode->color = BLACK;
    pnode->key = key;
    pnode->state = UNREAD;
    strcpy(pnode->keywords, keywords);
    pnode->left = NullNode;
    pnode->right = NullNode;
    pnode->parent = NULL;
    return pnode;
}

Node * CreateNode(Node *pnode, int key, char keywords[]) {
    struct Node *node = (Node *)malloc(sizeof(struct Node));
    node->color = RED;
    node->key = key;
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

void DeleteFixUp(Node *node) {
    struct Node * wNode = NULL;
    while (node != Root && node->color == BLACK) {
        if (node->parent->left == node) {
            wNode = node->parent->right;
            if (wNode->color == RED) {
                wNode->color = BLACK;
                node->parent->color = RED;
                LeftRotate(node->parent);
                wNode = node->parent->right;
            }
            if (wNode->left->color == BLACK && 
                    wNode->right->color == BLACK) {
                wNode->color = RED;
                node = node->parent;
            } else if (wNode->right->color == BLACK) {
                wNode->left->color = BLACK;
                wNode->color = RED;
                RightRotate(wNode);
                wNode = node->parent->right;
            }
            wNode->color = node->parent->color;
            node->parent->color = BLACK;
            wNode->right->color = BLACK;
            LeftRotate(node->parent);
            Root = node;
        } else {
            wNode = node->parent->left;
            if (wNode->color == RED) {
                wNode->color = BLACK;
                node->parent->color = RED;
                RightRotate(node->parent);
                wNode = node->parent->left;
            }
            if (wNode->right->color == BLACK && 
                    wNode->left->color == BLACK) {
                wNode->color = RED;
                node = node->parent;
            } else if (wNode->left->color == BLACK) {
                wNode->right->color = BLACK;
                wNode->color = RED;
                LeftRotate(wNode);
                wNode = node->parent->left;
            }
            wNode->color = node->parent->color;
            node->parent->color = BLACK;
            wNode->left->color = BLACK;
            RightRotate(node->parent);
            Root = node;
        }
    }
    node->color = BLACK;
}

void DeleteNode(Node *node) {
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
        DeleteFixUp(pNode);
}

void TreeInsert(int key, char * keywords) {
    if (Root == NULL) {
        Root = CreateRoot(Root, key, keywords);
        return;
    }
    struct Node *node = NullNode;
    struct Node *pnode = NULL;
    node = Root;
    int flag = 1;
    while (node != NullNode) {
        if (node->key >= key) {
            pnode = node;
            node = node->left;
            flag = 1;
        }
        else {
            pnode = node;
            node = node->right;
            flag = 0;
        }
    }
    node = CreateNode(pnode, key, keywords);
    if (flag == 1)
        node->parent->left = node;
    else
        node->parent->right = node;
    InsertFixUp(node);
}

void CreateTree() {
    struct LNode *node = NULL;
    NullNode = NULLNODE();
    node = Head;
    while (node != NULL) {
        TreeInsert(node->key, node->keywords);
        node = node->next;
    }
}

Node * TravNode(Node *node) {
    if (node->left != NullNode) {
        node = node->left;
        while (node != NullNode) {
            if (node->right != NullNode)
                node = node->right;
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

void Print() {
    struct Node *node = NULL;
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
    printf("The highest frequency of 10 words and the number of them appear:\n");
    int i = 1;
    while (i <= 10) {
        printf("The top %d is %s    %d\n", i, node->keywords, node->key);
        node->state = READ;
        node = TravNode(node);
        if (node == NULL || node == NullNode) {
            printf("There are not 10 words.\n");
            break;
        }
        i++;
    }
}


int main(int argc, char *argv[]) {
    FILE *fp;
    fp = fopen(argv[1], "rt");
    if (fp == NULL) {
        printf("The file does't exit.\n");
        exit(0);
    }
    Head = NULL;
    Root = NULL;
    ReadWords(fp);
   // struct LNode *node = NULL;
   // node = Head;
   // while (node != NULL) {
   //     printf("keywords is \"%s\" and key = %d\n", node->keywords, node->key);
   //     node = node->next;
   // }
    CreateTree();
    Print();
    fclose(fp);
    return 0;
}
