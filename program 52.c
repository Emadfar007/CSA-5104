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
        output[i] = input[i] + 3;      // Caesar Cipher
    }

    output[i] = '\0';
}

void transportMode(struct Packet packet)
{
    char encrypted[100];

    encrypt(packet.payload, encrypted);

    printf("\n=========================================\n");
    printf("          IPSec TRANSPORT MODE\n");
    printf("=========================================\n");

    printf("Source IP      : %s\n", packet.sourceIP);
    printf("Destination IP : %s\n", packet.destinationIP);
    printf("Encrypted Data : %s\n", encrypted);

    printf("\nPacket Structure:\n");
    printf("[IP HEADER][ESP][Encrypted Payload]\n");
}

void tunnelMode(struct Packet packet)
{
    char encrypted[150];

    char fullPacket[200];

    sprintf(fullPacket,
            "%s|%s|%s",
            packet.sourceIP,
            packet.destinationIP,
            packet.payload);

    encrypt(fullPacket, encrypted);

    printf("\n=========================================\n");
    printf("            IPSec TUNNEL MODE\n");
    printf("=========================================\n");

    printf("Outer Source IP      : 172.16.1.1\n");
    printf("Outer Destination IP : 172.16.1.2\n");

    printf("\nEncrypted Original Packet:\n");
    printf("%s\n", encrypted);

    printf("\nPacket Structure:\n");
    printf("[NEW IP HEADER][ESP][Encrypted Original IP Packet]\n");
}

int main()
{
    struct Packet packet;
    int choice;

    printf("=========================================\n");
    printf(" IPSec Transport Mode and Tunnel Mode\n");
    printf("=========================================\n");

    printf("Enter Source IP Address      : ");
    scanf("%19s", packet.sourceIP);

    printf("Enter Destination IP Address : ");
    scanf("%19s", packet.destinationIP);

    printf("Enter Payload                : ");
    scanf("%99s", packet.payload);

    printf("\nChoose IPSec Mode\n");
    printf("1. Transport Mode\n");
    printf("2. Tunnel Mode\n");

    printf("Enter Choice : ");
    scanf("%d", &choice);

    printf("\n=========================================\n");
    printf("Original Packet\n");
    printf("=========================================\n");

    printf("Source IP      : %s\n", packet.sourceIP);
    printf("Destination IP : %s\n", packet.destinationIP);
    printf("Payload        : %s\n", packet.payload);

    switch(choice)
    {
        case 1:
            transportMode(packet);
            break;

        case 2:
            tunnelMode(packet);
            break;

        default:
            printf("\nInvalid Choice!\n");
    }

    return 0;
}
