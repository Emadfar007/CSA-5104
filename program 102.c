#include <stdio.h>

#define N 6

int main()
{
    int network[N][N] = {
        {0,1,1,0,0,0},
        {1,0,1,1,0,0},
        {1,1,0,0,1,0},
        {0,1,0,0,1,1},
        {0,0,1,1,0,1},
        {0,0,0,1,1,0}
    };

    int infected[N] = {0};
    int newInfected[N];
    int i, j, round;

    /* Initially infect Node 0 */
    infected[0] = 1;

    printf("========================================\n");
    printf("       WORM PROPAGATION SIMULATION\n");
    printf("========================================\n");

    printf("\nInitial infected node: Node 1\n");

    /* Simulate propagation */
    for (round = 1; round <= 3; round++)
    {
        for (i = 0; i < N; i++)
            newInfected[i] = infected[i];

        for (i = 0; i < N; i++)
        {
            if (infected[i] == 1)
            {
                for (j = 0; j < N; j++)
                {
                    if (network[i][j] == 1)
                        newInfected[j] = 1;
                }
            }
        }

        for (i = 0; i < N; i++)
            infected[i] = newInfected[i];

        printf("\nRound %d:", round);

        for (i = 0; i < N; i++)
        {
            if (infected[i])
                printf(" Node %d", i + 1);
        }
    }

    printf("\n\n========================================\n");
    printf("          FINAL NETWORK STATUS\n");
    printf("========================================\n");

    for (i = 0; i < N; i++)
    {
        if (infected[i])
            printf("Node %d : INFECTED\n", i + 1);
        else
            printf("Node %d : SAFE\n", i + 1);
    }

    printf("\n========================================\n");

    return 0;
}
