#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    int i, j, c, letters, state;
    letters = 0;
    state = IN;

    int wordlength[11];
    for (i = 0; i <= 10; ++i) {
        wordlength[i] = 0;
    }

    while ((c = getchar()) != EOF) {

        if (c == ' ' || c == '\t' || c == '\n') {
            state = OUT;
            
            if (letters <= 10) ++wordlength[letters - 1];
            else ++wordlength[10];

            letters = 0;
            state = IN;
        }
        
        else {
            state = IN;
            ++letters;
        }
    }
    printf("\n\n\tword occurrences\n");

    for (i = 0; i <= 10; ++i) {

        if (i < 9) printf("%d  | ", i+1);
        else if (i == 9) printf("%d | ", i+1);
        else printf(">10|");

        for (j = 0; j < wordlength[i]; ++j) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
