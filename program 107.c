#include <stdio.h>
#include <string.h>

int main()
{
    char method[20];
    char url[200];

    char *blocked[] = {
        "malware",
        "phishing",
        "blocked.com",
        "dangerous"
    };

    int count = 4;
    int blockedRequest = 0;
    int i;

    printf("========================================\n");
    printf("      APPLICATION LEVEL FIREWALL\n");
    printf("========================================\n");

    printf("\nEnter HTTP method (GET/POST): ");
    scanf("%19s", method);

    printf("Enter URL: ");
    scanf("%199s", url);

    /* Check HTTP method */
    if (strcmp(method, "GET") != 0 &&
        strcmp(method, "POST") != 0)
    {
        printf("\nHTTP method not allowed.\n");
        printf("Decision: BLOCKED\n");
        return 0;
    }

    /* Check blocked URL patterns */
    for (i = 0; i < count; i++)
    {
        if (strstr(url, blocked[i]) != NULL)
        {
            blockedRequest = 1;
            break;
        }
    }

    printf("\n========================================\n");
    printf("          PROXY FIREWALL\n");
    printf("========================================\n");

    printf("\nHTTP Method: %s", method);
    printf("\nURL        : %s", url);

    if (blockedRequest)
    {
        printf("\nDecision   : BLOCKED");
        printf("\nReason     : Suspicious URL detected.");
    }
    else
    {
        printf("\nDecision   : ALLOWED");
        printf("\nReason     : Request passed firewall rules.");
    }

    printf("\n========================================\n");

    return 0;
}
