#include <stdio.h>

// CTRL + D to signal EOF

int main()
{
    int num_lines = 0;
    int input;
    
    while ((input = getchar()) != EOF) {
        if (getchar() == '\n') ++num_lines;
    }   

    printf("\nLines: %d", num_lines);
    return 0; 
}
