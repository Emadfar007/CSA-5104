#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    char filename[100];
    char line[500];

    char *patterns[] = {
        "VIRUS",
        "MALWARE",
        "TROJAN",
        "SUSPICIOUS_CODE"
    };

    int patternCount = 4;
    int found = 0;
    int i;

    printf("========================================\n");
    printf("       VIRUS SIGNATURE SCANNER\n");
    printf("========================================\n");

    printf("\nEnter file name: ");
    scanf("%99s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("\nError: Cannot open file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        for (i = 0; i < patternCount; i++)
        {
            if (strstr(line, patterns[i]) != NULL)
            {
                printf("\nSuspicious pattern found: %s", patterns[i]);
                found = 1;
            }
        }
    }

    fclose(fp);

    printf("\n\n========================================\n");

    if (found)
        printf("Result: Suspicious file detected!\n");
    else
        printf("Result: No known virus pattern detected.\n");

    printf("========================================\n");

    return 0;
}
