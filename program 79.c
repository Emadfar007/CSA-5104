#include <stdio.h>
#include <string.h>

typedef unsigned long long ULL;

#define ROTR(x,n) ((x >> n) | (x << (64 - n)))

#define CH(x,y,z)  ((x & y) ^ (~x & z))
#define MAJ(x,y,z) ((x & y) ^ (x & z) ^ (y & z))

#define EP0(x) (ROTR(x,28) ^ ROTR(x,34) ^ ROTR(x,39))
#define EP1(x) (ROTR(x,14) ^ ROTR(x,18) ^ ROTR(x,41))

#define SIG0(x) (ROTR(x,1) ^ ROTR(x,8) ^ (x >> 7))
#define SIG1(x) (ROTR(x,19) ^ ROTR(x,61) ^ (x >> 6))

ULL K[80] = {
0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL,
0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL,
0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL,
0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL,
0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL,
0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL,
0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
0xd192e819d6ef5218ULL, 0xd69906245565a910ULL,
0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL,
0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL,
0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
0x28db77f523047d84ULL, 0x32caab7b40c72493ULL,
0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
};

void sha512(char input[], int len, ULL h[])
{
    unsigned char data[256];
    ULL w[80];
    ULL a,b,c,d,e,f,g,hh;
    ULL t1,t2;
    ULL bitLen;
    int newLen;
    int i,j;

    newLen = len + 1;

    while ((newLen % 128) != 112)
        newLen++;

    memset(data, 0, sizeof(data));
    memcpy(data, input, len);

    data[len] = 0x80;

    bitLen = (ULL)len * 8;

    /*
       Store message length as 128-bit big-endian.
       For our input size, upper 64 bits are zero.
    */
    for (i = 0; i < 8; i++)
        data[newLen + 15 - i] =
            (unsigned char)(bitLen >> (i * 8));

    for (i = 0; i < newLen + 16; i += 128)
    {
        for (j = 0; j < 16; j++)
        {
            w[j] =
                ((ULL)data[i + j*8] << 56) |
                ((ULL)data[i + j*8 + 1] << 48) |
                ((ULL)data[i + j*8 + 2] << 40) |
                ((ULL)data[i + j*8 + 3] << 32) |
                ((ULL)data[i + j*8 + 4] << 24) |
                ((ULL)data[i + j*8 + 5] << 16) |
                ((ULL)data[i + j*8 + 6] << 8) |
                ((ULL)data[i + j*8 + 7]);
        }

        for (j = 16; j < 80; j++)
            w[j] = SIG1(w[j-2]) + w[j-7]
                 + SIG0(w[j-15]) + w[j-16];

        a = h[0];
        b = h[1];
        c = h[2];
        d = h[3];
        e = h[4];
        f = h[5];
        g = h[6];
        hh = h[7];

        for (j = 0; j < 80; j++)
        {
            t1 = hh + EP1(e) + CH(e,f,g)
                 + K[j] + w[j];

            t2 = EP0(a) + MAJ(a,b,c);

            hh = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += hh;
    }
}

void printHash(ULL h[], int count)
{
    int i;

    for (i = 0; i < count; i++)
        printf("%016llx", h[i]);

    printf("\n");
}

int main()
{
    char input[100];
    ULL sha384[8];
    ULL sha512Hash[8];

    printf("Enter message: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    /* SHA-512 initial values */

    sha512Hash[0] = 0x6a09e667f3bcc908ULL;
    sha512Hash[1] = 0xbb67ae8584caa73bULL;
    sha512Hash[2] = 0x3c6ef372fe94f82bULL;
    sha512Hash[3] = 0xa54ff53a5f1d36f1ULL;
    sha512Hash[4] = 0x510e527fade682d1ULL;
    sha512Hash[5] = 0x9b05688c2b3e6c1fULL;
    sha512Hash[6] = 0x1f83d9abfb41bd6bULL;
    sha512Hash[7] = 0x5be0cd19137e2179ULL;

    /* SHA-384 initial values */

    sha384[0] = 0xcbbb9d5dc1059ed8ULL;
    sha384[1] = 0x629a292a367cd507ULL;
    sha384[2] = 0x9159015a3070dd17ULL;
    sha384[3] = 0x152fecd8f70e5939ULL;
    sha384[4] = 0x67332667ffc00b31ULL;
    sha384[5] = 0x8eb44a8768581511ULL;
    sha384[6] = 0xdb0c2e0d64f98fa7ULL;
    sha384[7] = 0x47b5481dbefa4fa4ULL;

    sha512(input, strlen(input), sha512Hash);
    sha512(input, strlen(input), sha384);

    printf("\nInput: %s\n", input);

    printf("\nSHA-384 Hash: ");
    printHash(sha384, 6);

    printf("Digest Size: 384 bits (48 bytes)\n");

    printf("\nSHA-512 Hash: ");
    printHash(sha512Hash, 8);

    printf("Digest Size: 512 bits (64 bytes)\n");

    printf("\nComparison:\n");
    printf("SHA-384 = 384 bits = 48 bytes = 96 hexadecimal characters\n");
    printf("SHA-512 = 512 bits = 64 bytes = 128 hexadecimal characters\n");

    return 0;
}
