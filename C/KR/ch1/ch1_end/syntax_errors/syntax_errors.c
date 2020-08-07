#include <stdio.h>

void in_comment();
void in_quote(int current_character);

int main()
{
    int c;
    int parentheses = 0, braces = 0, brackets = 0;

    while ((c = getchar()) != EOF) {
        
        if (c == '/' && (c = getchar()) == '*') {
            in_comment(c);
        }        

        else if (c == '\'' || c == '\"') {
            in_quote(c);
        }

        else {

            if (c == '(') ++parentheses;
            else if (c == '{') ++braces;
            else if (c == '[') ++brackets;

            else if (c == ')') --parentheses;
            else if (c == '}') --braces;
            else if (c == ']') --brackets;
        }

    if (parentheses != 0) {
        printf("unmatched parentheses\n");
    }

    if (braces != 0) {
        printf("unmatched braces\n");
    }

    if (brackets != 0) {
        printf("unmatched brackets\n");
    }

    return 0;
    }
}

void in_comment()
{
    int d, e;

    d = getchar();
    e = getchar();
    
    while (d != '*' || e != '/') {
        d = e;
        e = getchar(); 
    }
}

void in_quote(int c)
{
    int d = getchar();

    while (d != c) {
        d = getchar();
    }
}
