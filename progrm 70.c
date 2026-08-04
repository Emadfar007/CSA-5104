#include <stdio.h>
#include <string.h>

struct Certificate
{
    char sender[50];
    char receiver[50];
    int certificateID;
    char certificateAuthority[50];
    char status[20];
};

int main()
{
    struct Certificate cert;

    printf("=====================================================\n");
    printf("      S/MIME Certificate Validation Module\n");
    printf("=====================================================\n");

    printf("Enter Sender Name              : ");
    scanf("%49s", cert.sender);

    printf("Enter Receiver Name            : ");
    scanf("%49s", cert.receiver);

    printf("Enter Certificate ID           : ");
    scanf("%d", &cert.certificateID);

    printf("Enter Certificate Authority    : ");
    scanf("%49s", cert.certificateAuthority);

    printf("Enter Certificate Status\n");
    printf("(VALID/EXPIRED): ");
    scanf("%19s", cert.status);

    printf("\n=====================================================\n");
    printf("Certificate Details\n");
    printf("=====================================================\n");

    printf("Sender                 : %s\n", cert.sender);
    printf("Receiver               : %s\n", cert.receiver);
    printf("Certificate ID         : %d\n", cert.certificateID);
    printf("Certificate Authority  : %s\n", cert.certificateAuthority);
    printf("Certificate Status     : %s\n", cert.status);

    printf("\n=====================================================\n");
    printf("Validation Result\n");
    printf("=====================================================\n");

    if(strcmp(cert.status, "VALID") == 0)
    {
        printf("Certificate Verification : SUCCESSFUL\n");
        printf("Authentication           : VERIFIED\n");
        printf("Secure Email             : ALLOWED\n");
    }
    else
    {
        printf("Certificate Verification : FAILED\n");
        printf("Reason                   : Certificate Expired\n");
        printf("Secure Email             : BLOCKED\n");
    }

    return 0;
}
