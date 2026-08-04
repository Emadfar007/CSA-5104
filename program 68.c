#include <stdio.h>
#include <string.h>

struct SMIME
{
    char sender[50];
    char receiver[50];
    char message[100];
    int publicCertificate;
    int privateCertificate;
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
    int signature = 0;

    for(i = 0; message[i] != '\0'; i++)
    {
        signature += message[i];
    }

    return signature;
}

int main()
{
    struct SMIME email;

    char encryptedMessage[100];
    char decryptedMessage[100];

    int senderSignature;
    int receiverSignature;

    printf("=====================================================\n");
    printf(" S/MIME Email Encryption and Signature Verification\n");
    printf("=====================================================\n");

    printf("Enter Sender Name            : ");
    scanf("%49s", email.sender);

    printf("Enter Receiver Name          : ");
    scanf("%49s", email.receiver);

    printf("Enter Email Message          : ");
    scanf("%99s", email.message);

    printf("Enter Public Certificate Key : ");
    scanf("%d", &email.publicCertificate);

    printf("Enter Private Certificate Key: ");
    scanf("%d", &email.privateCertificate);

    senderSignature = generateSignature(email.message);

    encrypt(email.message,
            encryptedMessage,
            email.publicCertificate);

    printf("\n=====================================================\n");
    printf("Sender Side\n");
    printf("=====================================================\n");

    printf("Sender             : %s\n", email.sender);
    printf("Receiver           : %s\n", email.receiver);
    printf("Original Message   : %s\n", email.message);
    printf("Digital Signature  : %d\n", senderSignature);
    printf("Encrypted Message  : %s\n", encryptedMessage);

    printf("\nEncrypted Email Sent Successfully...\n");

    decrypt(encryptedMessage,
            decryptedMessage,
            email.privateCertificate);

    receiverSignature = generateSignature(decryptedMessage);

    printf("\n=====================================================\n");
    printf("Receiver Side\n");
    printf("=====================================================\n");

    printf("Received Message   : %s\n", decryptedMessage);
    printf("Received Signature : %d\n", receiverSignature);

    printf("\n=====================================================\n");
    printf("Verification Result\n");
    printf("=====================================================\n");

    if(senderSignature == receiverSignature)
    {
        printf("Digital Signature Verified Successfully.\n");
        printf("Authentication : Successful\n");
        printf("Integrity      : Maintained\n");
        printf("Confidentiality: Achieved\n");
    }
    else
    {
        printf("Signature Verification Failed.\n");
        printf("Email Integrity Compromised.\n");
    }

    return 0;
}
