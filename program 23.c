#include <stdio.h>
#include <string.h>

int main()
{
    char file[100], image[100], extracted[100];

    printf("Enter File Content: ");
    fgets(file, sizeof(file), stdin);
    file[strcspn(file, "\n")] = '\0';

    // Hide file inside image (simulation)
    strcpy(image, file);

    printf("\nFile Hidden Successfully!\n");

    // Extract file
    strcpy(extracted, image);

    printf("Recovered File Content: %s\n", extracted);

    return 0;
}
