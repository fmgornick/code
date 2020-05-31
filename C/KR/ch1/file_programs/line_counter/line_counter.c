#include <stdio.h>

int main()
{
    int nl;
    nl = 0;

    while(getchar() != EOF)
        if (getchar() == '\n')
            ++nl;

    printf("%d\n", nl);
    return 0; 
}
