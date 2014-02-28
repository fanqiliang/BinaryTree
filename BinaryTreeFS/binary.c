#include "binary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ReadWords(FILE *fp) {
    char word[MAX];
    char ch;
    int i = 0;

    ch = fgetc(fp);
    while(ch != EOF) {
        while (!(isalpha(ch))) {
            if (ch == EOF)
                return;
            ch = fgetc(fp);
        }
        if (ch == EOF)
            return;
        word[i] = ch;
        i++;
        ch = fgetc(fp);
        if (!(isalpha(ch))) {
            word[i] = '\0';
            i = 0;
            ch = fgetc(fp);
            TreeInsert(word);
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

Node * CreateRoot(Node *node, char *keywords) {
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

/*Read words according to its key order*/
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

//Bullbe sort
void BullbeSort(int Array[], int low, int high) {
    for (int i = low; i <= high; i++) {
        for (int j = high; j > i; j--) {
            if (Array[j-1] > Array[j]) {
                int temp = Array[j-1];
                char *tempp = stopten[j-1];
                Array[j-1] = Array[j];
                stopten[j-1] = stopten[j];
                Array[j] = temp;
                stopten[j] = tempp;
            }
        }
    }
    return;
}


/*print the top 10 words*/
void Print() {
    struct Node *node = NULL;
    struct Node *rnode = NULL;
    if (Root == NULL)
        printf("The file is null.");
    else {
        node = Root;
    }
    while (node != NullNode) {
        if (node->left != NullNode)
            node = node->left;
        else
            break;
    }
    rnode = node;
    node = Root;
    while (node != NullNode) {
        if (node->right != NullNode)
            node = node->right;
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


int main(int argc, char *argv[]) {
    FILE *fp;
    fp = fopen(argv[1], "rt");
    if (fp == NULL) {
        printf("The file does't exit.\n");
        exit(0);
    }
    Root = NULL;
    NullNode = NULLNODE();
    ReadWords(fp);
    Print();
    fclose(fp);
    return 0;
}
