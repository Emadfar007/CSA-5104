#include <stdio.h>

#define MAX_PACKETS 100

int main()
{
    int receivedSeq[MAX_PACKETS];
    int totalPackets;
    int highestSeq = 0;
    int i, j;
    int seq;
    int replay;

    printf("=============================================\n");
    printf(" IPSec Anti-Replay Protection Simulation\n");
    printf("=============================================\n");

    printf("Enter Number of Incoming Packets: ");
    scanf("%d", &totalPackets);

    if(totalPackets > MAX_PACKETS)
    {
        printf("Maximum %d packets allowed.\n", MAX_PACKETS);
        return 0;
    }

    for(i = 0; i < totalPackets; i++)
    {
        printf("\nEnter Sequence Number for Packet %d: ", i + 1);
        scanf("%d", &seq);

        replay = 0;

        /* Check for duplicate sequence number */
        for(j = 0; j < i; j++)
        {
            if(receivedSeq[j] == seq)
            {
                replay = 1;
                break;
            }
        }

        if(replay)
        {
            printf("Packet %d Rejected - Replay Attack Detected!\n", i + 1);
        }
        else if(seq < highestSeq)
        {
            printf("Packet %d Rejected - Old Packet Detected!\n", i + 1);
        }
        else
        {
            receivedSeq[i] = seq;

            if(seq > highestSeq)
                highestSeq = seq;

            printf("Packet %d Accepted.\n", i + 1);
            printf("Current Highest Sequence Number: %d\n", highestSeq);
        }
    }

    printf("\n=============================================\n");
    printf("Communication Summary\n");
    printf("=============================================\n");
    printf("Highest Sequence Number Received: %d\n", highestSeq);
    printf("Anti-Replay Protection Completed Successfully.\n");

    return 0;
}
