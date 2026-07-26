#include <stdio.h>

int main() {
    FILE *fin, *fout;
    char ch;
    char key = 'K';   // Encryption key

    fin = fopen("input.txt", "r");
    fout = fopen("encrypted.txt", "w");

    if (fin == NULL) {
        printf("Cannot open input file!\n");
        return 1;
    }

    while ((ch = fgetc(fin)) != EOF) {
        fputc(ch ^ key, fout);   // Encrypt using XOR
    }

    fclose(fin);
    fclose(fout);

    printf("File encrypted successfully!\n");

    return 0;
}
