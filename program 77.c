#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define ROTL(x,n) (((x) << (n)) | ((x) >> (32 - (n))))

void sha1(const unsigned char *msg, int len, unsigned char hash[20])
{
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    unsigned char data[128];
    uint32_t w[80];
    uint32_t a, b, c, d, e, f, k, temp;
    int newLen, i, j;

    newLen = len + 1;

    while (newLen % 64 != 56)
        newLen++;

    memset(data, 0, sizeof(data));
    memcpy(data, msg, len);

    data[len] = 0x80;

    uint64_t bitLen = (uint64_t)len * 8;

    for (i = 0; i < 8; i++)
        data[newLen + 7 - i] = (bitLen >> (i * 8)) & 0xFF;

    for (i = 0; i < newLen + 8; i += 64)
    {
        for (j = 0; j < 16; j++)
        {
            w[j] =
                ((uint32_t)data[i + j * 4] << 24) |
                ((uint32_t)data[i + j * 4 + 1] << 16) |
                ((uint32_t)data[i + j * 4 + 2] << 8) |
                ((uint32_t)data[i + j * 4 + 3]);
        }

        for (j = 16; j < 80; j++)
            w[j] = ROTL(w[j-3] ^ w[j-8] ^ w[j-14] ^ w[j-16], 1);

        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;

        for (j = 0; j < 80; j++)
        {
            if (j < 20)
            {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (j < 40)
            {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (j < 60)
            {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else
            {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            temp = ROTL(a, 5) + f + e + k + w[j];

            e = d;
            d = c;
            c = ROTL(b, 30);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    hash[0] = h0 >> 24;
    hash[1] = h0 >> 16;
    hash[2] = h0 >> 8;
    hash[3] = h0;

    hash[4] = h1 >> 24;
    hash[5] = h1 >> 16;
    hash[6] = h1 >> 8;
    hash[7] = h1;

    hash[8] = h2 >> 24;
    hash[9] = h2 >> 16;
    hash[10] = h2 >> 8;
    hash[11] = h2;

    hash[12] = h3 >> 24;
    hash[13] = h3 >> 16;
    hash[14] = h3 >> 8;
    hash[15] = h3;

    hash[16] = h4 >> 24;
    hash[17] = h4 >> 16;
    hash[18] = h4 >> 8;
    hash[19] = h4;
}

void printHash(unsigned char hash[20])
{
    int i;

    for (i = 0; i < 20; i++)
        printf("%02x", hash[i]);

    printf("\n");
}

int main()
{
    char text[1000];
    char modified[1000];

    unsigned char hash1[20];
    unsigned char hash2[20];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    text[strcspn(text, "\n")] = '\0';

    sha1((unsigned char *)text, strlen(text), hash1);

    strcpy(modified, text);

    /* Modify one character */
    if (modified[0] != '\0')
        modified[0]++;

    sha1((unsigned char *)modified, strlen(modified), hash2);

    printf("\nOriginal Text : %s", text);
    printf("\nSHA-1 Hash    : ");
    printHash(hash1);

    printf("\nModified Text : %s", modified);
    printf("\nSHA-1 Hash    : ");
    printHash(hash2);

    if (memcmp(hash1, hash2, 20) != 0)
        printf("\nVerification: Hash values are different.\n");
    else
        printf("\nVerification: Hash values are same.\n");

    return 0;
}
