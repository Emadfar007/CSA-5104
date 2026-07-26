#include <stdio.h>

int main() {
    FILE *fin, *fout;
    char ch;
    char key = 'K';   // Same key used for encryption

    fin = fopen("encrypted.txt", "r");
    fout = fopen("decrypted.txt", "w");

    if (fin == NULL) {
        printf("Cannot open encrypted file!\n");
        return 1;
    }

    while ((ch = fgetc(fin)) != EOF) {
        fputc(ch ^ key, fout);   // Decrypt using XOR
    }

    fclose(fin);
    fclose(fout);

    printf("File decrypted successfully!\n");

    return 0;
}
