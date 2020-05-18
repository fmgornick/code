#include <stdio.h>

int main()
{
    int fahrenheit, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahrenheit = lower;
    while(fahrenheit <= upper) {
        celsius = (5 * (fahrenheit - 32)) / 9; 
        printf("%d\t%d\n", fahrenheit, celsius);
        fahrenheit = fahrenheit +  step;
    }
    return 0;
}
