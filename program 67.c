#include <stdio.h>
#include <string.h>

struct Email
{
    char sender[50];
    char receiver[50];
    char message[100];
    int key;
};

void encrypt(char input[], char output[], int key)
{
    int i;

    for(i = 0; input[i] != '\0'; i++)
    {
        output[i] = input[i] + key;
    }

    output[i] = '\0';
}

void decrypt(char input[], char output[], int key)
{
    int i;

    for(i = 0; input[i] != '\0'; i++)
    {
        output[i] = input[i] - key;
    }

    output[i] = '\0';
}

int generateSignature(char message[])
{
    int i;
    int sum = 0;

    for(i = 0; message[i] != '\0'; i++)
    {
        sum += message[i];
    }

    return sum;
}

int main()
{
    struct Email email;

    char encryptedMessage[100];
    char decryptedMessage[100];

    int senderSignature;
    int receiverSignature;

    printf("=====================================================\n");
    printf("      Secure Email Transmission using PGP\n");
    printf("=====================================================\n");

    printf("Enter Sender Name       : ");
    scanf("%49s", email.sender);

    printf("Enter Receiver Name     : ");
    scanf("%49s", email.receiver);

    printf("Enter Email Message     : ");
    scanf("%99s", email.message);

    printf("Enter Encryption Key    : ");
    scanf("%d", &email.key);

    senderSignature = generateSignature(email.message);

    encrypt(email.message, encryptedMessage, email.key);

    printf("\n=====================================================\n");
    printf("Sender Side\n");
    printf("=====================================================\n");

    printf("Sender              : %s\n", email.sender);
    printf("Receiver            : %s\n", email.receiver);
    printf("Original Message    : %s\n", email.message);
    printf("Digital Signature   : %d\n", senderSignature);
    printf("Encrypted Message   : %s\n", encryptedMessage);

    printf("\nSecure Email Sent Successfully...\n");

    decrypt(encryptedMessage, decryptedMessage, email.key);

    receiverSignature = generateSignature(decryptedMessage);

    printf("\n=====================================================\n");
    printf("Receiver Side\n");
    printf("=====================================================\n");

    printf("Received Message    : %s\n", decryptedMessage);
    printf("Calculated Signature: %d\n", receiverSignature);

    printf("\n=====================================================\n");
    printf("Verification Result\n");
    printf("=====================================================\n");

    if(senderSignature == receiverSignature)
    {
        printf("Digital Signature Verified.\n");
        printf("Message Integrity      : Maintained\n");
        printf("Authentication         : Successful\n");
        printf("Email Status           : Securely Delivered\n");
    }
    else
    {
        printf("Signature Verification Failed.\n");
        printf("Email Status           : Message Tampered\n");
    }

    return 0;
}
