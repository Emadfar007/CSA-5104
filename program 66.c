#include <stdio.h>
#include <string.h>

struct PGP
{
    char sender[50];
    char receiver[50];
    char message[100];
};

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
    struct PGP email;

    int senderSignature;
    int receiverSignature;

    printf("=====================================================\n");
    printf("     PGP Digital Signature Verification\n");
    printf("=====================================================\n");

    printf("Enter Sender Name   : ");
    scanf("%49s", email.sender);

    printf("Enter Receiver Name : ");
    scanf("%49s", email.receiver);

    printf("Enter Message       : ");
    scanf("%99s", email.message);

    senderSignature = generateSignature(email.message);

    printf("\n=====================================================\n");
    printf("Sender Side\n");
    printf("=====================================================\n");

    printf("Sender             : %s\n", email.sender);
    printf("Receiver           : %s\n", email.receiver);
    printf("Message            : %s\n", email.message);
    printf("Generated Signature: %d\n", senderSignature);

    printf("\nMessage and Signature Sent Successfully...\n");

    receiverSignature = generateSignature(email.message);

    printf("\n=====================================================\n");
    printf("Receiver Side\n");
    printf("=====================================================\n");

    printf("Received Message   : %s\n", email.message);
    printf("Received Signature : %d\n", senderSignature);
    printf("Calculated Signature: %d\n", receiverSignature);

    printf("\n=====================================================\n");
    printf("Verification Result\n");
    printf("=====================================================\n");

    if(senderSignature == receiverSignature)
    {
        printf("Digital Signature Verified Successfully.\n");
        printf("Message Integrity      : Maintained\n");
        printf("Sender Authentication  : Successful\n");
    }
    else
    {
        printf("Digital Signature Verification Failed.\n");
        printf("Message Integrity      : Compromised\n");
    }

    return 0;
}
