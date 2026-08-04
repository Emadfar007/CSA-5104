#include <stdio.h>
#include <string.h>

#define AH_HEADER_SIZE 24

struct Packet
{
    char sourceIP[20];
    char destinationIP[20];
    char payload[100];
};

int calculateICV(char payload[])
{
    int i;
    int icv = 0;

    for(i = 0; payload[i] != '\0'; i++)
    {
        icv += payload[i];
    }

    return icv;
}

int main()
{
    struct Packet packet;

    int payloadSize;
    int packetWithoutAH;
    int packetWithAH;
    int icv;

    printf("==============================================\n");
    printf(" Packet Transmission Comparison (AH vs No AH)\n");
    printf("==============================================\n");

    printf("Enter Source IP Address      : ");
    scanf("%19s", packet.sourceIP);

    printf("Enter Destination IP Address : ");
    scanf("%19s", packet.destinationIP);

    printf("Enter Payload                : ");
    scanf("%99s", packet.payload);

    payloadSize = strlen(packet.payload);

    packetWithoutAH = payloadSize;
    packetWithAH = payloadSize + AH_HEADER_SIZE;

    icv = calculateICV(packet.payload);

    printf("\n==============================================\n");
    printf("Transmission WITHOUT AH\n");
    printf("==============================================\n");

    printf("Source IP      : %s\n", packet.sourceIP);
    printf("Destination IP : %s\n", packet.destinationIP);
    printf("Payload        : %s\n", packet.payload);
    printf("Packet Size    : %d Bytes\n", packetWithoutAH);
    printf("Integrity      : Not Protected\n");
    printf("Authentication : Not Available\n");

    printf("\n==============================================\n");
    printf("Transmission WITH AH\n");
    printf("==============================================\n");

    printf("Source IP      : %s\n", packet.sourceIP);
    printf("Destination IP : %s\n", packet.destinationIP);
    printf("SPI            : 1001\n");
    printf("Sequence No    : 1\n");
    printf("ICV            : %d\n", icv);
    printf("Payload        : %s\n", packet.payload);
    printf("Packet Size    : %d Bytes\n", packetWithAH);
    printf("Integrity      : Protected\n");
    printf("Authentication : Verified\n");

    printf("\n==============================================\n");
    printf("Comparison\n");
    printf("==============================================\n");

    printf("Without AH Packet Size : %d Bytes\n", packetWithoutAH);
    printf("With AH Packet Size    : %d Bytes\n", packetWithAH);
    printf("Packet Overhead        : %d Bytes\n",
           packetWithAH - packetWithoutAH);

    if(packetWithAH > packetWithoutAH)
        printf("Result                 : AH increases packet size due to security header.\n");

    return 0;
}
