#include <stdio.h>

int main()
{
    int fahrenheit, celsius;    // declaring variables as ints
    int lower, upper, step;

    lower = 0;  // assigning integer values to variables
    upper = 300;
    step = 20;

    fahrenheit = lower;
    while(fahrenheit <= upper) {                   // while loop for temp
        celsius = (5 * (fahrenheit - 32)) / 9;     // incrementing
        printf("%d\t%d\n", fahrenheit, celsius);
        fahrenheit += step;
    }
    return 0;
}
