#include <stdio.h>

#define TABSTOP 8

int main()
{
    int i, c, position = 0;

    while ((c = getchar()) != EOF) {

        if (c == '\t') {

            while (position % TABSTOP != 0) {
                putchar(' ');
                ++position;
            }
        }

        else if (c == '\n') {
            putchar(c);
            position = 0;
        }

        else {
            putchar(c);
            ++position;
        }
    }
    return 0;
}
