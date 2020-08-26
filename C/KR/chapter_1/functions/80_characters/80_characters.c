#include <stdio.h>
#define MAXLINE 1000
#define threshold 80

int line_length(char line[], int maximum_length);

int main()
{
    int length;
    char line[MAXLINE];

    while ((length = line_length(line, MAXLINE)) > 0)
        if (length >= threshold)
            printf("\n%s", line);

    return 0;
}

int line_length(char s[], int limit)
{
    int i, c;

    for (i = 0; i < limit-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}
