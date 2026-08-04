#include <stdio.h>
#include <string.h>

int main()
{
    char sender[100];
    char subject[200];
    char content[500];

    char spamWords[10][20] =
    {
        "WIN",
        "FREE",
        "LOTTERY",
        "PRIZE",
        "OFFER",
        "CLICK",
        "MONEY",
        "URGENT",
        "BONUS",
        "CASH"
    };

    int i;
    int spamCount = 0;

    printf("=====================================================\n");
    printf("      Keyword Based Spam Detection System\n");
    printf("=====================================================\n");

    printf("Enter Sender Email : ");
    scanf("%99s", sender);

    getchar();

    printf("Enter Email Subject : ");
    fgets(subject, sizeof(subject), stdin);

    printf("Enter Email Content : ");
    fgets(content, sizeof(content), stdin);

    printf("\n=====================================================\n");
    printf("Email Analysis\n");
    printf("=====================================================\n");

    printf("Sender  : %s\n", sender);
    printf("Subject : %s", subject);
    printf("Content : %s", content);

    printf("\nSpam Keywords Found:\n");

    for(i = 0; i < 10; i++)
    {
        if(strstr(subject, spamWords[i]) != NULL ||
           strstr(content, spamWords[i]) != NULL)
        {
            printf("- %s\n", spamWords[i]);
            spamCount++;
        }
    }

    printf("\n=====================================================\n");
    printf("Detection Result\n");
    printf("=====================================================\n");

    if(spamCount > 0)
    {
        printf("Email Status : SPAM EMAIL\n");
        printf("Spam Score   : %d\n", spamCount);
    }
    else
    {
        printf("Email Status : LEGITIMATE EMAIL\n");
        printf("Spam Score   : 0\n");
    }

    return 0;
}
