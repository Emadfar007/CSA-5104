#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char image[200];
    char msg[100], enc[100], dec[100];
    char key = 'K';
    int i, len;

    // Dummy image data
    for(i = 0; i < 200; i++)
        image[i] = 100;

    printf("Enter Secret Message: ");
    scanf("%s", msg);

    len = strlen(msg);

    // Encrypt using XOR
    for(i = 0; i < len; i++)
        enc[i] = msg[i] ^ key;
    enc[len] = '\0';

    // Hide encrypted message (simulation)
    for(i = 0; i < len; i++)
        image[i] = enc[i];

    printf("\nEncrypted Message Hidden Successfully!\n");

    // Extract encrypted message
    for(i = 0; i < len; i++)
        enc[i] = image[i];
    enc[len] = '\0';

    // Decrypt
    for(i = 0; i < len; i++)
        dec[i] = enc[i] ^ key;
    dec[len] = '\0';

    printf("Recovered Message: %s\n", dec);

    return 0;
}
