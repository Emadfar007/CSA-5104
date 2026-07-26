#include <stdio.h>
#include <string.h>

int main() {
    FILE *fin, *fout;
    char ch;
    char key[] = "SecretKey123";
    int i = 0, keyLen = strlen(key);

    fin = fopen("encrypted.txt", "r");
    fout = fopen("decrypted.txt", "w");

    if (fin == NULL) {
        printf("Cannot open encrypted file!\n");
        return 1;
    }

    while ((ch = fgetc(fin)) != EOF) {
        fputc(ch ^ key[i % keyLen], fout);
        i++;
    }

    fclose(fin);
    fclose(fout);

    printf("File decrypted successfully!\n");
    printf("Check 'decrypted.txt' to verify it matches 'input.txt'.\n");

    return 0;
}
