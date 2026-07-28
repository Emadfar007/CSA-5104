#include <stdio.h>
#include <string.h>

int main()
{
    char plaintext[100], key[100], cipher[100], decrypted[100];
    int i, keyLen;

    printf("Enter Plaintext: ");
    gets(plaintext);

    printf("Enter Key: ");
    gets(key);

    keyLen = strlen(key);

    /* Encryption */
    for(i = 0; i < strlen(plaintext); i++)
        cipher[i] = plaintext[i] ^ key[i % keyLen];
    cipher[i] = '\0';

    printf("\nEncrypted (Hex): ");
    for(i = 0; i < strlen(plaintext); i++)
        printf("%02X ", (unsigned char)cipher[i]);

    /* Decryption */
    for(i = 0; i < strlen(plaintext); i++)
        decrypted[i] = cipher[i] ^ key[i % keyLen];
    decrypted[i] = '\0';

    printf("\n\nDecrypted Text: %s\n", decrypted);

    if(strcmp(plaintext, decrypted) == 0)
        printf("Verification Successful!\n");
    else
        printf("Verification Failed!\n");

    return 0;
}
