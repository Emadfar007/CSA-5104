#include <stdio.h>
#include <string.h>
#include <stdint.h>

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
0xa2bfe8a1,0xa81a664b,0x8cc70208,0x90befffa,
0xa4506ceb,0xbef9a3f7,0xc67178f2,0x84c87814,
0x1e376c08,0x2748774c,0x34b0b5e5,0x391c0cb3,
0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,0x748f82ee,
0x78a5636f,0x8cc70208,0x90befffa,0xa4506ceb,
0xbef9a3f7,0xc67178f2,0x106aa070,0x19a4c116,
0x1e376c08,0x2748774c,0x34b0b5e5,0x391c0cb3,
0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,0x748f82ee,
0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,
0xa4506ceb,0xbef9a3f7,0xc67178f2,0x106aa070
};

/* Correct SHA-256 constants */
uint32_t C[64] = {
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

void sha256(unsigned char data[], int len, unsigned char hash[32])
{
    unsigned char block[128];
    uint32_t w[64], h[8];
    uint32_t a,b,c,d,e,f,g,hh,t1,t2;
    int newLen, i, j;

    h[0]=0x6a09e667;
    h[1]=0xbb67ae85;
    h[2]=0x3c6ef372;
    h[3]=0xa54ff53a;
    h[4]=0x510e527f;
    h[5]=0x9b05688c;
    h[6]=0x1f83d9ab;
    h[7]=0x5be0cd19;

    newLen = len + 1;

    while(newLen % 64 != 56)
        newLen++;

    memset(block,0,sizeof(block));
    memcpy(block,data,len);

    block[len] = 0x80;

    for(i=0;i<8;i++)
        block[newLen+7-i] =
        (unsigned char)(((uint64_t)len*8) >> (8*i));

    for(i=0;i<newLen+8;i+=64)
    {
        for(j=0;j<16;j++)
        {
            w[j] =
            ((uint32_t)block[i+j*4] << 24) |
            ((uint32_t)block[i+j*4+1] << 16) |
            ((uint32_t)block[i+j*4+2] << 8) |
            block[i+j*4+3];
        }

        for(j=16;j<64;j++)
            w[j] = S1(w[j-2]) + w[j-7]
                 + S0(w[j-15]) + w[j-16];

        a=h[0]; b=h[1]; c=h[2]; d=h[3];
        e=h[4]; f=h[5]; g=h[6]; hh=h[7];

        for(j=0;j<64;j++)
        {
            t1 = hh + E1(e) + CH(e,f,g) + C[j] + w[j];
            t2 = E0(a) + MAJ(a,b,c);

            hh=g;
            g=f;
            f=e;
            e=d+t1;
            d=c;
            c=b;
            b=a;
            a=t1+t2;
        }

        h[0]+=a; h[1]+=b; h[2]+=c; h[3]+=d;
        h[4]+=e; h[5]+=f; h[6]+=g; h[7]+=hh;
    }

    for(i=0;i<8;i++)
    {
        hash[i*4]   = h[i] >> 24;
        hash[i*4+1] = h[i] >> 16;
        hash[i*4+2] = h[i] >> 8;
        hash[i*4+3] = h[i];
    }
}

int calculateFileHash(char filename[], unsigned char hash[32])
{
    FILE *fp;
    unsigned char data[4096];
    unsigned char *allData;
    long size;
    size_t readBytes;

    fp = fopen(filename,"rb");

    if(fp == NULL)
        return 0;

    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    rewind(fp);

    allData = (unsigned char *)malloc(size + 1);

    if(allData == NULL)
    {
        fclose(fp);
        return 0;
    }

    readBytes = fread(allData,1,size,fp);
    fclose(fp);

    sha256(allData,(int)readBytes,hash);

    free(allData);

    return 1;
}

void printHash(unsigned char hash[32])
{
    int i;

    for(i=0;i<32;i++)
        printf("%02x",hash[i]);

    printf("\n");
}

int main()
{
    char filename[100];

    unsigned char hash1[32];
    unsigned char hash2[32];

    printf("========================================\n");
    printf("       FILE INTEGRITY MONITOR\n");
    printf("========================================\n");

    printf("\nEnter file name: ");
    scanf("%99s",filename);

    /* First hash */
    if(!calculateFileHash(filename,hash1))
    {
        printf("\nError: Cannot open file.\n");
        return 1;
    }

    printf("\nOriginal SHA-256 Hash:\n");
    printHash(hash1);

    printf("\nNow modify the file if required.\n");
    printf("Press ENTER after modification...");

    getchar();
    getchar();

    /* Second hash */
    if(!calculateFileHash(filename,hash2))
    {
        printf("\nError: Cannot open file.\n");
        return 1;
    }

    printf("\nCurrent SHA-256 Hash:\n");
    printHash(hash2);

    printf("\n========================================\n");

    if(memcmp(hash1,hash2,32) == 0)
    {
        printf("FILE STATUS: NOT MODIFIED\n");
        printf("Integrity verification successful.\n");
    }
    else
    {
        printf("FILE STATUS: MODIFIED\n");
        printf("Unauthorized modification detected!\n");
    }

    printf("========================================\n");

    return 0;
}
