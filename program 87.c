#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], char key[], char result[])
{
    int i, j = 0;
    int keyLen = strlen(key);

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char base = isupper(text[i]) ? 'A' : 'a';

            result[i] = (text[i] - base +
                         toupper(key[j % keyLen]) - 'A') % 26 + base;

            j++;
        }
        else
        {
            result[i] = text[i];
        }
    }

    result[i] = '\0';
}

void decrypt(char text[], char key[], char result[])
{
    int i, j = 0;
    int keyLen = strlen(key);

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char base = isupper(text[i]) ? 'A' : 'a';

            result[i] = (text[i] - base -
                         (toupper(key[j % keyLen]) - 'A') + 26) % 26 + base;

            j++;
        }
        else
        {
            result[i] = text[i];
        }
    }

    result[i] = '\0';
}

int main()
{
    char text[200];
    char key[100];
    char encrypted[200];
    char decrypted[200];

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    encrypt(text, key, encrypted);
    decrypt(encrypted, key, decrypted);

    printf("\nOriginal Message : %s", text);
    printf("\nKey              : %s", key);
    printf("\nEncrypted Message: %s", encrypted);
    printf("\nDecrypted Message: %s\n", decrypted);

    return 0;
}
