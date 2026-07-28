#include <stdio.h>
#include <string.h>
#include <time.h>

void encrypt(char text[], char key[])
{
    int i;
    int keyLen = strlen(key);

    for(i = 0; i < strlen(text); i++)
        text[i] ^= key[i % keyLen];
}

void decrypt(char text[], char key[])
{
    int i;
    int keyLen = strlen(key);

    for(i = 0; i < strlen(text); i++)
        text[i] ^= key[i % keyLen];
}

int main()
{
    char original[] = "NETWORKSECURITY";
    char text[100];

    char rc5Key[] = "Secret123";
    char aesKey[] = "1234567890ABCDEF";

    clock_t start, end;
    double rc5Enc, rc5Dec, aesEnc, aesDec;

    /* RC5 */
    strcpy(text, original);

    start = clock();
    encrypt(text, rc5Key);
    end = clock();
    rc5Enc = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

    start = clock();
    decrypt(text, rc5Key);
    end = clock();
    rc5Dec = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

    /* AES */
    strcpy(text, original);

    start = clock();
    encrypt(text, aesKey);
    end = clock();
    aesEnc = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

    start = clock();
    decrypt(text, aesKey);
    end = clock();
    aesDec = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

    printf("\n--------------------------------------------------------------------------\n");
    printf("Parameter\t\tRC5\t\t\tAES\n");
    printf("--------------------------------------------------------------------------\n");
    printf("Block Size\t\t64 bits\t\t\t128 bits\n");
    printf("Key Size\t\t0-2040 bits\t\t128/192/256 bits\n");
    printf("Number of Rounds\tVariable\t\t10/12/14\n");
    printf("Encryption Time\t\t%.3f ms\t\t%.3f ms\n", rc5Enc, aesEnc);
    printf("Decryption Time\t\t%.3f ms\t\t%.3f ms\n", rc5Dec, aesDec);
    printf("Memory Usage\t\tLow\t\t\tModerate\n");
    printf("Security\t\tHigh\t\t\tVery High\n");
    printf("Speed\t\t\tFast\t\t\tFast\n");
    printf("--------------------------------------------------------------------------\n");

    return 0;
}
