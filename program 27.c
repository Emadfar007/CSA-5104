#include <stdio.h>

int main() {
    char cipher[9] = {0x02, 0x7E, 0x7F, 0x62, 0x76, 0x67, 0x76, 0x66, '\0'};
    char key[9] = "A1B2C3D4";
    char plain[9];
    int i;

    for (i = 0; i < 8; i++) {
        plain[i] = cipher[i] ^ key[i];
    }
    plain[8] = '\0';

    printf("Decrypted Plaintext: %s\n", plain);

    return 0;
}
