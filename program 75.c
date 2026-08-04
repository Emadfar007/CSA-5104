#include <stdio.h>
#include <string.h>

struct Email
{
    char sender[100];
    char subject[200];
    char content[500];
    char url[200];
    char attachment[50];
    char headerStatus[10];
    float mlProbability;
};

int main()
{
    struct Email email;

    char spamWords[10][20] =
    {
        "FREE",
        "WIN",
        "MONEY",
        "CLICK",
        "PRIZE",
        "BONUS",
        "URGENT",
        "OFFER",
        "LOTTERY",
        "CASH"
    };

    int i;
    int score = 0;

    printf("=====================================================\n");
    printf(" Comprehensive Secure Email Analyzer\n");
    printf("=====================================================\n");

    printf("Enter Sender Email : ");
    scanf("%99s", email.sender);

    getchar();

    printf("Enter Email Subject : ");
    fgets(email.subject, sizeof(email.subject), stdin);

    printf("Enter Email Content : ");
    fgets(email.content, sizeof(email.content), stdin);

    printf("Enter URL : ");
    scanf("%199s", email.url);

    printf("Enter Attachment Name : ");
    scanf("%49s", email.attachment);

    printf("Header Match (YES/NO) : ");
    scanf("%9s", email.headerStatus);

    printf("Enter ML Spam Probability (0-100): ");
    scanf("%f", &email.mlProbability);

    printf("\n=====================================================\n");
    printf("Email Analysis Report\n");
    printf("=====================================================\n");

    printf("Sender      : %s\n", email.sender);
    printf("Subject     : %s", email.subject);
    printf("Content     : %s", email.content);
    printf("URL         : %s\n", email.url);
    printf("Attachment  : %s\n", email.attachment);

    printf("\nDetected Issues:\n");

    /* Spam Keyword Detection */

    for(i = 0; i < 10; i++)
    {
        if(strstr(email.subject, spamWords[i]) != NULL ||
           strstr(email.content, spamWords[i]) != NULL)
        {
            printf("- Spam Keyword : %s\n", spamWords[i]);
            score++;
        }
    }

    /* URL Check */

    if(strncmp(email.url, "http://", 7) == 0)
    {
        printf("- Insecure URL Detected\n");
        score++;
    }

    /* Attachment Check */

    if(strstr(email.attachment, ".exe") != NULL ||
       strstr(email.attachment, ".bat") != NULL ||
       strstr(email.attachment, ".js") != NULL ||
       strstr(email.attachment, ".vbs") != NULL)
    {
        printf("- Dangerous Attachment\n");
        score++;
    }

    /* Header Check */

    if(strcmp(email.headerStatus, "NO") == 0)
    {
        printf("- Header Mismatch\n");
        score++;
    }

    /* ML Simulation */

    if(email.mlProbability >= 70)
    {
        printf("- Machine Learning Predicts Spam (%.2f%%)\n",
               email.mlProbability);
        score++;
    }

    printf("\n=====================================================\n");
    printf("Final Classification\n");
    printf("=====================================================\n");

    printf("Risk Score : %d\n", score);

    if(score >= 4)
    {
        printf("Email Type : PHISHING EMAIL\n");
    }
    else if(score >= 2)
    {
        printf("Email Type : SPAM EMAIL\n");
    }
    else
    {
        printf("Email Type : LEGITIMATE EMAIL\n");
    }

    return 0;
}
