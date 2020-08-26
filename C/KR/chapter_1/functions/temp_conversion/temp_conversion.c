#include <stdio.h>

float conversion(int fahr);

int main()
{
    int i;

    for (i = 0; i <= 300; i += 20) 
        printf("\n%3d°F = %6.2f°C", i, conversion(i));

    return 0;
}

float conversion(int fahr)
{
    return (5.0/9.0) * (fahr - 32);
}
