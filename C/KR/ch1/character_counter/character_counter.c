#include <stdio.h>

int main()
{
    int nc;

    for(nc = 0; getchar() != EOF; ++nc)
        ;

    printf("%1d\n", nc);
    return 0;
}
