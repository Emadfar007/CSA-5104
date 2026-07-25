#include <stdio.h>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int modInverse(int a)
{
    int i;
    a = (a % 26 + 26) % 26;

    for (i = 1; i < 26; i++)
    {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}

int main()
{
    int k[2][2], inv[2][2];
    int det, detInv;
    int p[2], c[2], d[2];
    char text[3];

    printf("Enter 2x2 Key Matrix:\n");
    scanf("%d %d %d %d",
          &k[0][0], &k[0][1],
          &k[1][0], &k[1][1]);

    det = k[0][0] * k[1][1] - k[0][1] * k[1][0];
    det = (det % 26 + 26) % 26;

    if (gcd(det, 26) != 1)
    {
        printf("Invalid Key Matrix!\n");
        return 0;
    }

    detInv = modInverse(det);

    inv[0][0] = ( k[1][1] * detInv) % 26;
    inv[0][1] = ((-k[0][1] * detInv) % 26 + 26) % 26;
    inv[1][0] = ((-k[1][0] * detInv) % 26 + 26) % 26;
    inv[1][1] = ( k[0][0] * detInv) % 26;

    printf("Enter 2-letter Plaintext (A-Z): ");
    scanf("%s", text);

    p[0] = text[0] - 'A';
    p[1] = text[1] - 'A';

    c[0] = (k[0][0] * p[0] + k[0][1] * p[1]) % 26;
    c[1] = (k[1][0] * p[0] + k[1][1] * p[1]) % 26;

    printf("\nCiphertext: %c%c\n", c[0] + 'A', c[1] + 'A');

    d[0] = (inv[0][0] * c[0] + inv[0][1] * c[1]) % 26;
    d[1] = (inv[1][0] * c[0] + inv[1][1] * c[1]) % 26;

    d[0] = (d[0] + 26) % 26;
    d[1] = (d[1] + 26) % 26;

    printf("Inverse Matrix:\n");
    printf("%d %d\n", inv[0][0], inv[0][1]);
    printf("%d %d\n", inv[1][0], inv[1][1]);

    printf("Decrypted Text: %c%c\n", d[0] + 'A', d[1] + 'A');

    return 0;
}
