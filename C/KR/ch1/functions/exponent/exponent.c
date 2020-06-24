#include <stdio.h>

int power(int x, int y);

int main()
{
    int i;

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(-3,i), power(2,i));
    
    return 0;
} 

int power(int base, int n)
{
    int i, p;
    p = 1;

    if (n == 0) return 1;

    else if (n > 0) {
        for (i = 1; i <= n; ++i)
            p *= base;
        return p;
    }

    else {
        for (i = 1; i <= (0 - n); ++i)
            p *= base;
        return 1/p;
    }

}
