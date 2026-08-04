#include <stdio.h>
#include <string.h>

struct EmailAuthentication
{
    char from[100];
    char to[100];
    char spf[20];
    char dkim[20];
    char dmarc[20];
};

int main()
{
    struct EmailAuthentication email;

    printf("=====================================================\n");
    printf(" Email Header Authentication Field Parser\n");
    printf("=====================================================\n");

    printf("Enter Sender Email Address      : ");
    scanf("%99s", email.from);

    printf("Enter Receiver Email Address    : ");
    scanf("%99s", email.to);

    printf("Enter SPF Result (PASS/FAIL)    : ");
    scanf("%19s", email.spf);

    printf("Enter DKIM Result (PASS/FAIL)   : ");
    scanf("%19s", email.dkim);

    printf("Enter DMARC Result (PASS/FAIL)  : ");
    scanf("%19s", email.dmarc);

    printf("\n=====================================================\n");
    printf(" Extracted Authentication Fields\n");
    printf("=====================================================\n");

    printf("From           : %s\n", email.from);
    printf("To             : %s\n", email.to);
    printf("SPF Status     : %s\n", email.spf);
    printf("DKIM Status    : %s\n", email.dkim);
    printf("DMARC Status   : %s\n", email.dmarc);

    printf("\n=====================================================\n");
    printf(" Authentication Result\n");
    printf("=====================================================\n");

    if(strcmp(email.spf, "PASS") == 0 &&
       strcmp(email.dkim, "PASS") == 0 &&
       strcmp(email.dmarc, "PASS") == 0)
    {
        printf("Email Authentication : SUCCESSFUL\n");
        printf("Status               : Legitimate Email\n");
    }
    else
    {
        printf("Email Authentication : FAILED\n");
        printf("Status               : Suspicious Email\n");
    }

    return 0;
}
