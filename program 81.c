#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ROTR(x,n) ((x >> n) | (x << (32-n)))
#define CH(x,y,z) ((x & y) ^ (~x & z))
#define MAJ(x,y,z) ((x & y) ^ (x & z) ^ (y & z))
#define E0(x) (ROTR(x,2) ^ ROTR(x,13) ^ ROTR(x,22))
#define E1(x) (ROTR(x,6) ^ ROTR(x,11) ^ ROTR(x,25))
#define S0(x) (ROTR(x,7) ^ ROTR(x,18) ^ (x >> 3))
#define S1(x) (ROTR(x,17) ^ ROTR(x,19) ^ (x >> 10))

uint32_t K[64] = {
0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,
0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,
0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,
0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,
0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,
0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

typedef struct {
    uint32_t h[8];
    unsigned char buffer[64];
    uint64_t length;
    int bufferLen;
} SHA256_CTX;

void sha256_init(SHA256_CTX *ctx)
{
    ctx->h[0] = 0x6a09e667;
    ctx->h[1] = 0xbb67ae85;
    ctx->h[2] = 0x3c6ef372;
    ctx->h[3] = 0xa54ff53a;
    ctx->h[4] = 0x510e527f;
    ctx->h[5] = 0x9b05688c;
    ctx->h[6] = 0x1f83d9ab;
    ctx->h[7] = 0x5be0cd19;

    ctx->length = 0;
    ctx->bufferLen = 0;
}

void sha256_transform(SHA256_CTX *ctx, unsigned char data[])
{
    uint32_t w[64];
    uint32_t a,b,c,d,e,f,g,h;
    uint32_t t1,t2;
    int i;

    for(i=0;i<16;i++)
    {
        w[i] =
            ((uint32_t)data[i*4] << 24) |
            ((uint32_t)data[i*4+1] << 16) |
            ((uint32_t)data[i*4+2] << 8) |
            data[i*4+3];
    }

    for(i=16;i<64;i++)
        w[i] = S1(w[i-2]) + w[i-7]
             + S0(w[i-15]) + w[i-16];

    a=ctx->h[0];
    b=ctx->h[1];
    c=ctx->h[2];
    d=ctx->h[3];
    e=ctx->h[4];
    f=ctx->h[5];
    g=ctx->h[6];
    h=ctx->h[7];

    for(i=0;i<64;i++)
    {
        t1 = h + E1(e) + CH(e,f,g) + K[i] + w[i];
        t2 = E0(a) + MAJ(a,b,c);

        h=g;
        g=f;
        f=e;
        e=d+t1;
        d=c;
        c=b;
        b=a;
        a=t1+t2;
    }

    ctx->h[0] += a;
    ctx->h[1] += b;
    ctx->h[2] += c;
    ctx->h[3] += d;
    ctx->h[4] += e;
    ctx->h[5] += f;
    ctx->h[6] += g;
    ctx->h[7] += h;
}

void sha256_update(SHA256_CTX *ctx, unsigned char data[], int len)
{
    int i;

    for(i=0;i<len;i++)
    {
        ctx->buffer[ctx->bufferLen++] = data[i];
        ctx->length += 8;

        if(ctx->bufferLen == 64)
        {
            sha256_transform(ctx,ctx->buffer);
            ctx->bufferLen = 0;
        }
    }
}

void sha256_final(SHA256_CTX *ctx, unsigned char hash[32])
{
    int i;

    ctx->buffer[ctx->bufferLen++] = 0x80;

    while(ctx->bufferLen != 56)
    {
        if(ctx->bufferLen == 64)
        {
            sha256_transform(ctx,ctx->buffer);
            ctx->bufferLen = 0;
        }

        ctx->buffer[ctx->bufferLen++] = 0;
    }

    for(i=0;i<8;i++)
        ctx->buffer[56+i] =
            (unsigned char)(ctx->length >> (56-i*8));

    sha256_transform(ctx,ctx->buffer);

    for(i=0;i<8;i++)
    {
        hash[i*4]   = ctx->h[i] >> 24;
        hash[i*4+1] = ctx->h[i] >> 16;
        hash[i*4+2] = ctx->h[i] >> 8;
        hash[i*4+3] = ctx->h[i];
    }
}

int calculateHash(char *filename, unsigned char hash[32])
{
    FILE *fp;
    SHA256_CTX ctx;
    unsigned char buffer[1024];
    int bytes;

    fp = fopen(filename,"rb");

    if(fp == NULL)
        return 0;

    sha256_init(&ctx);

    while((bytes=fread(buffer,1,1024,fp)) > 0)
        sha256_update(&ctx,buffer,bytes);

    fclose(fp);

    sha256_final(&ctx,hash);

    return 1;
}

void printHash(unsigned char hash[32])
{
    int i;

    for(i=0;i<32;i++)
        printf("%02x",hash[i]);

    printf("\n");
}

int compareHash(unsigned char h1[32], unsigned char h2[32])
{
    int i;

    for(i=0;i<32;i++)
    {
        if(h1[i] != h2[i])
            return 0;
    }

    return 1;
}

int main()
{
    char filename[100];
    unsigned char hash1[32];
    unsigned char hash2[32];

    printf("Enter file name: ");
    scanf("%99s",filename);

    /* First hash */
    if(!calculateHash(filename,hash1))
    {
        printf("Cannot open file!\n");
        return 1;
    }

    printf("\nOriginal SHA-256 Hash:\n");
    printHash(hash1);

    printf("\nNow modify the file and save it.\n");
    printf("Press ENTER after modifying the file...");

    getchar();
    getchar();

    /* Second hash */
    if(!calculateHash(filename,hash2))
    {
        printf("Cannot open file!\n");
        return 1;
    }

    printf("\nNew SHA-256 Hash:\n");
    printHash(hash2);

    printf("\nIntegrity Check:\n");

    if(compareHash(hash1,hash2))
        printf("File NOT altered. Integrity verified.\n");
    else
        printf("File ALTERED! Integrity verification failed.\n");

    return 0;
}
