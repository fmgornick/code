#include <stdio.h>

int conversion(int fahr);

int main()
{
    int i;

    for (i = 0; i <= 300; i += 20) 
        printf("\n%d°F = %.2f°C", i, conversion(i));

    return 0;
}

int conversion(int fahr)
{
    float celsius;
    celsius = (5.0/9.0) * (fahr - 32);

    return celsius;
}
