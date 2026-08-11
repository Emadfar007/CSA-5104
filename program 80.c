#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

/* ---------- MD5 ---------- */

#define ROL(x,n) (((x) << (n)) | ((x) >> (32-(n))))

uint32_t MD5K[64] = {
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

int MD5S[64] = {
7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};

void md5(char *msg, int len, unsigned char out[16])
{
    unsigned char data[128];
    uint32_t a,b,c,d,A,B,C,D,F,g,temp;
    uint32_t M[16];
    int newLen,i,j;

    newLen=len+1;
    while(newLen%64!=56) newLen++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    {
        uint64_t bits=(uint64_t)len*8;
        memcpy(data+newLen,&bits,8);
    }

    A=0x67452301;
    B=0xefcdab89;
    C=0x98badcfe;
    D=0x10325476;

    for(i=0;i<newLen;i+=64)
    {
        for(j=0;j<16;j++)
            memcpy(&M[j],data+i+j*4,4);

        a=A;b=B;c=C;d=D;

        for(j=0;j<64;j++)
        {
            if(j<16){F=(b&c)|(~b&d);g=j;}
            else if(j<32){F=(d&b)|(~d&c);g=(5*j+1)%16;}
            else if(j<48){F=b^c^d;g=(3*j+5)%16;}
            else{F=c^(b|~d);g=(7*j)%16;}

            temp=d;
            d=c;
            c=b;
            b=b+ROL(a+F+MD5K[j]+M[g],MD5S[j]);
            a=temp;
        }

        A+=a;B+=b;C+=c;D+=d;
    }

    memcpy(out,&A,4);
    memcpy(out+4,&B,4);
    memcpy(out+8,&C,4);
    memcpy(out+12,&D,4);
}

/* ---------- SHA-1 ---------- */

#define SHA1ROL(x,n) (((x)<<(n))|((x)>>(32-(n))))

void sha1(char *msg,int len,unsigned char out[20])
{
    unsigned char data[128];
    uint32_t w[80];
    uint32_t a,b,c,d,e,f,k,t;
    uint32_t h0=0x67452301,h1=0xefcdab89;
    uint32_t h2=0x98badcfe,h3=0x10325476;
    uint32_t h4=0xc3d2e1f0;
    int newLen,i,j;

    newLen=len+1;
    while(newLen%64!=56) newLen++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    {
        uint64_t bits=(uint64_t)len*8;
        for(i=0;i<8;i++)
            data[newLen+7-i]=(bits>>(i*8))&255;
    }

    for(i=0;i<newLen+8;i+=64)
    {
        for(j=0;j<16;j++)
            w[j]=((uint32_t)data[i+j*4]<<24)|
                 ((uint32_t)data[i+j*4+1]<<16)|
                 ((uint32_t)data[i+j*4+2]<<8)|
                 data[i+j*4+3];

        for(j=16;j<80;j++)
            w[j]=SHA1ROL(w[j-3]^w[j-8]^w[j-14]^w[j-16],1);

        a=h0;b=h1;c=h2;d=h3;e=h4;

        for(j=0;j<80;j++)
        {
            if(j<20){f=(b&c)|(~b&d);k=0x5a827999;}
            else if(j<40){f=b^c^d;k=0x6ed9eba1;}
            else if(j<60){f=(b&c)|(b&d)|(c&d);k=0x8f1bbcdc;}
            else{f=b^c^d;k=0xca62c1d6;}

            t=SHA1ROL(a,5)+f+e+k+w[j];
            e=d;d=c;c=SHA1ROL(b,30);b=a;a=t;
        }

        h0+=a;h1+=b;h2+=c;h3+=d;h4+=e;
    }

    for(i=0;i<4;i++)
    {
        out[i]=(h0>>(24-8*i))&255;
        out[i+4]=(h1>>(24-8*i))&255;
        out[i+8]=(h2>>(24-8*i))&255;
        out[i+12]=(h3>>(24-8*i))&255;
        out[i+16]=(h4>>(24-8*i))&255;
    }
}

/* ---------- SHA-256 ---------- */

#define ROTR(x,n) ((x>>n)|(x<<(32-n)))
#define CH(x,y,z) ((x&y)^(~x&z))
#define MAJ(x,y,z) ((x&y)^(x&z)^(y&z))
#define E0(x) (ROTR(x,2)^ROTR(x,13)^ROTR(x,22))
#define E1(x) (ROTR(x,6)^ROTR(x,11)^ROTR(x,25))
#define S0(x) (ROTR(x,7)^ROTR(x,18)^(x>>3))
#define S1(x) (ROTR(x,17)^ROTR(x,19)^(x>>10))

uint32_t SHA256K[64]={
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
    int newLen,i,j;

    h[0]=0x6a09e667;h[1]=0xbb67ae85;
    h[2]=0x3c6ef372;h[3]=0xa54ff53a;
    h[4]=0x510e527f;h[5]=0x9b05688c;
    h[6]=0x1f83d9ab;h[7]=0x5be0cd19;

    newLen=len+1;
    while(newLen%64!=56) newLen++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    {
        uint64_t bits=(uint64_t)len*8;
        for(i=0;i<8;i++)
            data[newLen+7-i]=(bits>>(i*8))&255;
    }

    for(i=0;i<newLen+8;i+=64)
    {
        for(j=0;j<16;j++)
            w[j]=((uint32_t)data[i+j*4]<<24)|
                 ((uint32_t)data[i+j*4+1]<<16)|
                 ((uint32_t)data[i+j*4+2]<<8)|
                 data[i+j*4+3];

        for(j=16;j<64;j++)
            w[j]=S1(w[j-2])+w[j-7]+S0(w[j-15])+w[j-16];

        a=h[0];b=h[1];c=h[2];d=h[3];
        e=h[4];f=h[5];g=h[6];hh=h[7];

        for(j=0;j<64;j++)
        {
            t1=hh+E1(e)+CH(e,f,g)+SHA256K[j]+w[j];
            t2=E0(a)+MAJ(a,b,c);

            hh=g;g=f;f=e;e=d+t1;
            d=c;c=b;b=a;a=t1+t2;
        }

        h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;
        h[4]+=e;h[5]+=f;h[6]+=g;h[7]+=hh;
    }

    for(i=0;i<8;i++)
    {
        out[i*4]=(h[i]>>24)&255;
        out[i*4+1]=(h[i]>>16)&255;
        out[i*4+2]=(h[i]>>8)&255;
        out[i*4+3]=h[i]&255;
    }
}

/* ---------- Main ---------- */

void printHash(unsigned char *hash,int len)
{
    int i;

    for(i=0;i<len;i++)
        printf("%02x",hash[i]);

    printf("\n");
}

int main()
{
    char message[1000];

    unsigned char md5Hash[16];
    unsigned char sha1Hash[20];
    unsigned char sha256Hash[32];

    clock_t start,end;

    double md5Time;
    double sha1Time;
    double sha256Time;

    printf("Enter message: ");
    fgets(message,sizeof(message),stdin);

    message[strcspn(message,"\n")]='\0';

    /* MD5 */
    start=clock();
    md5(message,strlen(message),md5Hash);
    end=clock();
    md5Time=(double)(end-start)*1000/CLOCKS_PER_SEC;

    /* SHA-1 */
    start=clock();
    sha1(message,strlen(message),sha1Hash);
    end=clock();
    sha1Time=(double)(end-start)*1000/CLOCKS_PER_SEC;

    /* SHA-256 */
    start=clock();
    sha256(message,strlen(message),sha256Hash);
    end=clock();
    sha256Time=(double)(end-start)*1000/CLOCKS_PER_SEC;

    printf("\n============================================\n");
    printf("             HASH COMPARISON\n");
    printf("============================================\n");

    printf("\nInput: %s\n",message);

    printf("\nMD5:\n");
    printf("Hash Length : 128 bits / 16 bytes\n");
    printf("Hex Length  : 32 characters\n");
    printf("Digest      : ");
    printHash(md5Hash,16);
    printf("Time        : %.6f ms\n",md5Time);

    printf("\nSHA-1:\n");
    printf("Hash Length : 160 bits / 20 bytes\n");
    printf("Hex Length  : 40 characters\n");
    printf("Digest      : ");
    printHash(sha1Hash,20);
    printf("Time        : %.6f ms\n",sha1Time);

    printf("\nSHA-256:\n");
    printf("Hash Length : 256 bits / 32 bytes\n");
    printf("Hex Length  : 64 characters\n");
    printf("Digest      : ");
    printHash(sha256Hash,32);
    printf("Time        : %.6f ms\n",sha256Time);

    printf("\n============================================\n");
    printf("Algorithm\tDigest Size\tHex Length\tTime(ms)\n");
    printf("============================================\n");
    printf("MD5\t\t128 bits\t32\t\t%.6f\n",md5Time);
    printf("SHA-1\t\t160 bits\t40\t\t%.6f\n",sha1Time);
    printf("SHA-256\t\t256 bits\t64\t\t%.6f\n",sha256Time);
    printf("============================================\n");

    return 0;
}
