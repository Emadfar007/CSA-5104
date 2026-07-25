#include <stdio.h>
#include <string.h>

int main()
{
    char msg[100], img1[50], img2[50], result[100];
    int len, mid;

    printf("Enter Secret Message: ");
    scanf("%s", msg);

    len = strlen(msg);
    mid = len / 2;

    // Split message
    strncpy(img1, msg, mid);
    img1[mid] = '\0';

    strcpy(img2, msg + mid);

    printf("\nMessage Embedded into Two Images.\n");
    printf("Image 1 Data: %s\n", img1);
    printf("Image 2 Data: %s\n", img2);

    // Reconstruct message
    strcpy(result, img1);
    strcat(result, img2);

    printf("\nReconstructed Message: %s\n", result);

    return 0;
}
