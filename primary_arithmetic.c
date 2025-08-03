#include <stdio.h>

static unsigned int carries(unsigned int a, unsigned int b)
{
    unsigned int carry = 0, count = 0;
    do {
        carry = (a % 10 + b % 10 + carry) / 10;
        if (carry) {
            count++;
        }
        a /= 10;
        b /= 10;
    } while (a > 0 || b > 0);
    return count;
}

int main()
{
    for (;;) {
        unsigned int a, b, count;
        scanf("%u %u", &a, &b);
        if (a == 0 && b == 0) {
            break;
        }
        count = carries(a, b);
        switch (count) {
        case 0:
            printf("No carry operation.\n");
            break;
        case 1:
            printf("1 carry operation.\n");
            break;
        default:
            printf("%u carry operations.\n", count);
        }
    }
    return 0;
}
