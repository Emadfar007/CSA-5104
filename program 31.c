#include <stdio.h>
#include <string.h>

int main() {
    char plaintext[] = "NETWORKSECURITY";
    char key[] = "SecretKey123";
    char cipher[100];
    int i, keyLen = strlen(key);

    for (i = 0; i < strlen(plaintext); i++) {
        cipher[i] = plaintext[i] ^ key[i % keyLen];
    }

    printf("Plaintext : %s\n", plaintext);
    printf("Key       : %s\n", key);

    printf("Ciphertext (Hex): ");
    for (i = 0; i < strlen(plaintext); i++) {
        printf("%02X ", (unsigned char)cipher[i]);
    }

    printf("\n");

    return 0;
}
