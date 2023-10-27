#include <stdio.h>
int main() {
    int a, b, sum = 0;
    printf("Enter left border  A >= 0: ");
    scanf("%d", &a);
    printf("\n%d ", a);
    printf("Enter right border B >= 0: ");
    scanf("%d", &b);
    if (a % 4)
        a += 4 - a % 4;
    for (; a <= b; a += 4) {
        sum += a;
    }
    printf("\nSum: %d\n", sum);
    return 0;
}
