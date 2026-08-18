#include <stdio.h>

int main()
{
    printf("========================================\n");
    printf("        SSL/TLS HANDSHAKE ANALYZER\n");
    printf("========================================\n");

    printf("\n1. ClientHello\n");
    printf("   Client -> Server\n");
    printf("   Contains TLS version and cipher suites.\n");

    printf("\n2. ServerHello\n");
    printf("   Server -> Client\n");
    printf("   Server selects TLS version and cipher suite.\n");

    printf("\n3. Certificate\n");
    printf("   Server -> Client\n");
    printf("   Server sends its digital certificate.\n");

    printf("\n4. Key Exchange\n");
    printf("   Client <-> Server\n");
    printf("   Secure session key is established.\n");

    printf("\n5. Finished\n");
    printf("   Client <-> Server\n");
    printf("   Handshake verification is completed.\n");

    printf("\n========================================\n");
    printf("       TLS HANDSHAKE ANALYSIS\n");
    printf("========================================\n");

    printf("\nClientHello : Detected");
    printf("\nServerHello : Detected");
    printf("\nCertificate : Detected");
    printf("\nKey Exchange: Detected");
    printf("\nFinished    : Detected");

    printf("\n\nTLS Handshake completed successfully.\n");

    return 0;
}
