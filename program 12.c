#include <stdio.h>
#include <string.h>

#define MAX 100

int main()
{
    char plain[MAX], cipher[MAX], decrypt[MAX];
    char pad;
    char mat[20][20];
    int key, rows, len, i, j, k = 0;

    printf("Enter Plaintext: ");
    fgets(plain, MAX, stdin);
    plain[strcspn(plain, "\n")] = '\0';

    printf("Enter Key Length: ");
    scanf("%d", &key);

    printf("Enter Padding Character: ");
    scanf(" %c", &pad);

    len = strlen(plain);
    rows = (len + key - 1) / key;

    while(len < rows * key)
        plain[len++] = pad;
    plain[len] = '\0';

    // Fill Matrix
    k = 0;
    for(i = 0; i < rows; i++)
        for(j = 0; j < key; j++)
            mat[i][j] = plain[k++];

    printf("\nRow-wise Matrix:\n");
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < key; j++)
            printf("%c ", mat[i][j]);
        printf("\n");
    }

    // Encryption
    k = 0;
    for(j = 0; j < key; j++)
        for(i = 0; i < rows; i++)
            cipher[k++] = mat[i][j];
    cipher[k] = '\0';

    printf("\nCiphertext: %s\n", cipher);

    // Decryption
    k = 0;
    for(j = 0; j < key; j++)
        for(i = 0; i < rows; i++)
            mat[i][j] = cipher[k++];

    k = 0;
    for(i = 0; i < rows; i++)
        for(j = 0; j < key; j++)
            decrypt[k++] = mat[i][j];
    decrypt[k] = '\0';

    // Remove Padding
    while(k > 0 && decrypt[k - 1] == pad)
    {
        decrypt[k - 1] = '\0';
        k--;
    }

    printf("Decrypted Text: %s\n", decrypt);

    return 0;
}
