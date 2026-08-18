#include <stdio.h>
#include <string.h>

int verifyCertificate()
{
    char issuer[] = "Trusted Certificate Authority";
    char subject[] = "Secure Server";
    int valid = 1;

    printf("\n--- Certificate Verification ---\n");

    printf("Issuer  : %s\n", issuer);
    printf("Subject : %s\n", subject);
    printf("Validity: Valid\n");

    if (valid)
    {
        printf("Certificate verification: SUCCESS\n");
        return 1;
    }

    printf("Certificate verification: FAILED\n");
    return 0;
}

int main()
{
    char clientHello[] = "ClientHello";
    char serverHello[] = "ServerHello";

    printf("============================================\n");
    printf("       TLS SECURE CONNECTION SIMULATION\n");
    printf("============================================\n");

    printf("\n--- TLS HANDSHAKE ---\n");

    /* Step 1 */
    printf("\nClient -> Server : %s", clientHello);
    printf("\nClient sends supported TLS version and cipher suites.");

    /* Step 2 */
    printf("\n\nServer -> Client : %s", serverHello);
    printf("\nServer selects TLS version and cipher suite.");

    /* Step 3 */
    printf("\n\nServer -> Client : Certificate");
    printf("\nServer sends its digital certificate.");

    /* Step 4 */
    if (!verifyCertificate())
    {
        printf("\nTLS connection terminated.\n");
        return 0;
    }

    /* Step 5 */
    printf("\n--- Key Exchange ---\n");
    printf("Client -> Server : Key Exchange");
    printf("\nServer -> Client : Key Exchange");
    printf("\nShared session key established.");

    /* Step 6 */
    printf("\n\nClient -> Server : Finished");
    printf("\nServer -> Client : Finished");

    /* Connection established */
    printf("\n\n============================================\n");
    printf("TLS HANDSHAKE COMPLETED SUCCESSFULLY\n");
    printf("============================================\n");

    printf("\nSecure connection established.");
    printf("\nData can now be transmitted securely.\n");

    return 0;
}
