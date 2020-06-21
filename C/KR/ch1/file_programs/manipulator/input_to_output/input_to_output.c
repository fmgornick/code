#include <stdio.h>

int main()
{
    int input;

    for (input = getchar(); input != EOF; input = getchar()) {
        if (input == '\t') printf("\\t");
        if (input == '\b') printf("\\b");
        if (input == '\\') printf("\\\\");

        else putchar(input);
    }
    return 0;
}
