#include <stdio.h>
#include <string.h>
#include <time.h>

void encrypt(char text[], char key[], int rounds)
{
    int i, j, keyLen = strlen(key);

    for(j = 0; j < rounds; j++)
    {
        for(i = 0; i < strlen(text); i++)
            text[i] ^= key[i % keyLen];
    }
}

void decrypt(char text[], char key[], int rounds)
{
    int i, j, keyLen = strlen(key);

    for(j = 0; j < rounds; j++)
    {
        for(i = 0; i < strlen(text); i++)
            text[i] ^= key[i % keyLen];
    }
}

int main()
{
    char original[] = "NETWORKSECURITY";
    char key[] = "Secret123";
    char text[100];

    int rounds[] = {8, 12, 16, 20};
    int i;

    clock_t start, end;
    double encTime, decTime;

    printf("--------------------------------------------------------\n");
    printf("Rounds\tEncryption(ms)\tDecryption(ms)\n");
    printf("--------------------------------------------------------\n");

    for(i = 0; i < 4; i++)
    {
        strcpy(text, original);

        start = clock();
        encrypt(text, key, rounds[i]);
        end = clock();
        encTime = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

        start = clock();
        decrypt(text, key, rounds[i]);
        end = clock();
        decTime = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

        printf("%d\t%.3f\t\t%.3f\n",
               rounds[i], encTime, decTime);
    }

    printf("--------------------------------------------------------\n");

    return 0;
}
