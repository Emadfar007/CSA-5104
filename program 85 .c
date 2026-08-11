#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* ---------- MD5 ---------- */

#define ROL(x,n) (((x)<<(n))|((x)>>(32-(n))))

uint32_t K[64]={
0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
0x6b901122,0xfd987193,0xa679438e,0x49b40821,
0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};

int S[64]={
7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};

void md5(char *msg,int len,unsigned char out[16])
{
    unsigned char data[128];
    uint32_t M[16];
    uint32_t a,b,c,d,A,B,C,D,F,g,temp;
    int n,i,j;

    n=len+1;

    while(n%64!=56)
        n++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);

    data[len]=0x80;

    for(i=0;i<8;i++)
        data[n+i]=(unsigned char)(((uint64_t)len*8)>>(8*i));

    A=0x67452301;
    B=0xefcdab89;
    C=0x98badcfe;
    D=0x10325476;

    for(i=0;i<n+8;i+=64)
    {
        for(j=0;j<16;j++)
        {
            M[j]=(uint32_t)data[i+j*4] |
                 ((uint32_t)data[i+j*4+1]<<8) |
                 ((uint32_t)data[i+j*4+2]<<16) |
                 ((uint32_t)data[i+j*4+3]<<24);
        }

        a=A;
        b=B;
        c=C;
        d=D;

        for(j=0;j<64;j++)
        {
            if(j<16)
            {
                F=(b&c)|((~b)&d);
                g=j;
            }
            else if(j<32)
            {
                F=(d&b)|((~d)&c);
                g=(5*j+1)%16;
            }
            else if(j<48)
            {
                F=b^c^d;
                g=(3*j+5)%16;
            }
            else
            {
                F=c^(b|(~d));
                g=(7*j)%16;
            }

            temp=d;
            d=c;
            c=b;
            b=b+ROL(a+F+K[j]+M[g],S[j]);
            a=temp;
        }

        A+=a;
        B+=b;
        C+=c;
        D+=d;
    }

    for(i=0;i<4;i++)
    {
        out[i]=(A>>(8*i))&255;
        out[i+4]=(B>>(8*i))&255;
        out[i+8]=(C>>(8*i))&255;
        out[i+12]=(D>>(8*i))&255;
    }
}


/* ---------- SHA-256 ---------- */

#define ROTR(x,n) ((x>>n)|(x<<(32-n)))
#define CH(x,y,z) ((x&y)^(~x&z))
#define MAJ(x,y,z) ((x&y)^(x&z)^(y&z))
#define EP0(x) (ROTR(x,2)^ROTR(x,13)^ROTR(x,22))
#define EP1(x) (ROTR(x,6)^ROTR(x,11)^ROTR(x,25))
#define SIG0(x) (ROTR(x,7)^ROTR(x,18)^(x>>3))
#define SIG1(x) (ROTR(x,17)^ROTR(x,19)^(x>>10))

uint32_t K256[64]={
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

void sha256(char *msg,int len,unsigned char out[32])
{
    unsigned char data[128];
    uint32_t w[64],h[8];
    uint32_t a,b,c,d,e,f,g,hh,t1,t2;
    int n,i,j;

    h[0]=0x6a09e667;
    h[1]=0xbb67ae85;
    h[2]=0x3c6ef372;
    h[3]=0xa54ff53a;
    h[4]=0x510e527f;
    h[5]=0x9b05688c;
    h[6]=0x1f83d9ab;
    h[7]=0x5be0cd19;

    n=len+1;

    while(n%64!=56)
        n++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);

    data[len]=0x80;

    for(i=0;i<8;i++)
        data[n+7-i]=(unsigned char)(((uint64_t)len*8)>>(8*i));

    for(i=0;i<n+8;i+=64)
    {
        for(j=0;j<16;j++)
        {
            w[j]=((uint32_t)data[i+j*4]<<24) |
                 ((uint32_t)data[i+j*4+1]<<16) |
                 ((uint32_t)data[i+j*4+2]<<8) |
                 data[i+j*4+3];
        }

        for(j=16;j<64;j++)
            w[j]=SIG1(w[j-2])+w[j-7]+
                 SIG0(w[j-15])+w[j-16];

        a=h[0];
        b=h[1];
        c=h[2];
        d=h[3];
        e=h[4];
        f=h[5];
        g=h[6];
        hh=h[7];

        for(j=0;j<64;j++)
        {
            t1=hh+EP1(e)+CH(e,f,g)+K256[j]+w[j];
            t2=EP0(a)+MAJ(a,b,c);

            hh=g;
            g=f;
            f=e;
            e=d+t1;
            d=c;
            c=b;
            b=a;
            a=t1+t2;
        }

        h[0]+=a;
        h[1]+=b;
        h[2]+=c;
        h[3]+=d;
        h[4]+=e;
        h[5]+=f;
        h[6]+=g;
        h[7]+=hh;
    }

    for(i=0;i<8;i++)
    {
        out[i*4]=(h[i]>>24)&255;
        out[i*4+1]=(h[i]>>16)&255;
        out[i*4+2]=(h[i]>>8)&255;
        out[i*4+3]=h[i]&255;
    }
}


/* ---------- Print Hash ---------- */

void printHash(unsigned char hash[],int len)
{
    int i;

    for(i=0;i<len;i++)
        printf("%02x",hash[i]);

    printf("\n");
}


/* ---------- Main ---------- */

int main()
{
    char messages[10][100];

    unsigned char md5Hash[10][16];
    unsigned char shaHash[10][32];

    int n,i,j;
    int md5Collision=0;
    int shaCollision=0;

    printf("============================================\n");
    printf("       HASH COLLISION ANALYSIS\n");
    printf("============================================\n");

    printf("\nEnter number of messages (2-10): ");
    scanf("%d",&n);

    getchar();

    if(n<2 || n>10)
    {
        printf("Invalid number of messages!\n");
        return 0;
    }

    for(i=0;i<n;i++)
    {
        printf("Enter message %d: ",i+1);
        fgets(messages[i],100,stdin);

        messages[i][strcspn(messages[i],"\n")]='\0';

        md5(messages[i],strlen(messages[i]),md5Hash[i]);

        sha256(messages[i],strlen(messages[i]),shaHash[i]);
    }

    printf("\n============================================\n");
    printf("                 HASH VALUES\n");
    printf("============================================\n");

    for(i=0;i<n;i++)
    {
        printf("\nMessage %d: %s\n",i+1,messages[i]);

        printf("MD5     : ");
        printHash(md5Hash[i],16);

        printf("SHA-256 : ");
        printHash(shaHash[i],32);
    }

    /* Check MD5 collisions */

    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(strcmp(messages[i],messages[j])!=0 &&
               memcmp(md5Hash[i],md5Hash[j],16)==0)
            {
                md5Collision=1;

                printf("\nMD5 COLLISION FOUND!");
                printf("\nMessage %d and Message %d\n",
                       i+1,j+1);
            }
        }
    }

    /* Check SHA-256 collisions */

    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(strcmp(messages[i],messages[j])!=0 &&
               memcmp(shaHash[i],shaHash[j],32)==0)
            {
                shaCollision=1;

                printf("\nSHA-256 COLLISION FOUND!");
                printf("\nMessage %d and Message %d\n",
                       i+1,j+1);
            }
        }
    }

    printf("\n============================================\n");
    printf("             COLLISION ANALYSIS\n");
    printf("============================================\n");

    if(md5Collision)
        printf("MD5     : Collision detected\n");
    else
        printf("MD5     : No collision detected\n");

    if(shaCollision)
        printf("SHA-256 : Collision detected\n");
    else
        printf("SHA-256 : No collision detected\n");

    printf("\n============================================\n");
    printf("             SECURITY ANALYSIS\n");
    printf("============================================\n");

    printf("\nMD5:\n");
    printf("- Digest size: 128 bits\n");
    printf("- Collision attacks are practical.\n");
    printf("- Not recommended for security applications.\n");

    printf("\nSHA-1:\n");
    printf("- Digest size: 160 bits\n");
    printf("- Collision attacks have been demonstrated.\n");
    printf("- Not recommended for new security applications.\n");

    printf("\nSHA-256:\n");
    printf("- Digest size: 256 bits\n");
    printf("- Strong collision resistance.\n");
    printf("- Suitable for modern security applications.\n");

    printf("\nConclusion:\n");
    printf("A collision occurs when two different inputs\n");
    printf("produce the same hash value. Strong collision\n");
    printf("resistance is important for secure hashing.\n");

    return 0;
}
