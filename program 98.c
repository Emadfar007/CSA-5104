#include <stdio.h>
#include <string.h>

struct Certificate
{
    char subject[50];
    char issuer[50];
    char validFrom[20];
    char validTo[20];
    char publicKey[100];
};

int main()
{
    struct Certificate cert;
    char trustedIssuer[50];

    int issuerOK = 0;
    int validityOK = 0;
    int keyOK = 0;

    printf("========================================\n");
    printf("       X.509 CERTIFICATE VERIFICATION\n");
    printf("========================================\n");

    printf("\nEnter Subject: ");
    fgets(cert.subject, sizeof(cert.subject), stdin);
    cert.subject[strcspn(cert.subject, "\n")] = '\0';

    printf("Enter Issuer: ");
    fgets(cert.issuer, sizeof(cert.issuer), stdin);
    cert.issuer[strcspn(cert.issuer, "\n")] = '\0';

    printf("Enter Trusted Issuer: ");
    fgets(trustedIssuer, sizeof(trustedIssuer), stdin);
    trustedIssuer[strcspn(trustedIssuer, "\n")] = '\0';

    printf("Enter Valid From: ");
    fgets(cert.validFrom, sizeof(cert.validFrom), stdin);
    cert.validFrom[strcspn(cert.validFrom, "\n")] = '\0';

    printf("Enter Valid To: ");
    fgets(cert.validTo, sizeof(cert.validTo), stdin);
    cert.validTo[strcspn(cert.validTo, "\n")] = '\0';

    printf("Enter Public Key: ");
    fgets(cert.publicKey, sizeof(cert.publicKey), stdin);
    cert.publicKey[strcspn(cert.publicKey, "\n")] = '\0';

    /* Check issuer */
    if (strcmp(cert.issuer, trustedIssuer) == 0)
        issuerOK = 1;

    /* Simple validity check */
    if (strlen(cert.validFrom) > 0 &&
        strlen(cert.validTo) > 0)
        validityOK = 1;

    /* Check public key */
    if (strlen(cert.publicKey) > 0)
        keyOK = 1;

    printf("\n========================================\n");
    printf("       VERIFICATION RESULTS\n");
    printf("========================================\n");

    printf("\nSubject       : %s", cert.subject);
    printf("\nIssuer        : %s", cert.issuer);
    printf("\nValid From    : %s", cert.validFrom);
    printf("\nValid To      : %s", cert.validTo);
    printf("\nPublic Key    : %s", cert.publicKey);

    printf("\n\nIssuer Check  : ");

    if (issuerOK)
        printf("VALID");
    else
        printf("INVALID");

    printf("\nValidity Check: ");

    if (validityOK)
        printf("VALID");
    else
        printf("INVALID");

    printf("\nPublic Key    : ");

    if (keyOK)
        printf("VALID");
    else
        printf("INVALID");

    printf("\n\n----------------------------------------\n");

    if (issuerOK && validityOK && keyOK)
        printf("Certificate Status: VALID\n");
    else
        printf("Certificate Status: INVALID\n");

    printf("----------------------------------------\n");

    return 0;
}
