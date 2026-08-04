#include <stdio.h>
#include <string.h>

struct PGP
{
    char sender[50];
    char receiver[50];
    char message[100];
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

int generateSignature(char message[])
{
    int i;
    int signature = 0;

    for(i = 0; message[i] != '\0'; i++)
    {
        signature += message[i];
    }

    return signature;
}

int main()
{
    struct PGP pgp;

    char encryptedMessage[100];
    char decryptedMessage[100];

    int senderSignature;
    int receiverSignature;

    printf("=====================================================\n");
    printf("     Pretty Good Privacy (PGP) Simulation\n");
    printf("=====================================================\n");

    printf("Enter Sender Name   : ");
    scanf("%49s", pgp.sender);

    printf("Enter Receiver Name : ");
    scanf("%49s", pgp.receiver);

    printf("Enter Message       : ");
    scanf("%99s", pgp.message);

    senderSignature = generateSignature(pgp.message);

    encrypt(pgp.message, encryptedMessage);

    printf("\n=====================================================\n");
    printf("Sender Side\n");
    printf("=====================================================\n");

    printf("Sender            : %s\n", pgp.sender);
    printf("Receiver          : %s\n", pgp.receiver);
    printf("Original Message  : %s\n", pgp.message);
    printf("Digital Signature : %d\n", senderSignature);
    printf("Encrypted Message : %s\n", encryptedMessage);

    decrypt(encryptedMessage, decryptedMessage);

    receiverSignature = generateSignature(decryptedMessage);

    printf("\n=====================================================\n");
    printf("Receiver Side\n");
    printf("=====================================================\n");

    printf("Received Message  : %s\n", decryptedMessage);
    printf("Received Signature: %d\n", receiverSignature);

    if(senderSignature == receiverSignature)
    {
        printf("\nSignature Verification : SUCCESSFUL\n");
        printf("Authentication         : VERIFIED\n");
        printf("Integrity              : MAINTAINED\n");
        printf("Confidentiality        : ACHIEVED\n");
    }
    else
    {
        printf("\nSignature Verification : FAILED\n");
        printf("Message has been modified.\n");
    }

    return 0;
}
