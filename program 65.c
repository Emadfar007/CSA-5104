#include <stdio.h>
#include <string.h>

struct PGPEmail
{
    char sender[50];
    char receiver[50];
    int publicKey;
    int privateKey;
    char message[100];
};

void encryptMessage(char input[], char output[], int key)
{
    int i;

    for(i = 0; input[i] != '\0'; i++)
    {
        output[i] = input[i] + key;
    }

    output[i] = '\0';
}

void decryptMessage(char input[], char output[], int key)
{
    int i;

    for(i = 0; input[i] != '\0'; i++)
    {
        output[i] = input[i] - key;
    }

    output[i] = '\0';
}

int main()
{
    struct PGPEmail email;

    char encryptedMessage[100];
    char decryptedMessage[100];

    printf("====================================================\n");
    printf("     PGP Email Encryption and Decryption\n");
    printf("====================================================\n");

    printf("Enter Sender Name        : ");
    scanf("%49s", email.sender);

    printf("Enter Receiver Name      : ");
    scanf("%49s", email.receiver);

    printf("Enter Public Key (1-10)  : ");
    scanf("%d", &email.publicKey);

    printf("Enter Private Key (Same) : ");
    scanf("%d", &email.privateKey);

    printf("Enter Email Message      : ");
    scanf("%99s", email.message);

    encryptMessage(email.message, encryptedMessage, email.publicKey);

    decryptMessage(encryptedMessage, decryptedMessage, email.privateKey);

    printf("\n====================================================\n");
    printf("Sender Information\n");
    printf("====================================================\n");

    printf("Sender            : %s\n", email.sender);
    printf("Receiver          : %s\n", email.receiver);
    printf("Original Message  : %s\n", email.message);

    printf("\n====================================================\n");
    printf("Encryption Process\n");
    printf("====================================================\n");

    printf("Public Key        : %d\n", email.publicKey);
    printf("Encrypted Message : %s\n", encryptedMessage);

    printf("\n====================================================\n");
    printf("Decryption Process\n");
    printf("====================================================\n");

    printf("Private Key       : %d\n", email.privateKey);
    printf("Decrypted Message : %s\n", decryptedMessage);

    if(strcmp(email.message, decryptedMessage) == 0)
    {
        printf("\nEmail Successfully Encrypted and Decrypted.\n");
        printf("Secure Communication Established.\n");
    }
    else
    {
        printf("\nDecryption Failed.\n");
    }

    return 0;
}
