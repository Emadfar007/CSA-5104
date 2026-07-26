#include <stdio.h>
#include <string.h>

int main() {
    char cipher[] = {
        0x1D, 0x20, 0x37, 0x25, 0x2A, 0x39, 0x00,
        0x20, 0x2A, 0x72, 0x67, 0x71, 0x26, 0x31,
        0x20
    };

    char key[] = "SecretKey123";
    char plain[100];
    int i, keyLen = strlen(key);

    for (i = 0; i < 15; i++) {
        plain[i] = cipher[i] ^ key[i % keyLen];
    }
    plain[15] = '\0';

    printf("Decrypted Plaintext: %s\n", plain);

    return 0;
}
