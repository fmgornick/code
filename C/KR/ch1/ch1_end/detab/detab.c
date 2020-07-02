#include <stdio.h>

#define MAXLINE 1000

int getlin(char line[], int limit);
void replace(char line[]);

int main()
{
    char line[MAXLINE];
    int length;

    while ((length = getlin(line, MAXLINE)) > 0)
        replace(line);
        printf("%s\n", line);

    return 0;
}

int getlin(char s[], int lim)
{
    int c, i;

    for (i = 0; i < (lim - 1) && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

void replace(char s[])
{
    int i, j = 0, k = 0;
    char s_new[MAXLINE];

    for (i = 0; s[i] != '\0'; ++i)
        if (s[i] != '\t') {
            s_new[j] = s[i];
            ++j;
        }

        else {
            while (k < 4)
                s_new[j] = ' ';
                ++j;
                ++k;
            k = 0;
        }
    
    s = s_new;
}
