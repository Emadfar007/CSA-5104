#include <stdio.h>
#include <string.h>

int main()
{
    char plaintext[100], key[100];
    char cipher[100], decrypted[100];
    int w, r;
    int i, keyLen;

    printf("Enter Plaintext: ");
    gets(plaintext);

    printf("Enter Word Size (w): ");
    scanf("%d", &w);

    printf("Enter Number of Rounds (r): ");
    scanf("%d", &r);

    getchar();

    printf("Enter Secret Key: ");
    gets(key);

    keyLen = strlen(key);

    /* Encryption */
    for(i = 0; i < strlen(plaintext); i++)
        cipher[i] = plaintext[i] ^ key[i % keyLen];
    cipher[i] = '\0';

    printf("\nCiphertext (Hex): ");
    for(i = 0; i < strlen(plaintext); i++)
        printf("%02X ", (unsigned char)cipher[i]);

    /* Decryption */
    for(i = 0; i < strlen(plaintext); i++)
        decrypted[i] = cipher[i] ^ key[i % keyLen];
    decrypted[i] = '\0';

    printf("\n\nDecrypted Plaintext: %s\n", decrypted);

    if(strcmp(plaintext, decrypted) == 0)
        printf("Verification Successful!\n");
    else
        printf("Verification Failed!\n");

    return 0;
}
