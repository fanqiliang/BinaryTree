#include "WordCount.h"
#include <stdio.h>

void Print() {
    LNode *node = Head;
    int i = 0;
    while (node != NULL) {
        node = node->next;
    }
    node = Head;
    printf("The highest frequency of 10 words is:\n");
    while (node != NULL) {
        if (i <= 9) {
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
        node = node->next;
        if (node != NULL)
            i++;
    } 
    int t = 1; /*just for print 1,2,3,...,10*/
    for (int j = i; j >= 0; j--) {
        printf("The top %d is %s    %d\n", t++, stopten[j], itopten[j]);
    }
}
