#include <stdio.h>

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

long long powerMod(long long base, long long exp, long long mod)
{
    long long result = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp = exp / 2;
    }

    return result;
}

long long findD(long long e, long long phi)
{
    long long d = 1;

    while ((d * e) % phi != 1)
        d++;

    return d;
}

int main()
{
    long long p, q;
    long long n, phi;
    long long e, d;
    long long message;
    long long signature;
    long long verified;

    printf("Enter prime p: ");
    scanf("%lld", &p);

    printf("Enter prime q: ");
    scanf("%lld", &q);

    n = p * q;
    phi = (p - 1) * (q - 1);

    printf("Enter public key e: ");
    scanf("%lld", &e);

    if (gcd(e, phi) != 1)
    {
        printf("Invalid value of e!\n");
        return 0;
    }

    d = findD(e, phi);

    printf("\nPublic Key  : (%lld, %lld)", e, n);
    printf("\nPrivate Key : (%lld, %lld)", d, n);

    printf("\n\nEnter message number less than %lld: ", n);
    scanf("%lld", &message);

    if (message >= n)
    {
        printf("Message must be less than n.\n");
        return 0;
    }

    /* Generate signature using private key */
    signature = powerMod(message, d, n);

    /* Verify signature using public key */
    verified = powerMod(signature, e, n);

    printf("\nOriginal Message : %lld", message);
    printf("\nDigital Signature: %lld", signature);
    printf("\nVerified Message : %lld", verified);

    if (verified == message)
        printf("\n\nDigital Signature is VALID.\n");
    else
        printf("\n\nDigital Signature is INVALID.\n");

    return 0;
}
