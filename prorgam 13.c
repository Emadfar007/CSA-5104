#include <stdio.h>
#include <string.h>

#define MAX 100

int main()
{
    char text[MAX], key[20], mat[20][20];
    int rank[20], used[20]={0};
    int i,j,k=0,len,rows,col;

    printf("Enter Plaintext: ");
    fgets(text,MAX,stdin);
    text[strcspn(text,"\n")]=0;

    printf("Enter Keyword: ");
    scanf("%s",key);

    col=strlen(key);
    len=strlen(text);
    rows=(len+col-1)/col;

    while(len<rows*col)
        text[len++]='X';
    text[len]='\0';

    // Ranking of keyword (handles duplicates)
    for(i=0;i<col;i++)
    {
        int pos=-1;
        char min='Z'+1;
        for(j=0;j<col;j++)
        {
            if(!used[j] && key[j]<min)
            {
                min=key[j];
                pos=j;
            }
        }
        rank[pos]=i+1;
        used[pos]=1;
    }

    printf("\nKey Ranking:\n");
    for(i=0;i<col;i++)
        printf("%c ",key[i]);
    printf("\n");
    for(i=0;i<col;i++)
        printf("%d ",rank[i]);

    // Fill Matrix
    k=0;
    for(i=0;i<rows;i++)
        for(j=0;j<col;j++)
            mat[i][j]=text[k++];

    printf("\n\nOriginal Matrix:\n");
    for(i=0;i<rows;i++)
    {
        for(j=0;j<col;j++)
            printf("%c ",mat[i][j]);
        printf("\n");
    }

    // Encryption
    printf("\nCiphertext: ");
    for(k=1;k<=col;k++)
    {
        for(j=0;j<col;j++)
        {
            if(rank[j]==k)
            {
                for(i=0;i<rows;i++)
                    printf("%c",mat[i][j]);
            }
        }
    }

    // Permuted Matrix
    printf("\n\nPermuted Matrix:\n");
    for(i=0;i<rows;i++)
    {
        for(k=1;k<=col;k++)
        {
            for(j=0;j<col;j++)
            {
                if(rank[j]==k)
                    printf("%c ",mat[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nDecryption: Reverse the column order using the same ranking.\n");

    return 0;
}
