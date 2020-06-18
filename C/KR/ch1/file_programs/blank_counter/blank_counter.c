#include <stdio.h>

int main()
{
    int blanks = 0, tabs = 0, newlines = 0;
    int input;
    
    while ((input = getchar()) != EOF) {
        if (input == ' ') ++blanks;
        if (input == '\t') ++tabs;
        if (input == '\n') ++newlines;
    }

    printf("\nBlanks: %d\nTabs: %d\nNewlines: %d", blanks, tabs, newlines);
    return 0;
}

