#include "WordCount.h"

void BullbeSort(int Array[], int low, int high) {
    if (high == 0)
        return;
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


