#include <stdio.h>
#include <omp.h>

int main(void)
{
    int n, end[100];
    printf("Enter number of iterations: ");
    scanf("%d", &n);
#pragma omp parallel for schedule(static, 2)
    for (int i = 0; i < n; i++) end[omp_get_thread_num()] = i;
    for (int t = 0; t < omp_get_max_threads() && 2 * t < n; t++)
        printf("Thread %d : Iterations %d -- %d\n", t, 2 * t, end[t]);
    return 0;
}