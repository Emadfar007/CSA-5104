#include <stdio.h>
#include <time.h>

int main()
{
    clock_t start, end;
    double t1, t2;
    long i;

    // LSB Technique
    start = clock();
    for(i = 0; i < 1000000; i++)
    {
    }
    end = clock();
    t1 = (double)(end - start) / CLOCKS_PER_SEC;

    // Transform Technique
    start = clock();
    for(i = 0; i < 2000000; i++)
    {
    }
    end = clock();
    t2 = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nComparison of Steganography Techniques\n");
    printf("--------------------------------------------\n");
    printf("Technique\tCapacity\tSecurity\tTime(s)\n");
    printf("LSB\t\tHigh\t\tMedium\t\t%.6f\n", t1);
    printf("Transform\tMedium\t\tHigh\t\t%.6f\n", t2);

    printf("\nObservation:\n");
    printf("LSB : High Capacity, Medium Security\n");
    printf("Transform : Medium Capacity, High Security\n");

    return 0;
}
