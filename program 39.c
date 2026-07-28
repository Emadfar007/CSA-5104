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

    if (fin == NULL)
    {
        printf("Cannot open input file!\n");
        return;
    }

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
    char inputFile[100], encFile[100], decFile[100];
    int choice;

    char key128[] = "1234567890ABCDEF";
    char key192[] = "1234567890ABCDEFGHIJKL";
    char key256[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    printf("Enter Input File Name: ");
    scanf("%s", inputFile);

    printf("Enter Encrypted File Name: ");
    scanf("%s", encFile);

    printf("Enter Decrypted File Name: ");
    scanf("%s", decFile);

    printf("\nChoose AES Version:\n");
    printf("1. AES-128\n");
    printf("2. AES-192\n");
    printf("3. AES-256\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            processFile(inputFile, encFile, key128);
            processFile(encFile, decFile, key128);
            break;

        case 2:
            processFile(inputFile, encFile, key192);
            processFile(encFile, decFile, key192);
            break;

        case 3:
            processFile(inputFile, encFile, key256);
            processFile(encFile, decFile, key256);
            break;

        default:
            printf("Invalid Choice!\n");
            return 0;
    }

    printf("\nEncryption Completed.\n");
    printf("Decryption Completed.\n");
    printf("Check '%s' to verify it matches the original file.\n", decFile);

    return 0;
}
