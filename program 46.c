#include <stdio.h>
#include <string.h>

struct IPPacket
{
    char sourceIP[20];
    char destinationIP[20];
    char payload[100];
};

void displayPacket(struct IPPacket p)
{
    printf("\n=========================================\n");
    printf("           ORIGINAL IP PACKET\n");
    printf("=========================================\n");
    printf("Source IP      : %s\n", p.sourceIP);
    printf("Destination IP : %s\n", p.destinationIP);
    printf("Payload        : %s\n", p.payload);
}

void applyAH(struct IPPacket p)
{
    int icv = 0;
    int i;

    for(i = 0; p.payload[i] != '\0'; i++)
    {
        icv += p.payload[i];
    }

    printf("\n=========================================\n");
    printf(" Authentication Header (AH) Applied\n");
    printf("=========================================\n");
    printf("SPI             : 1001\n");
    printf("Sequence Number : 1\n");
    printf("Integrity Check Value (ICV): %d\n", icv);

    printf("\nSecured Packet:\n");
    printf("[AH | SPI=1001 | SEQ=1 | ICV=%d | DATA=%s]\n",
           icv, p.payload);
}

void applyESP(struct IPPacket p)
{
    char encrypted[100];
    int i;

    for(i = 0; p.payload[i] != '\0'; i++)
    {
        encrypted[i] = p.payload[i] + 3;
    }
    encrypted[i] = '\0';

    printf("\n=========================================\n");
    printf(" Encapsulating Security Payload (ESP)\n");
    printf("=========================================\n");
    printf("Encryption : Caesar Cipher Simulation\n");
    printf("Encrypted Payload : %s\n", encrypted);

    printf("\nSecured Packet:\n");
    printf("[ESP | DATA=%s]\n", encrypted);
}

void applyAHESP(struct IPPacket p)
{
    char encrypted[100];
    int icv = 0;
    int i;

    for(i = 0; p.payload[i] != '\0'; i++)
    {
        icv += p.payload[i];
        encrypted[i] = p.payload[i] + 3;
    }
    encrypted[i] = '\0';

    printf("\n=========================================\n");
    printf(" AH + ESP Applied\n");
    printf("=========================================\n");

    printf("SPI             : 1001\n");
    printf("Sequence Number : 1\n");
    printf("ICV             : %d\n", icv);
    printf("Encrypted Data  : %s\n", encrypted);

    printf("\nFinal Secure Packet:\n");
    printf("[AH | SPI=1001 | SEQ=1 | ICV=%d | ESP | DATA=%s]\n",
           icv, encrypted);
}

int main()
{
    struct IPPacket packet;
    int choice;

    printf("=========================================\n");
    printf("      IPSec Architecture Simulation\n");
    printf("=========================================\n");

    printf("Enter Source IP Address      : ");
    scanf("%19s", packet.sourceIP);

    printf("Enter Destination IP Address : ");
    scanf("%19s", packet.destinationIP);

    printf("Enter Payload                : ");
    scanf("%99s", packet.payload);

    printf("\nChoose IPSec Service\n");
    printf("1. Authentication Header (AH)\n");
    printf("2. Encapsulating Security Payload (ESP)\n");
    printf("3. AH + ESP\n");

    printf("Enter your choice : ");
    scanf("%d", &choice);

    displayPacket(packet);

    switch(choice)
    {
        case 1:
            applyAH(packet);
            break;

        case 2:
            applyESP(packet);
            break;

        case 3:
            applyAHESP(packet);
            break;

        default:
            printf("\nInvalid Choice!\n");
            return 0;
    }

    printf("\n=========================================\n");
    printf("Packet processed successfully using IPSec.\n");
    printf("=========================================\n");

    return 0;
}
