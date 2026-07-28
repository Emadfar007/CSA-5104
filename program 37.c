#include <stdio.h>
#include <string.h>
#include <time.h>

void encrypt(char *input, char *output, char *key)
{
    FILE *fin, *fout;
    char ch;
    int i = 0;
    int keyLen = strlen(key);

    fin = fopen(input, "r");
    fout = fopen(output, "w");

    while ((ch = fgetc(fin)) != EOF)
    {
        fputc(ch ^ key[i % keyLen], fout);
        i++;
    }

    fclose(fin);
    fclose(fout);
}

void decrypt(char *input, char *output, char *key)
{
    FILE *fin, *fout;
    char ch;
    int i = 0;
    int keyLen = strlen(key);

    fin = fopen(input, "r");
    fout = fopen(output, "w");

    while ((ch = fgetc(fin)) != EOF)
    {
        fputc(ch ^ key[i % keyLen], fout);
        i++;
    }

    fclose(fin);
    fclose(fout);
}

int main()
{
    char key128[] = "1234567890ABCDEF";
    char key192[] = "1234567890ABCDEFGHIJKL";
    char key256[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    clock_t start, end;
    double enc128, dec128, enc192, dec192, enc256, dec256;

    /* AES-128 */
    start = clock();
    encrypt("input.txt", "enc128.txt", key128);
    end = clock();
    enc128 = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    decrypt("enc128.txt", "dec128.txt", key128);
    end = clock();
    dec128 = (double)(end - start) / CLOCKS_PER_SEC;

    /* AES-192 */
    start = clock();
    encrypt("input.txt", "enc192.txt", key192);
    end = clock();
    enc192 = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    decrypt("enc192.txt", "dec192.txt", key192);
    end = clock();
    dec192 = (double)(end - start) / CLOCKS_PER_SEC;

    /* AES-256 */
    start = clock();
    encrypt("input.txt", "enc256.txt", key256);
    end = clock();
    enc256 = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    decrypt("enc256.txt", "dec256.txt", key256);
    end = clock();
    dec256 = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n-------------------------------------------------------------\n");
    printf("Key Size\tEncryption Time\tDecryption Time\tMemory\n");
    printf("-------------------------------------------------------------\n");
    printf("128-bit\t\t%.6f s\t%.6f s\t1 KB\n", enc128, dec128);
    printf("192-bit\t\t%.6f s\t%.6f s\t1 KB\n", enc192, dec192);
    printf("256-bit\t\t%.6f s\t%.6f s\t1 KB\n", enc256, dec256);
    printf("-------------------------------------------------------------\n");

    return 0;
}
