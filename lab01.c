#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int l, int m, int r)
{
    int i = l, j = m + 1, k = 0, temp[r - l + 1];
    while (i <= m && j <= r) temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];
    for (i = l, k = 0; i <= r; i++) a[i] = temp[k++];
}

void mergeSort(int a[], int l, int r, int par)
{
    if (l >= r) return;
    int m = (l + r) / 2;
#pragma omp parallel sections if (par)
    {
#pragma omp section
        mergeSort(a, l, m, par);
#pragma omp section
        mergeSort(a, m + 1, r, par);
    }
    merge(a, l, m, r);
}

int main(void)
{
    omp_set_max_active_levels(4);
    const int n = 100000;
    int arr[2][n];
    for (int i = 0; i < n; i++) arr[1][i] = arr[0][i] = rand() % 1000;
    for (int p = 0; p < 2; p++)
    {
        double start = omp_get_wtime();
        mergeSort(arr[p], 0, n - 1, p);
        printf("%s %.6f s\n", p ? "Parallel:  " : "Sequential:", omp_get_wtime() - start);
    }
    return 0;
}