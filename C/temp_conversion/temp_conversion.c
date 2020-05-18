#include <stdio.h>

int main()
{
    float fahrenheit, celsius;    // declaring variables as ints
    int lower, upper, step;

    lower = 0;  // assigning integer values to variables
    upper = 300;
    step = 20;

    fahrenheit = lower;
    while(fahrenheit <= upper) {                   // while loop for temp
        celsius = (5.0/9.0) * (fahrenheit - 32);     // incrementing
        printf("%3.0f %6.1f\n", fahrenheit, celsius);
        fahrenheit += step;
    }
    return 0;
}
