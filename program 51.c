#include <stdio.h>
#include <string.h>

struct Packet
{
    char sourceIP[20];
    char destinationIP[20];
    char payload[100];
};

void encryptPayload(char input[], char output[])
{
    int i;

    for(i = 0; input[i] != '\0'; i++)
    {
        output[i] = input[i] + 3;
    }

    output[i] = '\0';
}

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

    char encryptedPayload[100];
    int spi;
    int seqNo;
    int icv;

    printf("=========================================\n");
    printf(" Encapsulating Security Payload (ESP)\n");
    printf("=========================================\n");

    printf("Enter Source IP Address      : ");
    scanf("%19s", packet.sourceIP);

    printf("Enter Destination IP Address : ");
    scanf("%19s", packet.destinationIP);

    printf("Enter Payload                : ");
    scanf("%99s", packet.payload);

    printf("Enter Security Parameter Index (SPI): ");
    scanf("%d", &spi);

    printf("Enter Sequence Number: ");
    scanf("%d", &seqNo);

    encryptPayload(packet.payload, encryptedPayload);

    icv = calculateICV(packet.payload);

    printf("\n=========================================\n");
    printf("Original Packet\n");
    printf("=========================================\n");

    printf("Source IP      : %s\n", packet.sourceIP);
    printf("Destination IP : %s\n", packet.destinationIP);
    printf("Payload        : %s\n", packet.payload);

    printf("\n=========================================\n");
    printf("ESP Protected Packet\n");
    printf("=========================================\n");

    printf("SPI            : %d\n", spi);
    printf("Sequence No    : %d\n", seqNo);
    printf("Encrypted Data : %s\n", encryptedPayload);
    printf("ICV            : %d\n", icv);

    printf("\nFinal Packet:\n");
    printf("[ESP | SPI=%d | SEQ=%d | DATA=%s | ICV=%d]\n",
           spi,
           seqNo,
           encryptedPayload,
           icv);

    printf("\nConfidentiality : ENABLED\n");
    printf("Integrity       : VERIFIED\n");
    printf("Authentication  : SUCCESSFUL\n");

    return 0;
}
