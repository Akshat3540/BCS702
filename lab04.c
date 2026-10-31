#include <stdio.h>
#include <omp.h>

int is_prime(int num)
{
    for (int i = 2; i * i <= num; i++) if (num % i == 0) return 0;
    return num > 1;
}

int main(void)
{
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("\nPrime numbers from 1 to %d:\n", n);
    for (int i = 1; i <= n; i++) if (is_prime(i)) printf("%d ", i);
    printf("\n");
    for (int p = 0; p < 2; p++)
    {
        double t = omp_get_wtime();
#pragma omp parallel for if (p)
        for (int i = 1; i <= n; i++) is_prime(i);
        printf("%s Time: %f seconds\n", p ? "Parallel" : "Serial", omp_get_wtime() - t);
    }
    return 0;
}