#include <stdio.h>
#include <string.h>

struct Connection
{
    char srcIP[20];
    char destIP[20];
    int srcPort;
    int destPort;
};

int main()
{
    struct Connection table[10];

    int count = 0;
    int i;
    int found = 0;

    char srcIP[20];
    char destIP[20];
    int srcPort;
    int destPort;

    char type[20];

    printf("========================================\n");
    printf("       STATEFUL FIREWALL SIMULATION\n");
    printf("========================================\n");

    printf("\nEnter packet type (NEW/ESTABLISHED): ");
    scanf("%19s", type);

    printf("Enter source IP: ");
    scanf("%19s", srcIP);

    printf("Enter destination IP: ");
    scanf("%19s", destIP);

    printf("Enter source port: ");
    scanf("%d", &srcPort);

    printf("Enter destination port: ");
    scanf("%d", &destPort);

    /*
       If NEW packet, create a connection.
    */
    if (strcmp(type, "NEW") == 0)
    {
        strcpy(table[count].srcIP, srcIP);
        strcpy(table[count].destIP, destIP);

        table[count].srcPort = srcPort;
        table[count].destPort = destPort;

        count++;

        printf("\nNEW connection detected.");
        printf("\nConnection added to state table.");

        printf("\n\nDecision: ALLOWED\n");
    }

    /*
       If ESTABLISHED packet, check state table.
    */
    else if (strcmp(type, "ESTABLISHED") == 0)
    {
        /*
           Demonstration connection.
        */
        strcpy(table[0].srcIP, "192.168.1.10");
        strcpy(table[0].destIP, "192.168.1.20");

        table[0].srcPort = 5000;
        table[0].destPort = 80;

        count = 1;

        for (i = 0; i < count; i++)
        {
            if (strcmp(srcIP, table[i].srcIP) == 0 &&
                strcmp(destIP, table[i].destIP) == 0 &&
                srcPort == table[i].srcPort &&
                destPort == table[i].destPort)
            {
                found = 1;
                break;
            }
        }

        if (found)
            printf("\nConnection found in state table.");
        else
            printf("\nConnection NOT found in state table.");

        if (found)
            printf("\nDecision: ALLOWED\n");
        else
            printf("\nDecision: BLOCKED\n");
    }

    else
    {
        printf("\nInvalid packet type.\n");
    }

    printf("\n========================================\n");

    return 0;
}
