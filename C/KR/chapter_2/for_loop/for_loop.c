#include <stdio.h>

#define lim 1000

// for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)
//     s[i] = c 

int main()
{
    char s[lim];
    int i, c;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            break;
        }

        else if (i >= lim-1) {
            break;
        }

        else {
            s[i] = c;
            ++i;
        }
    }

    printf("%s", s);

    return 0;
}
