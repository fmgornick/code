#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    int input, state;

    while ((input = getchar()) != EOF) {
        if (input == ' ' || input == '\t' || input == '\n') 
            state = OUT;

        else putchar(input);

        if (state == OUT) {
            printf("\n");
            state = IN;
        }
    }
    return 0;
}
