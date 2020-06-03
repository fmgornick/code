#include <stdio.h>

int main()
{
    FILE *fr;
    fr = fopen("text.txt", "r");

    int nc;
    nc = 0;
    
    char ch;

    for (ch = getc(fr); ch != EOF; ch = getc(fr))
        ++nc;

    fclose(fr);

    printf("%d\n", nc);
    return 0;
}
