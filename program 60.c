#include <stdio.h>
#include <string.h>
#include <time.h>

#define AH_OVERHEAD 24
#define ESP_OVERHEAD 32

int calculateICV(char data[])
{
    int i;
    int icv = 0;

    for(i = 0; data[i] != '\0'; i++)
    {
        icv += data[i];
    }

    return icv;
}

void encrypt(char input[], char output[])
{
    int i;

    for(i = 0; input[i] != '\0'; i++)
    {
        output[i] = input[i] + 3;
    }

    output[i] = '\0';
}

int main()
{
    char payload[100];
    char encrypted[100];

    int icv;
    int payloadSize;

    clock_t startAH, endAH;
    clock_t startESP, endESP;

    double ahTime;
    double espTime;

    printf("=================================================\n");
    printf(" AH vs ESP Performance Comparison\n");
    printf("=================================================\n");

    printf("Enter Packet Payload: ");
    scanf("%99s", payload);

    payloadSize = strlen(payload);

    /* AH Processing */

    startAH = clock();

    icv = calculateICV(payload);

    endAH = clock();

    ahTime = ((double)(endAH - startAH)) / CLOCKS_PER_SEC;

    /* ESP Processing */

    startESP = clock();

    encrypt(payload, encrypted);

    endESP = clock();

    espTime = ((double)(endESP - startESP)) / CLOCKS_PER_SEC;

    printf("\n=================================================\n");
    printf("Authentication Header (AH)\n");
    printf("=================================================\n");

    printf("Calculated ICV     : %d\n", icv);
    printf("Processing Time    : %.6f seconds\n", ahTime);
    printf("Packet Overhead    : %d Bytes\n", AH_OVERHEAD);
    printf("Final Packet Size  : %d Bytes\n",
           payloadSize + AH_OVERHEAD);

    printf("\n=================================================\n");
    printf("Encapsulating Security Payload (ESP)\n");
    printf("=================================================\n");

    printf("Encrypted Payload  : %s\n", encrypted);
    printf("Processing Time    : %.6f seconds\n", espTime);
    printf("Packet Overhead    : %d Bytes\n", ESP_OVERHEAD);
    printf("Final Packet Size  : %d Bytes\n",
           payloadSize + ESP_OVERHEAD);

    printf("\n=================================================\n");
    printf("Comparison Summary\n");
    printf("=================================================\n");

    printf("Payload Size           : %d Bytes\n", payloadSize);
    printf("AH Overhead            : %d Bytes\n", AH_OVERHEAD);
    printf("ESP Overhead           : %d Bytes\n", ESP_OVERHEAD);

    if(AH_OVERHEAD < ESP_OVERHEAD)
        printf("Packet Overhead Result : AH has lower overhead than ESP.\n");
    else
        printf("Packet Overhead Result : ESP has lower overhead than AH.\n");

    if(ahTime < espTime)
        printf("Processing Result      : AH processed faster than ESP.\n");
    else if(espTime < ahTime)
        printf("Processing Result      : ESP processed faster than AH.\n");
    else
        printf("Processing Result      : Both required approximately the same time.\n");

    return 0;
}
