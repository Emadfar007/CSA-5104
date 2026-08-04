#include <stdio.h>
#include <string.h>

#define MAX_SA 10

struct SecurityAssociation
{
    int spi;
    char sourceIP[20];
    char destinationIP[20];
    char encryptionAlgo[20];
    char authenticationAlgo[20];
};

int main()
{
    struct SecurityAssociation sa[MAX_SA];
    int n, i;
    int searchSPI;
    int found = 0;

    printf("=============================================\n");
    printf("   Security Association (SA) Database\n");
    printf("=============================================\n");

    printf("Enter the number of Security Associations: ");
    scanf("%d", &n);

    if(n > MAX_SA)
    {
        printf("Maximum allowed entries are %d\n", MAX_SA);
        return 0;
    }

    printf("\nEnter SA Details\n");

    for(i = 0; i < n; i++)
    {
        printf("\n------ Security Association %d ------\n", i + 1);

        printf("Enter SPI: ");
        scanf("%d", &sa[i].spi);

        printf("Enter Source IP: ");
        scanf("%19s", sa[i].sourceIP);

        printf("Enter Destination IP: ");
        scanf("%19s", sa[i].destinationIP);

        printf("Enter Encryption Algorithm: ");
        scanf("%19s", sa[i].encryptionAlgo);

        printf("Enter Authentication Algorithm: ");
        scanf("%19s", sa[i].authenticationAlgo);
    }

    printf("\n=============================================\n");
    printf("Current SA Database\n");
    printf("=============================================\n");

    for(i = 0; i < n; i++)
    {
        printf("\nSA %d\n", i + 1);
        printf("SPI                  : %d\n", sa[i].spi);
        printf("Source IP            : %s\n", sa[i].sourceIP);
        printf("Destination IP       : %s\n", sa[i].destinationIP);
        printf("Encryption Algorithm : %s\n", sa[i].encryptionAlgo);
        printf("Authentication Algo  : %s\n", sa[i].authenticationAlgo);
    }

    printf("\n=============================================\n");
    printf("SA Lookup\n");
    printf("=============================================\n");

    printf("Enter SPI to search: ");
    scanf("%d", &searchSPI);

    for(i = 0; i < n; i++)
    {
        if(sa[i].spi == searchSPI)
        {
            found = 1;

            printf("\nSecurity Association Found\n");
            printf("------------------------------\n");
            printf("SPI                  : %d\n", sa[i].spi);
            printf("Source IP            : %s\n", sa[i].sourceIP);
            printf("Destination IP       : %s\n", sa[i].destinationIP);
            printf("Encryption Algorithm : %s\n", sa[i].encryptionAlgo);
            printf("Authentication Algo  : %s\n", sa[i].authenticationAlgo);
            break;
        }
    }

    if(found == 0)
    {
        printf("\nSecurity Association Not Found.\n");
    }

    return 0;
}
