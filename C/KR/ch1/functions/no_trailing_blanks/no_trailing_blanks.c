#include <stdio.h>
#define MAXLINE 1000

int mod_line(char current_line[], int max_length);

int main()
{
    char line[MAXLINE];
    char length;

    while((length = mod_line(line, MAXLINE)) > 0)
        printf("%s\n", line);
}

int mod_line(char s[], int max_length)
{
    int i, c;
    int num_char = 0;

    for (i = 0; i < max_length - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        if ((c != ' ' && c != '\t') || num_char > 0) {
            s[i] = c;
            ++num_char;
        }

    if (num_char == 0)
        s[0] = '\0';

    else s[i] = '\0';

    return num_char;
}
