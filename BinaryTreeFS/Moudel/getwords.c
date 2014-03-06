#include "WordCount.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void ReadWords(FILE *fp, char *type) {
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
            if (strcmp(type, "RB") == 0)
                TreeInsert(word);
            else
                CreateLinkTabel(word);
        }
    }
    return;
}

