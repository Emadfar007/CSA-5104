#include <stdio.h>
#include <string.h>

struct Rule
{
    char ip[20];
    int port;
    int action;   /* 0 = BLOCK, 1 = ALLOW */
};

int main()
{
    struct Rule rules[3] =
    {
        {"192.168.1.10", 80, 0},
        {"10.0.0.5", 22, 0},
        {"192.168.1.20", 443, 1}
    };

    char sourceIP[20];
    int port;
    int i;
    int found = 0;
    int action = 1;

    printf("========================================\n");
    printf("       PACKET FILTERING FIREWALL\n");
    printf("========================================\n");

    printf("\nFirewall Rules:\n");
    printf("192.168.1.10 : Port 80  : BLOCK\n");
    printf("10.0.0.5     : Port 22  : BLOCK\n");
    printf("192.168.1.20 : Port 443 : ALLOW\n");

    printf("\nEnter source IP address: ");
    scanf("%19s", sourceIP);

    printf("Enter destination port: ");
    scanf("%d", &port);

    for (i = 0; i < 3; i++)
    {
        if (strcmp(sourceIP, rules[i].ip) == 0 &&
            port == rules[i].port)
        {
            found = 1;
            action = rules[i].action;
            break;
        }
    }

    printf("\n========================================\n");
    printf("          FIREWALL DECISION\n");
    printf("========================================\n");

    printf("\nSource IP : %s", sourceIP);
    printf("\nPort      : %d", port);

    if (found && action == 0)
        printf("\nDecision  : BLOCKED\n");
    else
        printf("\nDecision  : ALLOWED\n");

    printf("========================================\n");

    return 0;
}
