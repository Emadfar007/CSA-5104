#include <stdio.h>

long long powerMod(long long base, long long exponent, long long mod)
{
    long long result = 1;

    while (exponent > 0)
    {
        result = (result * base) % mod;
        exponent--;
    }

    return result;
}

int main()
{
    long long p, g;
    long long a, b;
    long long A, B;
    long long keyA, keyB;

    printf("Enter prime number (p): ");
    scanf("%lld", &p);

    printf("Enter primitive root (g): ");
    scanf("%lld", &g);

    printf("Enter private key of User A: ");
    scanf("%lld", &a);

    printf("Enter private key of User B: ");
    scanf("%lld", &b);

    /* Generate public keys */
    A = powerMod(g, a, p);
    B = powerMod(g, b, p);

    /* Generate shared secret keys */
    keyA = powerMod(B, a, p);
    keyB = powerMod(A, b, p);

    printf("\nUser A Public Key: %lld", A);
    printf("\nUser B Public Key: %lld", B);

    printf("\n\nUser A Shared Key: %lld", keyA);
    printf("\nUser B Shared Key: %lld", keyB);

    if (keyA == keyB)
        printf("\n\nShared secret key established successfully.\n");
    else
        printf("\n\nKey exchange failed.\n");

    return 0;
}
