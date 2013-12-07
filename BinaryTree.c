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
    int  temp[10];
    int  Storage[1000][2];
    int  i = 0;
    int  j = 0;
    int  t = 0;
    int  s = 0;

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
                Head->key = 0;
                strcpy(Head->data, ReadInfo);
                (Head->Num)++;
                Head->key = ++t;
                printf("%d  \n", Head->key);
                Storage[t][0] = Head->Num;
                Storage[t][1] = Head->key;
                t++;
                i = 0;
                memset(ReadInfo, ' ', sizeof(ReadInfo));
            } else {
                pNode = Head;
                s = 1;
                while(pNode != NULL) {
                    if (strcasecmp(pNode->data, ReadInfo) == 0) {
                        (pNode->Num)++;
                        Storage[s][0] = pNode->Num;
                        ch = fgetc(fp);
                        i = 0;
                        memset(ReadInfo, ' ', sizeof(ReadInfo));
                        break;
                    } else {
                        if (pNode->next == NULL) {
                            qNode = (Linktable *)malloc(sizeof(struct Linktable));
                            pNode->next = qNode;
                            pNode = pNode->next;
                            strcpy(pNode->data, ReadInfo);
                            (pNode->Num)++;
                            pNode->key = t;
                            Storage[t][0] = pNode->Num;
                            Storage[t][1] = pNode->key;
                            i = 0;
                            memset(ReadInfo, ' ', sizeof(ReadInfo));
                            ch = fgetc(fp);
                            t++;
                            break;
                        } else {
                            pNode = pNode->next;
                            s++;
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
    QuickSort(Storage, 0, t-2);
    printf("The top 10 words is following!!!!!!\n");
    for(j = t-2; j > t-12; j--) {
        pNode = Head;
        while (pNode != NULL) {
            if (pNode->key == Storage[j][1]) {
                printf("%s ", pNode->data);
                printf("%d ", pNode->Num);
                printf("\n");
                break;
            }
            pNode = pNode->next;
        }
    }
    fclose(fp);
}

int Partition(int list[][2], int low, int high) {
    int k = list[low][0];
    int temp = list[low][1];

    while(low < high) {
        while (low < high && list[high][0] >= k)
            high--;
        list[low][0] = list[high][0];
        list[low][1] = list[high][1];
        while (low < high && list[low][0] <= k)
            low++;
        list[high][0] = list[low][0];
        list[high][1] = list[low][1];
    }

    list[low][0] = k;
    list[low][1] = temp;
    return low;
}

void QuickSort(int list[][2], int low, int high) {
    int key;
    int i;

    if (low < high) {
        key = Partition(list, low, high);
        QuickSort(list, low, key-1);
        QuickSort(list, key+1, high);
    }
}

int main() {
    GetInfo(); 
} 
