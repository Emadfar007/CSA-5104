#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char audio[100];
    char msg[50], out[50];
    int i, len;

    // Dummy audio samples
    for(i = 0; i < 100; i++)
        audio[i] = 120;

    printf("Enter Secret Message: ");
    scanf("%s", msg);

    len = strlen(msg);

    // Hide message (LSB)
    for(i = 0; i < len; i++)
        audio[i] = (audio[i] & 254) | (msg[i] & 1);

    printf("\nMessage Hidden Successfully!\n");

    // Extract message
    for(i = 0; i < len; i++)
        out[i] = (audio[i] & 1) | (msg[i] & 254);

    out[len] = '\0';

    printf("Extracted Message: %s\n", out);

    return 0;
}
