#include <stdio.h>
#include <string.h>

void encrypt(char text[], int shift)
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = ((text[i] - 'A' + shift) % 26) + 'A';

        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = ((text[i] - 'a' + shift) % 26) + 'a';
    }
}

void decrypt(char text[], int shift)
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = ((text[i] - 'A' - shift + 26) % 26) + 'A';

        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = ((text[i] - 'a' - shift + 26) % 26) + 'a';
    }
}

int main()
{
    char text[200];
    char encrypted[200];
    int shift;

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);

    text[strcspn(text, "\n")] = '\0';

    printf("Enter shift value: ");
    scanf("%d", &shift);

    shift = shift % 26;

    strcpy(encrypted, text);

    encrypt(encrypted, shift);

    printf("\nOriginal Message : %s", text);
    printf("\nEncrypted Message: %s", encrypted);

    decrypt(encrypted, shift);

    printf("\nDecrypted Message: %s\n", encrypted);

    return 0;
}
