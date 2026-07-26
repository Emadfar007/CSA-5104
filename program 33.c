#include <stdio.h>
#include <string.h>

int main() {
    FILE *fin, *fout;
    char ch;
    char key[] = "SecretKey123";
    int i = 0, keyLen = strlen(key);

    fin = fopen("input.txt", "r");
    fout = fopen("encrypted.txt", "w");

    if (fin == NULL) {
        printf("Cannot open input file!\n");
        return 1;
    }

    while ((ch = fgetc(fin)) != EOF) {
        fputc(ch ^ key[i % keyLen], fout);
        i++;
    }

    fclose(fin);
    fclose(fout);

    printf("File encrypted successfully!\n");

    return 0;
}
