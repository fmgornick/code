#include <stdio.h>

#define MAXLINE 1024
#define BORDER 80

#define TAB '\t'
#define TABSTOP 8

#define SPACE ' '
#define NEW '\n'

int main()
{
    int c, i = 0, j, position = 0;
    char word[MAXLINE];

    while ((c = getchar()) != EOF) {
        
        if (c != SPACE && c != TAB && c != NEW && position < BORDER) {
            word[i] = c;
            ++i;
            ++position;
        }

        else if (c == SPACE && position < BORDER) {

            if (i > 0) {
                for (j = 0; j <= i; ++j) {
                    putchar(word[j]);
                    word[j] = '\0';
                }
                i = 0;
            }

            if (++position == BORDER) {
                printf("\n");
                position = 0;
            }

            else {
            putchar(c);
            ++position;
            }
        }

        else if (c == TAB && position < BORDER) {
            
            if (position + (TABSTOP - (position % TABSTOP)) >= BORDER) {

                for (j = 0; j <= i; ++j) {
                    putchar(word[j]);
                    word[j] = '\0';
                }
                printf("\n");
                position = 0;
                i = 0;
            }

            else {

                for (j = 0; j <= i; ++j) {
                    putchar(word[j]);
                    word[j] = '\0';
                }

                putchar(c);
                position += TABSTOP - (position % TABSTOP);
                i = 0;
            }
        }

        else {

            if (i > 0) {
                printf("\n");

                for (j = 0; j <= i; ++j) {
                    putchar(word[j]);
                    word[j] = '\0';
                }
                putchar(c);

                position = i + 2;
                i = 0;
            }
        }
    }
    printf("\n");
    return 0;
}

