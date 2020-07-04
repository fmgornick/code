#include <stdio.h>

#define TAB '\t'
#define SPACE '#'
#define TABSTOP 8
#define MAXLINE 1024

int main()
{
    int c, position = 0, num_blanks = 0, tab_length = 0; 

    while ((c = getchar()) != EOF) {

        if (c != ' ' && c != TAB && c != '\n' && num_blanks == 0) {
            putchar(c);
            ++position;
        }

        else if (c == '\n' && num_blanks == 0) {
            putchar(c);
            position = 0;
        }

        else if (c == ' ') {
            ++num_blanks;
            ++position;
        }

        else if (c == TAB) {

            if (position % TABSTOP == 0) {
                num_blanks += TABSTOP;
                position += TABSTOP;
            }

            else {
                num_blanks += TABSTOP - (position % TABSTOP);
                position += TABSTOP - (position % TABSTOP);
            }
        }

        else {
            position -= num_blanks;

            if (position % TABSTOP == 0) tab_length = TABSTOP;
            else tab_length = TABSTOP - (position % TABSTOP);

            while (num_blanks >= tab_length) {
                putchar(TAB);
                num_blanks -= tab_length;
                position += tab_length;

                tab_length = TABSTOP;
            }

            while (num_blanks > 0) {
                putchar(SPACE);
                --num_blanks;
                ++position;
            }

            if (c == '\n') {
                putchar(c);
                position = 0;
            }

            else {
                putchar(c);
                ++position;
            }
        }
    }

    return 0;
}
