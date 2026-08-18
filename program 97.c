#include <stdio.h>
#include <string.h>

struct Certificate
{
    char subject[100];
    char issuer[100];
    char publicKey[100];
    char validFrom[20];
    char validTo[20];
    char signature[100];
};

int main()
{
    struct Certificate cert;

    printf("========================================\n");
    printf("       SELF-SIGNED X.509 CERTIFICATE\n");
    printf("========================================\n");

    printf("\nEnter Subject: ");
    fgets(cert.subject, sizeof(cert.subject), stdin);
    cert.subject[strcspn(cert.subject, "\n")] = '\0';

    /* Self-signed certificate */
    strcpy(cert.issuer, cert.subject);

    strcpy(cert.publicKey,
           "RSA Public Key: 2048-bit");

    strcpy(cert.validFrom, "01-01-2026");
    strcpy(cert.validTo, "01-01-2027");

    strcpy(cert.signature,
           "Self-Signed Digital Signature");

    printf("\n========================================\n");
    printf("        CERTIFICATE DETAILS\n");
    printf("========================================\n");

    printf("\nSubject     : %s", cert.subject);
    printf("\nIssuer      : %s", cert.issuer);
    printf("\nPublic Key  : %s", cert.publicKey);
    printf("\nValid From  : %s", cert.validFrom);
    printf("\nValid To    : %s", cert.validTo);
    printf("\nSignature   : %s", cert.signature);

    printf("\n\n========================================\n");

    if (strcmp(cert.subject, cert.issuer) == 0)
    {
        printf("Certificate Type : SELF-SIGNED\n");
        printf("Certificate Status: VALID\n");
    }
    else
    {
        printf("Certificate Status: INVALID\n");
    }

    printf("========================================\n");

    return 0;
}
