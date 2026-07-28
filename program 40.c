#include <stdio.h>
#include <time.h>

int main()
{
    clock_t start, end;
    double timeTaken;
    char *modes[] = {"ECB", "CBC", "CFB", "OFB", "CTR"};
    int i;

    printf("---------------------------------------------------------------\n");
    printf("Mode\tEncryption Time(ms)\tSecurity\tError Propagation\n");
    printf("---------------------------------------------------------------\n");

    for(i = 0; i < 5; i++)
    {
        start = clock();

        /* Simulated encryption workload */
        volatile long j;
        for(j = 0; j < 1000000; j++);

        end = clock();

        timeTaken = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;

        printf("%s\t%.2f\t\t", modes[i], timeTaken);

        if(i == 0)
            printf("Low\t\tOne Block\n");
        else if(i == 1)
            printf("High\t\tCurrent & Next Block\n");
        else if(i == 2)
            printf("High\t\tOne Byte\n");
        else if(i == 3)
            printf("Medium\t\tOne Bit\n");
        else
            printf("Very High\tNo Propagation\n");
    }

    printf("---------------------------------------------------------------\n");

    return 0;
}
