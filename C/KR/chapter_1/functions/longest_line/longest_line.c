#include <stdio.h>
#define MAXLINE 1000

int getlin(char line[], int maximum_length);
void copy(char to[], char from[]);

int main()
{
    int len;                    // length of current line
    int max = 0;                // length of longest line (so far)
    char line[MAXLINE];         // current line
    char longest[MAXLINE];      // longest line (so far)

    while ((len = getlin(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    
    if (max > 0)
        printf("\n\nlongest line: %snumber of characters: %d", longest, max - 2);
    
    return 0;
}

int getlin(char s[], int limit)
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

void copy(char to[], char from[])
{
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i;
}
