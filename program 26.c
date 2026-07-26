#include <stdio.h>
#include <string.h>

int main() {
    char plaintext[9] = "COMPUTER";
    char key[9] = "A1B2C3D4";
    char cipher[9];
    int i;

    printf("Plaintext: %s\n", plaintext);
    printf("Key: %s\n", key);

    // Simple XOR encryption
    for (i = 0; i < 8; i++) {
        cipher[i] = plaintext[i] ^ key[i];
    }
    cipher[8] = '\0';

    printf("Ciphertext (Hex): ");
    for (i = 0; i < 8; i++) {
        printf("%02X ", (unsigned char)cipher[i]);
    }

    printf("\n");

    return 0;
}
