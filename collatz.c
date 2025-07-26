#include <stdio.h>

static unsigned int collatz(unsigned int n)
{
    unsigned int res = 1;
    while (n != 1) {
        if (n % 2 != 0) {
            n = 3 * n + 1;
        } else {
            n /= 2;
        }
        res++;
    }
    return res;
}

static unsigned int collatz_max(unsigned int i, unsigned int j)
{
    unsigned int max = 1;
    for (; i <= j; i++) {
        unsigned int c = collatz(i);
        if (max < c) {
            max = c;
        }
    }
    return max;
}

int main()
{
    int n, i, j;
    while ((n = scanf("%d %d", &i, &j)) != EOF) {
        int min = i < j ? i : j;
        int max = i > j ? i : j;
        printf("%d %d %d\n", i, j, collatz_max(min, max));
    }
    return 0;
}
