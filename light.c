#include <math.h>
#include <stdio.h>

#define MAX_BULBS 4294967296

int main()
{
    for (;;) {
        unsigned int n, s;
        scanf("%u", &n);
        if (n == 0) {
            break;
        }
        s = sqrt(n);
        if (s * s == n) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    return 0;
}
