#include <stdio.h>
#include <string.h>

unsigned long hash(char text[])
{
    unsigned long h = 5381;
    int i;

    for (i = 0; text[i] != '\0'; i++)
        h = ((h << 5) + h) + text[i];

    return h;
}

int main()
{
    char order[200];
    char payment[200];

    unsigned long orderHash;
    unsigned long paymentHash;
    unsigned long dualSignature;
    unsigned long verifySignature;

    printf("========================================\n");
    printf("       SET DUAL-SIGNATURE SIMULATION\n");
    printf("========================================\n");

    printf("\nEnter Order Information: ");
    fgets(order, sizeof(order), stdin);
    order[strcspn(order, "\n")] = '\0';

    printf("Enter Payment Information: ");
    fgets(payment, sizeof(payment), stdin);
    payment[strcspn(payment, "\n")] = '\0';

    /* Generate hashes */
    orderHash = hash(order);
    paymentHash = hash(payment);

    /* Generate dual signature */
    dualSignature = orderHash ^ paymentHash;

    printf("\nOrder Hash   : %lu", orderHash);
    printf("\nPayment Hash : %lu", paymentHash);

    printf("\nDual Signature: %lu", dualSignature);

    /* Verify */
    verifySignature = hash(order) ^ hash(payment);

    printf("\n\nVerification Signature: %lu", verifySignature);

    if (dualSignature == verifySignature)
        printf("\n\nDual Signature: VALID");
    else
        printf("\n\nDual Signature: INVALID");

    printf("\n\n========================================\n");

    return 0;
}
