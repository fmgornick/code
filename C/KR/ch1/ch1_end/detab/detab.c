#include <stdio.h>

#define MAXLINE 1000
#define TABLENGTH 4

int getlin(char line[], int limit);
void replace(char line[]);

int main()
{
    char line[MAXLINE];
    int length;

    while ((length = getlin(line, MAXLINE)) > 0) {
        replace(line);
        printf("%s\n", line);
    }

    return 0;
}

int getlin(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
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
    int i, j = 0, k, l = 0;
    char s_new[MAXLINE];

    for (i = 0; s[i] != '\0'; ++i) {
        if (s[i] != '\t') {
            s_new[j] = s[i];
            ++j;
        }
    }

        else {
            for (k = 0; k < TABLENGTH; ++k) {
                s_new[j] = ' ';
                ++j;
            }
        }

    if (s[i] == '\n') {
        s_new[j] = s[i];
        ++j;
    }
    
    s_new[j] = '\0';

    while ((s[l] = s_new[l]) != '\0')
        ++l;
}
