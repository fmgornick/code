#include <stdio.h>

#define LOWER   0       // LOWER, UPPER, and STEP are symbolic constants,
#define UPPER   300     // not variables
#define STEP    20      

int main()
{
    float fahrenheit, celsius;    // declaring variables as ints

    fahrenheit = LOWER;
    while(fahrenheit <= UPPER) {                   // while loop for temp
        celsius = (5.0/9.0) * (fahrenheit - 32);     // incrementing
        printf("%3.0f %6.1f\n", fahrenheit, celsius);
        fahrenheit += STEP;
    }
    return 0;
}
