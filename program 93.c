#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Simple XOR encryption/decryption */

void encryptDecrypt(char text[], char key[])
{
    int i;
    int keyLen = strlen(key);

    for (i = 0; text[i] != '\0'; i++)
        text[i] = text[i] ^ key[i % keyLen];
}

/* Simple hash for demonstration */

unsigned long simpleHash(char text[])
{
    unsigned long hash = 5381;
    int i;

    for (i = 0; text[i] != '\0'; i++)
        hash = ((hash << 5) + hash) + text[i];

    return hash;
}

int main()
{
    char message[200];
    char key[100];
    char encrypted[200];
    char decrypted[200];

    unsigned long senderHash;
    unsigned long receiverHash;

    int i;

    printf("============================================\n");
    printf("       SECURE CLIENT-SERVER SYSTEM\n");
    printf("============================================\n");

    /* Client */
    printf("\n--- CLIENT ---\n");

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter secret key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    /* Generate hash */
    senderHash = simpleHash(message);

    /* Copy message for encryption */
    strcpy(encrypted, message);

    encryptDecrypt(encrypted, key);

    printf("\nClient Hash: %lu", senderHash);

    printf("\nEncrypted Data: ");

    for (i = 0; encrypted[i] != '\0'; i++)
        printf("%02X ", (unsigned char)encrypted[i]);

    /* Server */
    printf("\n\n--- SERVER ---\n");

    strcpy(decrypted, encrypted);

    /* Decrypt */
    encryptDecrypt(decrypted, key);

    receiverHash = simpleHash(decrypted);

    printf("Decrypted Message: %s", decrypted);
    printf("\nServer Hash: %lu", receiverHash);

    /* Verification */
    if (senderHash == receiverHash)
    {
        printf("\n\nMessage Integrity: VERIFIED");
        printf("\nSecure communication successful.\n");
    }
    else
    {
        printf("\n\nMessage Integrity: FAILED");
        printf("\nMessage may have been modified.\n");
    }

    return 0;
}
