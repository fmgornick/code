#include <stdio.h>
#define MAXLINE 1000

int getlin(char line[], int maximum_length);
void reverse(char line[]);

int main()
{
    char line[MAXLINE];
    int length;

    while ((length = getlin(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s\n", line);
    }

    return 0;
}

int getlin(char s[], int limit)
{
    int i, c;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

void reverse(char s[])
{
    int i, j, swap;
    j = 0;

    for (i = 0; s[i] != '\0'; ++i);
    i--;

    if (s[i] == '\n') --i;

    while (j < i) {
        swap = s[j];
        s[j] = s[i];
        s[i] = swap;

        --i;
        ++j;
    }
}
