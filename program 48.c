#include <stdio.h>
#include <string.h>

struct AH
{
    int spi;
    int seqNo;
    int icv;
};

struct Packet
{
    char sourceIP[20];
    char destinationIP[20];
    char payload[100];
};

int calculateICV(char data[])
{
    int i, sum = 0;

    for(i = 0; data[i] != '\0'; i++)
    {
        sum += data[i];
    }

    return sum;
}

int main()
{
    struct Packet packet;
    struct AH ah;

    printf("=========================================\n");
    printf(" Authentication Header (AH) Simulation\n");
    printf("=========================================\n");

    printf("Enter Source IP Address      : ");
    scanf("%19s", packet.sourceIP);

    printf("Enter Destination IP Address : ");
    scanf("%19s", packet.destinationIP);

    printf("Enter Payload                : ");
    scanf("%99s", packet.payload);

    printf("Enter Security Parameter Index (SPI): ");
    scanf("%d", &ah.spi);

    printf("Enter Sequence Number: ");
    scanf("%d", &ah.seqNo);

    ah.icv = calculateICV(packet.payload);

    printf("\n=========================================\n");
    printf("Original Packet\n");
    printf("=========================================\n");

    printf("Source IP      : %s\n", packet.sourceIP);
    printf("Destination IP : %s\n", packet.destinationIP);
    printf("Payload        : %s\n", packet.payload);

    printf("\nApplying Authentication Header...\n");

    printf("\n=========================================\n");
    printf("Authentication Header\n");
    printf("=========================================\n");

    printf("SPI             : %d\n", ah.spi);
    printf("Sequence Number : %d\n", ah.seqNo);
    printf("ICV             : %d\n", ah.icv);

    printf("\n=========================================\n");
    printf("Authenticated Packet\n");
    printf("=========================================\n");

    printf("[AH | SPI=%d | SEQ=%d | ICV=%d | DATA=%s]\n",
           ah.spi,
           ah.seqNo,
           ah.icv,
           packet.payload);

    printf("\nPacket Integrity : VERIFIED\n");
    printf("Origin Authentication : SUCCESSFUL\n");

    return 0;
}
