#include "WordCount.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    if (argv[1] == NULL || argv[2] == NULL) {
        printf("please input: ./a.out filename RB or\n");
        printf("              ./a.out filename LN\n");
        exit(1);
    }
    fp = fopen(argv[1], "rt");
    if (fp == NULL) {
        printf("The file does't exit.\n");
        exit(0);
    }
    Head = NULL;
    Root = NULL;
    NullNode = NULLNODE();
    ReadWords(fp, argv[2]);
    if (strcmp(argv[2], "RB") == 0)
        getRBInfo();
    else
        Print();
    fclose(fp);
    return 0;
}
