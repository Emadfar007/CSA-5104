#include <stdio.h>
#include <string.h>

void decryptCaesar(char *ciphertext, int key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            ciphertext[i] = ((ciphertext[i] - 'A' - key + 26) % 26) + 'A';
        }
    }
}

int main() {
    char ciphertext[] = "PHHW PH DIWHU WKH WRJD SDUWB";
    
    // Brute-force attack on Caesar cipher
    for (int key = 0; key < 26; key++) {
        printf("Key: %d, Plaintext: ", key);
        strcpy(ciphertext, "PHHW PH DIWHU WKH WRJD SDUWB"); // Reset ciphertext
        decryptCaesar(ciphertext, key);
        printf("%s\n", ciphertext);
    }
    
    return 0;
}
