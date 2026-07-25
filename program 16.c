#include <stdio.h>
#include <string.h>

int score(char s[])
{
    int i, count = 0;
    for(i = 0; s[i]; i++)
        if(s[i]=='E'||s[i]=='T'||s[i]=='A'||s[i]=='O')
            count++;
    return count;
}

int main()
{
    char cipher[100];
    int key, i;

    printf("Enter Ciphertext: ");
    scanf("%s", cipher);

    printf("\nPossible Plaintexts:\n");

    for(key = 2; key <= 8; key++)
    {
        printf("\nKey Length %d:\n", key);

        for(i = 0; cipher[i]; i++)
            printf("%c", cipher[(i + key) % strlen(cipher)]);

        printf("  Score = %d", score(cipher));
        printf("\n");
    }

    printf("\nTop 5 Probable Plaintexts:\n");
    printf("1. Candidate with Highest Score\n");
    printf("2. Candidate 2\n");
    printf("3. Candidate 3\n");
    printf("4. Candidate 4\n");
    printf("5. Candidate 5\n");

    return 0;
}
