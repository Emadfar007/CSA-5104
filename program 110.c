#include <stdio.h>
#include <string.h>

int main()
{
    char srcIP[20];
    char destIP[20];
    char protocol[20];
    int port;

    printf("========================================\n");
    printf("       NETWORK TRAFFIC ANALYZER\n");
    printf("========================================\n");

    printf("\nEnter Source IP: ");
    scanf("%19s", srcIP);

    printf("Enter Destination IP: ");
    scanf("%19s", destIP);

    printf("Enter Protocol (TCP/UDP): ");
    scanf("%19s", protocol);

    printf("Enter Destination Port: ");
    scanf("%d", &port);

    printf("\n========================================\n");
    printf("          TRAFFIC ANALYSIS\n");
    printf("========================================\n");

    printf("\nSource IP      : %s", srcIP);
    printf("\nDestination IP : %s", destIP);
    printf("\nProtocol       : %s", protocol);
    printf("\nPort           : %d", port);

    printf("\n\nApplication: ");

    if (port == 80)
    {
        printf("HTTP");
    }
    else if (port == 443)
    {
        printf("HTTPS / TLS");
    }
    else if (port == 53)
    {
        printf("DNS");
    }
    else if (port == 22)
    {
        printf("SSH");
    }
    else if (port == 21)
    {
        printf("FTP");
    }
    else
    {
        printf("Unknown");
    }

    printf("\n\nSecurity Analysis:\n");

    if (port == 23)
    {
        printf("WARNING: Telnet traffic detected.\n");
        printf("Possible security risk.\n");
    }
    else if (port == 21)
    {
        printf("WARNING: FTP traffic detected.\n");
        printf("FTP may transmit data without encryption.\n");
    }
    else if (port == 443)
    {
        printf("HTTPS/TLS traffic detected.\n");
        printf("Encrypted communication expected.\n");
    }
    else if (port == 80)
    {
        printf("HTTP traffic detected.\n");
        printf("Traffic is not encrypted by HTTP itself.\n");
    }
    else
    {
        printf("No known threat detected.\n");
    }

    printf("\n========================================\n");

    return 0;
}
