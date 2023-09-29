#include <stdio.h>
#include "omp.h"

int calculateEvenSum(int n)
{
    int sum=0, fibo[2*n + 1];
    fibo[0]=0, fibo[1]=1;

    for(int i=2; i <= 2*n; i++)
    {
        fibo[i] = fibo[i-1] + fibo[i-2];
    }

    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i <= 2*n; i+=2)
    {
        sum+=fibo[i];
    }

    return sum;
}

int main()
{
    int n = 15;

    double start_time = omp_get_wtime();
    int sum = calculateEvenSum(n);
    double end_time = omp_get_wtime();


    
    printf("La suma de los %d índices pares (contando desde 0) es de %d\n", n, sum);
    printf("El tiempo de ejecución es de %f segundos\n", end_time - start_time);

    return 0;
}
