#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8

int getlin(char line[], int limit);
void replace(char line[]);

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
