#include <stdio.h>
#include <string.h>

struct IPSecConfig
{
    char sourceIP[20];
    char destinationIP[20];
    char encryptionKey[50];
    char authenticationKey[50];
    char payload[100];
};

void encryptData(char input[], char output[])
{
    int i;

    for(i = 0; input[i] != '\0'; i++)
    {
        output[i] = input[i] + 3;      // Caesar Cipher Simulation
    }

    output[i] = '\0';
}

int main()
{
    struct IPSecConfig config;

    char encryptedPayload[100];

    printf("===============================================\n");
    printf(" IPSec Manual Key Management Simulation\n");
    printf("===============================================\n");

    printf("Enter Source IP Address      : ");
    scanf("%19s", config.sourceIP);

    printf("Enter Destination IP Address : ");
    scanf("%19s", config.destinationIP);

    printf("Enter Encryption Key         : ");
    scanf("%49s", config.encryptionKey);

    printf("Enter Authentication Key     : ");
    scanf("%49s", config.authenticationKey);

    printf("Enter Payload                : ");
    scanf("%99s", config.payload);

    encryptData(config.payload, encryptedPayload);

    printf("\n===============================================\n");
    printf("Configured Security Parameters\n");
    printf("===============================================\n");

    printf("Source IP          : %s\n", config.sourceIP);
    printf("Destination IP     : %s\n", config.destinationIP);
    printf("Encryption Key     : %s\n", config.encryptionKey);
    printf("Authentication Key : %s\n", config.authenticationKey);

    printf("\n===============================================\n");
    printf("Secure Communication\n");
    printf("===============================================\n");

    printf("Original Payload   : %s\n", config.payload);
    printf("Encrypted Payload  : %s\n", encryptedPayload);

    printf("\nStatus             : Communication Successful\n");
    printf("Encryption         : Enabled\n");
    printf("Authentication     : Verified\n");

    return 0;
}
