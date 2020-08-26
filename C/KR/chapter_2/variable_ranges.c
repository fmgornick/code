#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    printf("range for signed char: %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("range for unsigned char: %d to %d\n\n", CHAR_MIN, UCHAR_MAX);

    printf("range for signed int: %d to %d\n", INT_MIN, INT_MAX);
    printf("range for unsigned int: %d to %u\n\n", INT_MIN, UINT_MAX);

    printf("range for signed short: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("range for unsigned short: %d to %d\n\n", SHRT_MIN, USHRT_MAX);

    printf("range for signed long: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("range for unsigned long: %ld to %lu\n\n", LONG_MIN, ULONG_MAX);
}
