#include <stdio.h>
#include <string.h>

#define MAX 1000

void encrypt(char text[], int key)
{
    char rail[10][MAX];
    int i, j;

    for(i=0;i<key;i++)
        for(j=0;j<strlen(text);j++)
            rail[i][j]='\n';

    int row=0, dir=1;

    for(i=0;i<strlen(text);i++)
    {
        rail[row][i]=text[i];

        if(row==0)
            dir=1;
        else if(row==key-1)
            dir=-1;

        row+=dir;
    }

    printf("\nRail Matrix:\n");
    for(i=0;i<key;i++)
    {
        for(j=0;j<strlen(text);j++)
        {
            if(rail[i][j]=='\n')
                printf("  ");
            else
                printf("%c ",rail[i][j]);
        }
        printf("\n");
    }

    printf("\nCiphertext: ");

    for(i=0;i<key;i++)
        for(j=0;j<strlen(text);j++)
            if(rail[i][j]!='\n')
                printf("%c",rail[i][j]);

    printf("\n");
}

void decrypt(char text[], int key)
{
    char rail[10][MAX];
    int i,j,len=strlen(text);

    for(i=0;i<key;i++)
        for(j=0;j<len;j++)
            rail[i][j]='\n';

    int row=0,dir=1;

    for(i=0;i<len;i++)
    {
        rail[row][i]='*';

        if(row==0)
            dir=1;
        else if(row==key-1)
            dir=-1;

        row+=dir;
    }

    int index=0;

    for(i=0;i<key;i++)
        for(j=0;j<len;j++)
            if(rail[i][j]=='*')
                rail[i][j]=text[index++];

    row=0;
    dir=1;

    printf("Decrypted Text: ");

    for(i=0;i<len;i++)
    {
        printf("%c",rail[row][i]);

        if(row==0)
            dir=1;
        else if(row==key-1)
            dir=-1;

        row+=dir;
    }

    printf("\n");
}

int main()
{
    char plain[MAX];
    int rails;

    printf("Enter Plaintext: ");
    fgets(plain,MAX,stdin);

    plain[strcspn(plain,"\n")]='\0';

    printf("Enter Number of Rails (2-10): ");
    scanf("%d",&rails);

    encrypt(plain,rails);

    char cipher[MAX];
    printf("\nEnter Ciphertext for Decryption: ");
    scanf("%s",cipher);

    decrypt(cipher,rails);

    printf("\nPerformance Analysis\n");
    printf("---------------------\n");
    printf("Encryption Time Complexity : O(n)\n");
    printf("Decryption Time Complexity : O(n)\n");
    printf("Space Complexity : O(n)\n");
    printf("\nFor n > 100000, execution time increases linearly.\n");

    return 0;
}
