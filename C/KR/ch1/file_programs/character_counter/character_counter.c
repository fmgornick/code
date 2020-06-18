#include <stdio.h>

int main()
{
    int chars = 0;
    int input;

    while ((input = getchar()) != EOF) {
        ++chars;
    }

    printf("\nCharacters: %d", chars);
    return 0;
}
