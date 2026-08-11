#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define ROTR(x,n) (((x) >> (n)) | ((x) << (32-(n))))
#define CH(x,y,z) (((x)&(y)) ^ (~(x)&(z)))
#define MAJ(x,y,z) (((x)&(y)) ^ ((x)&(z)) ^ ((y)&(z)))
#define EP0(x) (ROTR(x,2)^ROTR(x,13)^ROTR(x,22))
#define EP1(x) (ROTR(x,6)^ROTR(x,11)^ROTR(x,25))
#define SIG0(x) (ROTR(x,7)^ROTR(x,18)^((x)>>3))
#define SIG1(x) (ROTR(x,17)^ROTR(x,19)^((x)>>10))

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

void sha256(char *input, int len, uint32_t h[8])
{
    unsigned char data[128];
    uint32_t w[64];
    uint32_t a,b,c,d,e,f,g,hh,t1,t2;
    int newLen, i, j;

    newLen = len + 1;
    while(newLen % 64 != 56)
        newLen++;

    memset(data, 0, sizeof(data));
    memcpy(data, input, len);
    data[len] = 0x80;

    uint64_t bits = (uint64_t)len * 8;

    for(i=0; i<8; i++)
        data[newLen + 7-i] = (bits >> (i*8)) & 0xff;

    for(i=0; i<newLen+8; i+=64)
    {
        for(j=0;j<16;j++)
        {
            w[j] =
                ((uint32_t)data[i+j*4] << 24) |
                ((uint32_t)data[i+j*4+1] << 16) |
                ((uint32_t)data[i+j*4+2] << 8) |
                data[i+j*4+3];
        }

        for(j=16;j<64;j++)
            w[j] = SIG1(w[j-2]) + w[j-7] +
                   SIG0(w[j-15]) + w[j-16];

        a=h[0]; b=h[1]; c=h[2]; d=h[3];
        e=h[4]; f=h[5]; g=h[6]; hh=h[7];

        for(j=0;j<64;j++)
        {
            t1 = hh + EP1(e) + CH(e,f,g) + K[j] + w[j];
            t2 = EP0(a) + MAJ(a,b,c);

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
}

void printHash(uint32_t h[8], int words)
{
    int i;

    for(i=0;i<words;i++)
        printf("%08x",h[i]);

    printf("\n");
}

int main()
{
    char input[1000];
    uint32_t sha256Hash[8];
    uint32_t sha224Hash[8];

    printf("Enter text: ");
    fgets(input,sizeof(input),stdin);

    input[strcspn(input,"\n")] = '\0';

    /* SHA-256 Initial Values */
    sha256Hash[0]=0x6a09e667;
    sha256Hash[1]=0xbb67ae85;
    sha256Hash[2]=0x3c6ef372;
    sha256Hash[3]=0xa54ff53a;
    sha256Hash[4]=0x510e527f;
    sha256Hash[5]=0x9b05688c;
    sha256Hash[6]=0x1f83d9ab;
    sha256Hash[7]=0x5be0cd19;

    /* SHA-224 Initial Values */
    sha224Hash[0]=0xc1059ed8;
    sha224Hash[1]=0x367cd507;
    sha224Hash[2]=0x3070dd17;
    sha224Hash[3]=0xf70e5939;
    sha224Hash[4]=0xffc00b31;
    sha224Hash[5]=0x68581511;
    sha224Hash[6]=0x64f98fa7;
    sha224Hash[7]=0xbefa4fa4;

    sha256(input,strlen(input),sha256Hash);
    sha256(input,strlen(input),sha224Hash);

    printf("\nInput       : %s\n",input);

    printf("\nSHA-224     : ");
    printHash(sha224Hash,7);

    printf("Digest Size : 224 bits (28 bytes)\n");
    printf("Hex Length  : 56 characters\n");

    printf("\nSHA-256     : ");
    printHash(sha256Hash,8);

    printf("Digest Size : 256 bits (32 bytes)\n");
    printf("Hex Length  : 64 characters\n");

    return 0;
}
