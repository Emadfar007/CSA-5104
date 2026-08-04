#include <stdio.h>
#include <string.h>

struct Packet
{
    char sourceIP[20];
    char destinationIP[20];
    int protocol;
    char payload[100];
};

int main()
{
    struct Packet packet;

    printf("==============================================\n");
    printf("      IPSec Packet Analyzer Simulation\n");
    printf("==============================================\n");

    printf("Enter Source IP Address      : ");
    scanf("%19s", packet.sourceIP);

    printf("Enter Destination IP Address : ");
    scanf("%19s", packet.destinationIP);

    printf("Enter Protocol Number\n");
    printf("(50 = ESP, 51 = AH, 100 = AH + ESP): ");
    scanf("%d", &packet.protocol);

    printf("Enter Payload : ");
    scanf("%99s", packet.payload);

    printf("\n==============================================\n");
    printf("Captured Packet Details\n");
    printf("==============================================\n");

    printf("Source IP      : %s\n", packet.sourceIP);
    printf("Destination IP : %s\n", packet.destinationIP);
    printf("Protocol No.   : %d\n", packet.protocol);
    printf("Payload        : %s\n", packet.payload);

    printf("\n==============================================\n");
    printf("Packet Analysis Result\n");
    printf("==============================================\n");

    switch(packet.protocol)
    {
        case 50:
            printf("Protocol Identified : ESP\n");
            printf("Confidentiality     : Enabled\n");
            printf("Payload             : Encrypted\n");
            break;

        case 51:
            printf("Protocol Identified : AH\n");
            printf("Integrity           : Enabled\n");
            printf("Authentication      : Enabled\n");
            break;

        case 100:
            printf("Protocol Identified : AH + ESP\n");
            printf("Confidentiality     : Enabled\n");
            printf("Integrity           : Enabled\n");
            printf("Authentication      : Enabled\n");
            break;

        default:
            printf("Protocol Identified : Normal IP Packet\n");
            printf("No IPSec Header Found.\n");
    }

    printf("\nAnalysis Completed Successfully.\n");

    return 0;
}
