#include <stdio.h>
#include <string.h>

int main()
{
    char frame[10][100];
    char msg[50], out[50];
    int i, len;

    // Dummy video frames
    for(i = 0; i < 10; i++)
        strcpy(frame[i], "FRAME_DATA");

    printf("Enter Secret Message: ");
    scanf("%s", msg);

    len = strlen(msg);

    // Embed message into selected frames
    for(i = 0; i < len; i++)
        frame[i][0] = msg[i];

    printf("\nMessage Embedded Successfully!\n");

    // Extract message
    for(i = 0; i < len; i++)
        out[i] = frame[i][0];

    out[len] = '\0';

    printf("Extracted Message: %s\n", out);

    return 0;
}
