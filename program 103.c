#include <stdio.h>
#include <string.h>

int main()
{
    char filename[100];
    char location[100];
    char behavior[100];

    int score = 0;

    printf("========================================\n");
    printf("        TROJAN DETECTION SIMULATION\n");
    printf("========================================\n");

    printf("\nEnter file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    printf("Enter file location: ");
    fgets(location, sizeof(location), stdin);
    location[strcspn(location, "\n")] = '\0';

    printf("Enter process behavior: ");
    fgets(behavior, sizeof(behavior), stdin);
    behavior[strcspn(behavior, "\n")] = '\0';

    /* Check suspicious file extension */
    if (strstr(filename, ".exe") != NULL ||
        strstr(filename, ".bat") != NULL ||
        strstr(filename, ".scr") != NULL)
    {
        score++;
        printf("\nSuspicious file extension detected.");
    }

    /* Check suspicious location */
    if (strstr(location, "Temp") != NULL ||
        strstr(location, "temp") != NULL)
    {
        score++;
        printf("\nSuspicious file location detected.");
    }

    /* Check suspicious behavior */
    if (strstr(behavior, "unknown") != NULL ||
        strstr(behavior, "hidden") != NULL ||
        strstr(behavior, "startup") != NULL)
    {
        score++;
        printf("\nSuspicious process behavior detected.");
    }

    printf("\n\n========================================\n");
    printf("Suspicion Score: %d / 3\n", score);

    if (score >= 2)
        printf("Result: POSSIBLE TROJAN DETECTED\n");
    else
        printf("Result: NO TROJAN DETECTED\n");

    printf("========================================\n");

    return 0;
}
