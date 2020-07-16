#include <stdio.h>

int main()
{
    int c, comment = 0, num_f_slash = 0;
    FILE *program = fopen("comment_code.c", "r");

    while ((c = fgetc(program)) != EOF) 
    {

        if (comment == 0 && c == '/' && num_f_slash == 1) {
            num_f_slash = 0;
            comment = 1;
        }

        else if (comment == 0 && c == '/' && num_f_slash == 0) {
            ++num_f_slash;
        }

        else if (comment == 0 && c == '*' && num_f_slash == 1) {
            num_f_slash = 0;
            comment = 2;
        }

        else if (comment == 0 && c != '/' && num_f_slash == 1) {
            putchar('/');
            putchar(c);
        }

        else if (comment == 0 && c != '/') {
            putchar(c);
        }

        else if (comment == 1 && c == '\n') {
            comment = 0;
            num_f_slash = 0;
            putchar(c);
        }

        else if (comment == 2 && c == '\n') {
            putchar(c);
        }

        else if (comment == 2 && c == '*' && num_f_slash == 0) {
            ++num_f_slash;
        }

        else if (comment == 2 && c == '/' && num_f_slash == 1) {
            num_f_slash = 0;
            comment = 0;
        }
    }
    return 0;
}
