#include <stdio.h>

#define IN 1    //if getchar() is in a word
#define OUT 2   //if getchar() isn't in a word

int main()
{
    int input, state, nc, nw, nl;
    nc = nw = 0;
    nl = 1;

    for (input = getchar(); input != EOF; input = getchar()) {
        ++nc;

        if (input == '\n') ++nl;

        if (input == ' ' || input == '\t' || input == '\n') state = OUT;
        else if (state == OUT) { 
            state = IN; 
            ++nw;
        }
    }
    printf("\n\nCharacters: %d\nWords: %d\nLines: %d\n", nc, nw, nl);

    return 0;
}
