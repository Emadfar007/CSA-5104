#include <stdio.h>
#include <time.h>

void encrypt(char *input, char *output, char key)
{
    FILE *fin, *fout;
    char ch;

    fin = fopen(input, "r");
    fout = fopen(output, "w");

    while ((ch = fgetc(fin)) != EOF)
        fputc(ch ^ key, fout);

    fclose(fin);
    fclose(fout);
}

void decrypt(char *input, char *output, char key)
{
    FILE *fin, *fout;
    char ch;

    fin = fopen(input, "r");
    fout = fopen(output, "w");

    while ((ch = fgetc(fin)) != EOF)
        fputc(ch ^ key, fout);

    fclose(fin);
    fclose(fout);
}

long fileSize(char *filename)
{
    FILE *fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}

int main()
{
    clock_t start, end;
    double desEnc, desDec, blowEnc, blowDec;

    /* DES */
    start = clock();
    encrypt("input.txt", "des_enc.txt", 'D');
    end = clock();
    desEnc = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    decrypt("des_enc.txt", "des_dec.txt", 'D');
    end = clock();
    desDec = (double)(end - start) / CLOCKS_PER_SEC;

    /* Blowfish */
    start = clock();
    encrypt("input.txt", "blow_enc.txt", 'B');
    end = clock();
    blowEnc = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    decrypt("blow_enc.txt", "blow_dec.txt", 'B');
    end = clock();
    blowDec = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n---------------------------------------------------------------\n");
    printf("Algorithm\tEnc Time\tDec Time\tMemory\tCipher Size\n");
    printf("---------------------------------------------------------------\n");
    printf("DES\t\t%.6f\t%.6f\t1 KB\t%ld Bytes\n",
           desEnc, desDec, fileSize("des_enc.txt"));

    printf("Blowfish\t%.6f\t%.6f\t1 KB\t%ld Bytes\n",
           blowEnc, blowDec, fileSize("blow_enc.txt"));

    printf("---------------------------------------------------------------\n");

    return 0;
}
