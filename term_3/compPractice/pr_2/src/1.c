#include <stdio.h>

int main() {
    int N, fact = 1, factVal = 1;

    printf("Enter N > 0: ");
    scanf("%d", &N);

    while (factVal < N) {
        factVal *= fact++;
    }
    fact--;
	
    printf("\nNearest factorial %d! = %d\n", fact, factVal);

    if (factVal == N)
        printf("\nN is factorial of %d\n", fact);
    else
        printf("\nN is not factorial of any number.\n");

    return 0;
}
