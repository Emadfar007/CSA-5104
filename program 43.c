#include <stdio.h>
#include <string.h>

int main()
{
    char plain1[] = "NETWORK";
    char plain2[] = "NETWORL";   // One character changed
    char key[] = "Secret123";

    char cipher1[100], cipher2[100];
    int i, changedBits = 0, totalBits = 0;
    int keyLen = strlen(key);

    /* Encrypt Original Plaintext */
    for(i = 0; i < strlen(plain1); i++)
        cipher1[i] = plain1[i] ^ key[i % keyLen];

    /* Encrypt Modified Plaintext */
    for(i = 0; i < strlen(plain2); i++)
        cipher2[i] = plain2[i] ^ key[i % keyLen];

    printf("Original Ciphertext : ");
    for(i = 0; i < strlen(plain1); i++)
        printf("%02X ", (unsigned char)cipher1[i]);

    printf("\nModified Ciphertext : ");
    for(i = 0; i < strlen(plain2); i++)
        printf("%02X ", (unsigned char)cipher2[i]);

    /* Compare Bits */
    for(i = 0; i < strlen(plain1); i++)
    {
        unsigned char diff = cipher1[i] ^ cipher2[i];

        while(diff)
        {
            changedBits += diff & 1;
            diff >>= 1;
        }

        totalBits += 8;
    }

    printf("\n\nChanged Bits Count : %d", changedBits);
    printf("\nAvalanche Percentage : %.2f%%",
           (changedBits * 100.0) / totalBits);

    return 0;
}
