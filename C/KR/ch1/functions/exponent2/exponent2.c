#include <stdio.h>

int expn(int base, int power);

int main()
{
    int i;

    for (i = 1; i <= 10; ++i) {
        printf("\n2^%-2d = %4d", i, expn(2,i));
        // minus sign alligns text left, otherwise it's right alligned
    }
}

int expn(x, y)
{
    int p;

    // for loop doesn't actually alter y, but it alters a copy
    for (p = 1; y > 0; --y) {
        p *= x;
    }

    return p;
}
