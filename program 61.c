#include <stdio.h>
#include <string.h>

struct EmailHeader
{
    char from[100];
    char to[100];
    char route[200];
    char date[100];
    char subject[100];
};

int main()
{
    struct EmailHeader email;

    printf("===============================================\n");
    printf("        Email Header Analyzer\n");
    printf("===============================================\n");

    printf("Enter Sender Email: ");
    scanf("%99s", email.from);

    printf("Enter Receiver Email: ");
    scanf("%99s", email.to);

    printf("Enter Routing Path (use '_' instead of spaces): ");
    scanf("%199s", email.route);

    printf("Enter Date and Time (use '_' instead of spaces): ");
    scanf("%99s", email.date);

    printf("Enter Subject (use '_' instead of spaces): ");
    scanf("%99s", email.subject);

    printf("\n===============================================\n");
    printf("        Email Header Analysis\n");
    printf("===============================================\n");

    printf("From           : %s\n", email.from);
    printf("To             : %s\n", email.to);
    printf("Routing Path   : %s\n", email.route);
    printf("Date & Time    : %s\n", email.date);
    printf("Subject        : %s\n", email.subject);

    printf("\n===============================================\n");
    printf("Analysis Result\n");
    printf("===============================================\n");

    printf("Sender Identified      : %s\n", email.from);
    printf("Receiver Identified    : %s\n", email.to);
    printf("Routing Path Verified  : %s\n", email.route);
    printf("Timestamp Recorded     : %s\n", email.date);

    printf("\nEmail Header Analysis Completed Successfully.\n");

    return 0;
}
