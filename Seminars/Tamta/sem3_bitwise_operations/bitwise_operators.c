#include <stdio.h>
int main()
{
    // a = 5(00000101), b = 9(00001001)
    unsigned char a = 5, b = 9;

    printf("a = %d, b = %d\n", a, b);

    printf("a&b = %d\n", a & b);

    printf("a|b = %d\n", a | b);

    printf("a^b = %d\n", a ^ b);

    printf("~a = %d\n", a = ~a);

    printf("!a = %d\n", !a);

    printf("!0 = %d\n", !0);

    printf("b<<1 = %d\n", b << 1);

    printf("b>>1 = %d\n", b >> 1);

    // c = -5 (11111011)
    char c = -5;
    printf("c = %d\n", c);
    // c>>1 = -3 (11111101)
    printf("c>>1 = %d\n", c >> 1);
    // c<<1 = -10 (11110110)
    printf("c<<1 = %d\n", c << 1);

    return 0;
}