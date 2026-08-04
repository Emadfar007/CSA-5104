#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct IKE
{
    char initiatorIP[20];
    char responderIP[20];
    char initiatorKey[50];
    char responderKey[50];
    int sessionID;
};

int main()
{
    struct IKE ike;

    srand(time(NULL));

    printf("=============================================\n");
    printf(" Internet Key Exchange (IKE) Simulation\n");
    printf("=============================================\n");

    printf("Enter Initiator IP Address : ");
    scanf("%19s", ike.initiatorIP);

    printf("Enter Responder IP Address : ");
    scanf("%19s", ike.responderIP);

    printf("Enter Initiator Pre-Shared Key : ");
    scanf("%49s", ike.initiatorKey);

    printf("Enter Responder Pre-Shared Key : ");
    scanf("%49s", ike.responderKey);

    printf("\n=============================================\n");
    printf("IKE Phase 1: Authentication\n");
    printf("=============================================\n");

    if(strcmp(ike.initiatorKey, ike.responderKey) == 0)
    {
        ike.sessionID = rand() % 9000 + 1000;

        printf("Authentication Successful.\n");

        printf("\n=============================================\n");
        printf("IKE Phase 2: Secure Session Establishment\n");
        printf("=============================================\n");

        printf("Session ID        : %d\n", ike.sessionID);
        printf("Initiator IP      : %s\n", ike.initiatorIP);
        printf("Responder IP      : %s\n", ike.responderIP);

        printf("\nSecurity Association Created Successfully.\n");
        printf("Secure Communication Established.\n");
    }
    else
    {
        printf("Authentication Failed!\n");
        printf("Pre-Shared Keys do not match.\n");
        printf("Session Establishment Failed.\n");
    }

    return 0;
}
