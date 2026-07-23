/*
 * Program 5: Security Risk Level Calculator
 * Aim: To calculate the security risk level.
 *
 * Risk = Likelihood x Impact   (each ranges from 1 to 5, so Risk ranges 1-25)
 *
 * Risk Level classification used here:
 *  1  - 6   : Low Risk
 *  7  - 14  : Medium Risk
 *  15 - 25  : High Risk
 */

#include <stdio.h>

int main() {
    int likelihood, impact, risk;

    printf("Likelihood : ");
    scanf("%d", &likelihood);
    printf("Impact : ");
    scanf("%d", &impact);

    risk = likelihood * impact;

    printf("Risk Score : %d\n", risk);

    if (risk <= 6) {
        printf("Risk Level : Low\n");
    } else if (risk <= 14) {
        printf("Risk Level : Medium\n");
    } else {
        printf("Risk Level : High\n");
    }

    return 0;
}
