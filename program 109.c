#include <stdio.h>
#include <string.h>

int main()
{
    char sourceIP[20];
    char signature[30];
    int port;

    int attack = 0;

    printf("========================================\n");
    printf("       INTRUSION PREVENTION SYSTEM\n");
    printf("========================================\n");

    printf("\nEnter source IP: ");
    scanf("%19s", sourceIP);

    printf("Enter destination port: ");
    scanf("%d", &port);

    printf("Enter packet signature: ");
    scanf("%29s", signature);

    printf("\n========================================\n");
    printf("           PACKET INSPECTION\n");
    printf("========================================\n");

    printf("\nSource IP       : %s", sourceIP);
    printf("\nDestination Port: %d", port);
    printf("\nSignature       : %s", signature);

    /* Attack signature rules */

    if (strcmp(signature, "MALWARE") == 0 ||
        strcmp(signature, "PORTSCAN") == 0 ||
        strcmp(signature, "ATTACK") == 0)
    {
        attack = 1;
    }

    /* Suspicious ports */

    if (port == 23 || port == 21)
    {
        attack = 1;
    }

    /* Block suspicious IP */

    if (strcmp(sourceIP, "192.168.1.100") == 0)
    {
        attack = 1;
    }

    printf("\n\n========================================\n");

    if (attack)
    {
        printf("ATTACK DETECTED!\n");
        printf("Packet ACTION: BLOCKED\n");
        printf("IPS prevented the suspicious packet.\n");
    }
    else
    {
        printf("No attack detected.\n");
        printf("Packet ACTION: ALLOWED\n");
    }

    printf("========================================\n");

    return 0;
}
