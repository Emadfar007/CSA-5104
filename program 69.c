#include <stdio.h>

void displayPGP()
{
    printf("\n=========================================\n");
    printf(" Pretty Good Privacy (PGP)\n");
    printf("=========================================\n");

    printf("Encryption           : Public Key Encryption\n");
    printf("Authentication       : Digital Signature\n");
    printf("Certificate          : User-managed Trust Model\n");
    printf("Key Management       : Web of Trust\n");
    printf("Email Security       : High\n");
}

void displaySMIME()
{
    printf("\n=========================================\n");
    printf(" Secure/Multipurpose Internet Mail Extensions (S/MIME)\n");
    printf("=========================================\n");

    printf("Encryption           : Public Key Encryption\n");
    printf("Authentication       : Digital Signature\n");
    printf("Certificate          : X.509 Certificates\n");
    printf("Key Management       : Certificate Authority (CA)\n");
    printf("Email Security       : High\n");
}

void compareBoth()
{
    printf("\n==========================================================================\n");
    printf("                     PGP vs S/MIME Comparison\n");
    printf("==========================================================================\n");

    printf("%-25s %-20s %-20s\n",
           "Feature",
           "PGP",
           "S/MIME");

    printf("--------------------------------------------------------------------------\n");

    printf("%-25s %-20s %-20s\n",
           "Encryption",
           "Public Key",
           "Public Key");

    printf("%-25s %-20s %-20s\n",
           "Authentication",
           "Digital Signature",
           "Digital Signature");

    printf("%-25s %-20s %-20s\n",
           "Certificate",
           "Web of Trust",
           "X.509 Certificate");

    printf("%-25s %-20s %-20s\n",
           "Key Management",
           "User Managed",
           "Certificate Authority");

    printf("%-25s %-20s %-20s\n",
           "Trust Model",
           "Decentralized",
           "Centralized");

    printf("%-25s %-20s %-20s\n",
           "Common Usage",
           "Personal Emails",
           "Enterprise Emails");

    printf("==========================================================================\n");
}

int main()
{
    int choice;

    printf("========================================================\n");
    printf("       PGP and S/MIME Comparison Tool\n");
    printf("========================================================\n");

    printf("\n1. View PGP Details\n");
    printf("2. View S/MIME Details\n");
    printf("3. Compare PGP and S/MIME\n");

    printf("\nEnter Your Choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            displayPGP();
            break;

        case 2:
            displaySMIME();
            break;

        case 3:
            compareBoth();
            break;

        default:
            printf("\nInvalid Choice!\n");
    }

    return 0;
}
