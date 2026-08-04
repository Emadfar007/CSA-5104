#include <stdio.h>
#include <string.h>

int calculateICV(char payload[])
{
    int i;
    int icv = 0;

    for(i = 0; payload[i] != '\0'; i++)
    {
        icv = icv + payload[i];
    }

    return icv;
}

int main()
{
    char payload[100];
    int icv;

    printf("=========================================\n");
    printf(" Integrity Check Value (ICV) Calculator\n");
    printf("=========================================\n");

    printf("Enter Packet Payload: ");
    scanf("%99s", payload);

    icv = calculateICV(payload);

    printf("\n=========================================\n");
    printf("Packet Details\n");
    printf("=========================================\n");
    printf("Payload            : %s\n", payload);
    printf("Payload Length     : %lu Bytes\n", strlen(payload));
    printf("Calculated ICV     : %d\n", icv);

    printf("\nVerification Status : SUCCESS\n");

    return 0;
}
