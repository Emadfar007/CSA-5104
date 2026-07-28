#include <stdio.h>
#include <string.h>

void processFile(char input[], char output[], char key[])
{
    FILE *fin, *fout;
    char ch;
    int i = 0;
    int keyLen = strlen(key);

    fin = fopen(input, "rb");
    fout = fopen(output, "wb");

    if(fin == NULL)
    {
        printf("Cannot open input file!\n");
        return;
    }

    while((ch = fgetc(fin)) != EOF)
    {
        fputc(ch ^ key[i % keyLen], fout);
        i++;
    }

    fclose(fin);
    fclose(fout);
}

int main()
{
    char inputFile[100];
    char encryptedFile[100];
    char decryptedFile[100];
    char key[100];

    printf("Enter Original File Name: ");
    scanf("%s", inputFile);

    printf("Enter Encrypted File Name: ");
    scanf("%s", encryptedFile);

    printf("Enter Decrypted File Name: ");
    scanf("%s", decryptedFile);

    printf("Enter Secret Key: ");
    scanf("%s", key);

    processFile(inputFile, encryptedFile, key);

    processFile(encryptedFile, decryptedFile, key);

    printf("\nOriginal File   : %s\n", inputFile);
    printf("Encrypted File  : %s\n", encryptedFile);
    printf("Decrypted File  : %s\n", decryptedFile);
    printf("\nVerification Complete.\n");
    printf("Compare '%s' with '%s'. They should be identical.\n",
           inputFile, decryptedFile);

    return 0;
}
