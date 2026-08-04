#include <stdio.h>
#include <string.h>

struct Email
{
    char sender[100];
    char url[200];
    char attachment[50];
    char headerStatus[10];
};

int main()
{
    struct Email email;
    int phishingScore = 0;

    printf("=====================================================\n");
    printf("        Phishing Email Detection System\n");
    printf("=====================================================\n");

    printf("Enter Sender Email : ");
    scanf("%99s", email.sender);

    printf("Enter URL : ");
    scanf("%199s", email.url);

    printf("Enter Attachment Name : ");
    scanf("%49s", email.attachment);

    printf("Header Match (YES/NO) : ");
    scanf("%9s", email.headerStatus);

    printf("\n=====================================================\n");
    printf("Email Analysis Report\n");
    printf("=====================================================\n");

    printf("Sender      : %s\n", email.sender);
    printf("URL         : %s\n", email.url);
    printf("Attachment  : %s\n", email.attachment);
    printf("Header      : %s\n", email.headerStatus);

    printf("\nSuspicious Factors Found:\n");

    /* Check URL */

    if(strncmp(email.url, "http://", 7) == 0)
    {
        printf("- Insecure URL (HTTP)\n");
        phishingScore++;
    }

    /* Check attachment */

    if(strstr(email.attachment, ".exe") != NULL ||
       strstr(email.attachment, ".bat") != NULL ||
       strstr(email.attachment, ".js") != NULL ||
       strstr(email.attachment, ".vbs") != NULL)
    {
        printf("- Dangerous Attachment\n");
        phishingScore++;
    }

    /* Check Header */

    if(strcmp(email.headerStatus, "NO") == 0)
    {
        printf("- Header Mismatch Detected\n");
        phishingScore++;
    }

    printf("\n=====================================================\n");
    printf("Detection Result\n");
    printf("=====================================================\n");

    printf("Phishing Score : %d\n", phishingScore);

    if(phishingScore >= 2)
    {
        printf("Email Status   : PHISHING EMAIL\n");
    }
    else if(phishingScore == 1)
    {
        printf("Email Status   : SUSPICIOUS EMAIL\n");
    }
    else
    {
        printf("Email Status   : LEGITIMATE EMAIL\n");
    }

    return 0;
}
