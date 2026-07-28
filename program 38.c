#include <stdio.h>
#include <string.h>

int main()
{
    char plain1[] = "HELLO";
    char plain2[] = "IELLO";   // One character changed
    char key[] = "SecretKey";

    char cipher1[100], cipher2[100];
    int i, changed = 0, bits = 0;
    int keyLen = strlen(key);

    /* Encrypt first plaintext */
    for(i = 0; i < strlen(plain1); i++)
        cipher1[i] = plain1[i] ^ key[i % keyLen];

    /* Encrypt modified plaintext */
    for(i = 0; i < strlen(plain2); i++)
        cipher2[i] = plain2[i] ^ key[i % keyLen];

    /* Compare bits */
    for(i = 0; i < strlen(plain1); i++)
    {
        unsigned char diff = cipher1[i] ^ cipher2[i];

        while(diff)
        {
            changed += diff & 1;
            diff >>= 1;
        }

        bits += 8;
    }

    printf("Changed Bits      : %d\n", changed);
    printf("Total Bits        : %d\n", bits);
    printf("Avalanche Effect  : %.2f%%\n",
           (changed * 100.0) / bits);

    return 0;
}
