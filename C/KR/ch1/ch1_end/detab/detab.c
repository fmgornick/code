#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8

int getlin(char line[], int limit);
void replace(char line[]);

int main()
{
    int i, c, position = 1, num_blanks = 0;

    while ((c = getchar()) != EOF) {

        if (c == '\t') {
            num_blanks = TABSTOP - ((position - 1) % TABSTOP);

            for (i = 0; i < num_blanks; ++i) {
                putchar('#');
            }

            position = 1;
            num_blanks = 0;
        }

        else if (c == '\n') {
            putchar(c);
            position = 1;
        }

        else {
            putchar(c);
            ++position;
        }
    }
    return 0;
}
