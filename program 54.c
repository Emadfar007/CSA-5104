#include <stdio.h>
#include <string.h>

struct Packet
{
    char sourceIP[20];
    char destinationIP[20];
    char payload[100];
};

void encrypt(char input[], char output[])
{
    int i;

    for(i = 0; input[i] != '\0'; i++)
    {
        output[i] = input[i] + 3;
    }

    output[i] = '\0';
}

void decrypt(char input[], char output[])
{
    int i;

    for(i = 0; input[i] != '\0'; i++)
    {
        output[i] = input[i] - 3;
    }

    output[i] = '\0';
}

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

int main()
{
    struct Packet packet;

    char encryptedData[100];
    char decryptedData[100];

    int spi;
    int seqNo;
    int icvOriginal;
    int icvReceived;

    printf("==============================================\n");
    printf("      AH + ESP IPSec Simulation\n");
    printf("==============================================\n");

    printf("Enter Source IP Address      : ");
    scanf("%19s", packet.sourceIP);

    printf("Enter Destination IP Address : ");
    scanf("%19s", packet.destinationIP);

    printf("Enter Payload                : ");
    scanf("%99s", packet.payload);

    printf("Enter SPI                    : ");
    scanf("%d", &spi);

    printf("Enter Sequence Number        : ");
    scanf("%d", &seqNo);

    icvOriginal = calculateICV(packet.payload);

    encrypt(packet.payload, encryptedData);

    printf("\n==============================================\n");
    printf("Original Packet\n");
    printf("==============================================\n");

    printf("Source IP      : %s\n", packet.sourceIP);
    printf("Destination IP : %s\n", packet.destinationIP);
    printf("Payload        : %s\n", packet.payload);

    printf("\n==============================================\n");
    printf("Packet After Applying AH + ESP\n");
    printf("==============================================\n");

    printf("SPI            : %d\n", spi);
    printf("Sequence No    : %d\n", seqNo);
    printf("ICV            : %d\n", icvOriginal);
    printf("Encrypted Data : %s\n", encryptedData);

    printf("\nSecure Packet:\n");
    printf("[AH | SPI=%d | SEQ=%d | ICV=%d | ESP | DATA=%s]\n",
           spi,
           seqNo,
           icvOriginal,
           encryptedData);

    decrypt(encryptedData, decryptedData);

    icvReceived = calculateICV(decryptedData);

    printf("\n==============================================\n");
    printf("Packet After Decryption\n");
    printf("==============================================\n");

    printf("Recovered Payload : %s\n", decryptedData);
    printf("Received ICV      : %d\n", icvReceived);

    if(icvOriginal == icvReceived)
    {
        printf("\nIntegrity         : VERIFIED\n");
        printf("Authentication    : SUCCESSFUL\n");
        printf("Confidentiality   : MAINTAINED\n");
    }
    else
    {
        printf("\nIntegrity Check Failed!\n");
    }

    return 0;
}
