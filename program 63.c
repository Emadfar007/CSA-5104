#include <stdio.h>
#include <string.h>

struct EmailHeader
{
    char from[100];
    char returnPath[100];
    char replyTo[100];
};

int main()
{
    struct EmailHeader email;

    printf("=====================================================\n");
    printf("        Email Spoof Detection System\n");
    printf("=====================================================\n");

    printf("Enter From Address        : ");
    scanf("%99s", email.from);

    printf("Enter Return-Path Address : ");
    scanf("%99s", email.returnPath);

    printf("Enter Reply-To Address    : ");
    scanf("%99s", email.replyTo);

    printf("\n=====================================================\n");
    printf("Email Header Analysis\n");
    printf("=====================================================\n");

    printf("From Address        : %s\n", email.from);
    printf("Return-Path Address : %s\n", email.returnPath);
    printf("Reply-To Address    : %s\n", email.replyTo);

    printf("\n=====================================================\n");
    printf("Spoof Detection Result\n");
    printf("=====================================================\n");

    if(strcmp(email.from, email.returnPath) == 0 &&
       strcmp(email.from, email.replyTo) == 0)
    {
        printf("Status : Legitimate Email\n");
        printf("Reason : All email header addresses match.\n");
    }
    else
    {
        printf("Status : Spoofed Email Detected\n");

        if(strcmp(email.from, email.returnPath) != 0)
            printf("- From and Return-Path addresses do not match.\n");

        if(strcmp(email.from, email.replyTo) != 0)
            printf("- From and Reply-To addresses do not match.\n");
    }

    printf("\nAnalysis Completed Successfully.\n");

    return 0;
}
