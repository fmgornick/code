#include <stdio.h>

int conversion(int temp, char type);

int main()
{
    printf("\n%d°C = %.2f°F", 20, conversion(20, 'c'));

}

int conversion(int temp, char type)
{
    int celsius, fahrenheit;

    if (type == 'f') {
        celsius = (5.0/9.0) * (temp - 32);
        return celsius;
    }

    else if (type == 'c') {
        fahrenheit = (9.0/5.0) * temp + 32;
        return fahrenheit;
    }
    
    else return "either c or f";
}
