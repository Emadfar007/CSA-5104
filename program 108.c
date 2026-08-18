#include <stdio.h>
#include <string.h>

int main()
{
    char sourceIP[20];
    char packetType[30];
    int port;

    int alert = 0;

    printf("========================================\n");
    printf("     NETWORK INTRUSION DETECTION SYSTEM\n");
    printf("========================================\n");

    printf("\nEnter source IP: ");
    scanf("%19s", sourceIP);

    printf("Enter destination port: ");
    scanf("%d", &port);

    printf("Enter packet type/signature: ");
    scanf("%29s", packetType);

    printf("\n========================================\n");
    printf("           PACKET ANALYSIS\n");
    printf("========================================\n");

    printf("\nSource IP      : %s", sourceIP);
    printf("\nDestination Port: %d", port);
    printf("\nPacket Type    : %s", packetType);

    /* Rule 1: Blocked IP */
    if (strcmp(sourceIP, "192.168.1.100") == 0)
    {
        printf("\n\nALERT: Suspicious source IP detected.");
        alert = 1;
    }

    /* Rule 2: Suspicious ports */
    if (port == 23 || port == 21)
    {
        printf("\nALERT: Suspicious destination port detected.");
        alert = 1;
    }

    /* Rule 3: Attack signatures */
    if (strcmp(packetType, "PORTSCAN") == 0 ||
        strcmp(packetType, "MALWARE") == 0 ||
        strcmp(packetType, "ATTACK") == 0)
    {
        printf("\nALERT: Attack signature detected.");
        alert = 1;
    }

    printf("\n\n========================================\n");

    if (alert)
    {
        printf("INTRUSION DETECTED!\n");
        printf("Security alert generated.\n");
    }
    else
    {
        printf("No intrusion detected.\n");
        printf("Packet classified as NORMAL.\n");
    }

    printf("========================================\n");

    return 0;
}
