#include <stdio.h>

#define MAX_STUDENTS_NUMBER 1000

static unsigned int calculate(unsigned int n)
{
    unsigned int students[MAX_STUDENTS_NUMBER];

    unsigned int sum = 0;
    for (unsigned int i = 0; i < n; i++) {
        unsigned int dollars, cents;
        scanf("%u.%u", &dollars, &cents);
        students[i] = dollars * 100 + cents;
        sum += students[i];
    }
    unsigned int less = sum / n;
    unsigned int greater = less + (sum % n != 0);

    unsigned int s1 = 0, s2 = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (students[i] > greater) {
            s1 += students[i] - greater;
        }
        if (students[i] < less) {
            s2 += less - students[i];
        }
    }
    return s1 > s2 ? s1 : s2;
}

int main()
{
    unsigned int n;
    scanf("%u", &n);
    while (n != 0) {
        unsigned int res = calculate(n);
        printf("$%u.%02u\n", res / 100, res % 100);
        scanf("%u", &n);
    }
    return 0;
}
