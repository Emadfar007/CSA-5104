#include <stdio.h>
#include <time.h>

void encrypt(char *input, char *output)
{
    FILE *fin, *fout;
    char ch;
    char key = 'K';

    fin = fopen(input, "r");
    fout = fopen(output, "w");

    while ((ch = fgetc(fin)) != EOF)
        fputc(ch ^ key, fout);

    fclose(fin);
    fclose(fout);
}

void decrypt(char *input, char *output)
{
    FILE *fin, *fout;
    char ch;
    char key = 'K';

    fin = fopen(input, "r");
    fout = fopen(output, "w");

    while ((ch = fgetc(fin)) != EOF)
        fputc(ch ^ key, fout);

    fclose(fin);
    fclose(fout);
}

int main()
{
    clock_t start, end;
    double enc_time, dec_time;

    start = clock();
    encrypt("input.txt", "encrypted.txt");
    end = clock();
    enc_time = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    decrypt("encrypted.txt", "decrypted.txt");
    end = clock();
    dec_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Encryption Time : %f seconds\n", enc_time);
    printf("Decryption Time : %f seconds\n", dec_time);

    return 0;
}
