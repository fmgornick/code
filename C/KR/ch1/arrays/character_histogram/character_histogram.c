#include <stdio.h>

#define TOTAL_CHARS 128

int main()
{
    int i, j, c;
    int characters[TOTAL_CHARS];

    for (i = 0; i < TOTAL_CHARS; ++i) {
        characters[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        ++characters[c];
    }

    for (i = 0; i < TOTAL_CHARS; ++i) {
        if (characters[i] != 0) {
            putchar('\n');
            putchar(i);
            printf("| ");
        }
        for (j = 0; j < characters[i]; ++j) {
            putchar('*');
        }
    }
    return 0;
}
