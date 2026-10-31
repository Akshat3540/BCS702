#include <stdio.h>
#include <omp.h>

int fib(int n)
{
    if (n < 2) return n;
    int x, y;
#pragma omp task shared(x)
    x = fib(n - 1);
    y = fib(n - 2);
#pragma omp taskwait
    return x + y;
}

int main(void)
{
    int n;
    printf("Enter number of Fibonacci terms: ");
    scanf("%d", &n);
    printf("Fibonacci Series:\n");
#pragma omp parallel
#pragma omp single
    for (int i = 0; i < n; i++) printf("%d ", fib(i));
    printf("\n");
    return 0;
}