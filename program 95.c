#include <stdio.h>
#include <string.h>

int main()
{
    char message[100];

    printf("========================================\n");
    printf("       SSL/TLS SOCKET SIMULATION\n");
    printf("========================================\n");

    /* Server */
    printf("\n[SERVER]\n");
    printf("Server started on port 443...\n");
    printf("Waiting for client...\n");

    /* Client */
    printf("\n[CLIENT]\n");
    printf("Connecting to server...\n");

    printf("\nTCP socket connection established.");

    /* TLS Handshake */
    printf("\n\n--- TLS HANDSHAKE ---\n");

    printf("ClientHello sent.\n");
    printf("ServerHello received.\n");
    printf("Server certificate received.\n");
    printf("Certificate verified.\n");
    printf("Key exchange completed.\n");
    printf("Finished messages exchanged.\n");

    printf("\nTLS connection established successfully.");

    /* Secure communication */
    printf("\n\nEnter message to send: ");
    fgets(message, sizeof(message), stdin);

    message[strcspn(message, "\n")] = '\0';

    printf("\nClient -> Server: %s", message);
    printf("\nServer received the message securely.");

    printf("\n\nServer -> Client: Message received successfully.");

    printf("\n\nConnection closed.\n");

    return 0;
}
