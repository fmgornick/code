#include <stdio.h>

int main()
{
    int fahr;
    
    printf("%3s %6s\n\n", "F", "C");

    for (fahr = 0; fahr <= 300; fahr += 20) {
        printf("%3d %6.2f\n", fahr, (5.0/9.0) * (fahr - 32));
    }
    return 0;
}
