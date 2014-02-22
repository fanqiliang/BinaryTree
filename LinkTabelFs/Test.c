#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int num = 0;

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
    char ReadInfo[50];
    int  i = 0;
    int  j;
    FILE * fp = OpenTxt();
    char Comp[4] = {"fjkl"};
    ch = fgetc(fp);
    while (ch != EOF) {
        if (ch == ' ' || ch == '\n' 
            || ch == '\t' || ch == ',' || ch == '.') {
            num++;
        //    for (j = 0; j < i; j++) {
          //      printf("%c", ReadInfo[i]);
           // }
           // printf("\n");
            ReadInfo[i] = '\0';
            printf("%s\n", ReadInfo);
           if(strcmp(Comp, ReadInfo) == 0) {
                printf("right\n");
           } else {
               printf("wrong\n");
           }
            
            memset(ReadInfo, ' ', sizeof(ReadInfo));
            i = 0;
        } else {
            ReadInfo[i] = ch;
            i++;
        }
        ch = fgetc(fp);
    }
    printf("num = %d\n", num);
    fclose(fp);
}

int main() {
    GetInfo();
}
