#include "BinaryTree.h"
#include <stdlib.h>
#include <string.h>


FILE * OpenTxt() {

    FILE *fp;

    fp = fopen("/Users/fanqiliang/sandbox/fan.txt", "rt");
    if (fp == NULL) {
        printf("FAILED!!!\n");
        exit(0);
    }
    return fp;
}
void GetInfo() {

    char ch;
    char ReadInfo[20];
    char Temp[20];
    int  i = 0;
    int  j = 0;
    FILE * fp = OpenTxt();
    Linktable * Head = NULL;
    Linktable * pNode = NULL;
    Linktable * qNode = NULL;
    ch = fgetc(fp);
    while (ch != EOF) {
        while (ch == '\t' || ch == ' ' || ch == ',' 
                || ch == '.' || ch == '\n' || ch == '\r') {
            ch = fgetc(fp);
        }
        ReadInfo[i] = ch;
        i++;
        ch = fgetc(fp);
        if (ch == ' ' || ch == '\n' 
            || ch == '\t' || ch == ',' || ch == '.' || ch == '\r') {
            ReadInfo[i] = '\0';
            if (Head == NULL) {
                Head = (Linktable *)malloc(sizeof(struct Linktable));
                Head->Num = 0;
                strcpy(Head->data, ReadInfo);
                (Head->Num)++;
                i = 0;
                memset(ReadInfo, ' ', sizeof(ReadInfo));
            } else {
                pNode = Head;
                while(pNode != NULL) {
                    if (strcasecmp(pNode->data, ReadInfo) == 0) {
                        (pNode->Num)++;
                        ch = fgetc(fp);
                        i = 0;
                        memset(ReadInfo, ' ', sizeof(ReadInfo));
                        break;
                    }
                    else {
                        if (pNode->next == NULL) {
                            qNode = (Linktable *)malloc(sizeof(struct Linktable));
                            pNode->next = qNode;
                            pNode = pNode->next;
                            strcpy(pNode->data, ReadInfo);
                            (pNode->Num)++;
                            i = 0;
                            memset(ReadInfo, ' ', sizeof(ReadInfo));
                            ch = fgetc(fp);
                            break;
                        } else {
                            pNode = pNode->next;
                        }
                    }
                }
            }
        }
    }
    qNode = Head;
    while(qNode != NULL) {
        printf("%s ", qNode->data);
        printf("%d\n", qNode->Num);
        qNode = qNode->next;
    }
    printf("\n");
    fclose(fp);
}
    int main() {
        GetInfo(); 
    } 
