#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long U32;
typedef unsigned long long U64;

/* =========================================================
   MD5
   ========================================================= */

#define MD5_ROL(x,n) (((x) << (n)) | ((x) >> (32-(n))))

U32 MD5_K[64] = {
0xd76aa478UL,0xe8c7b756UL,0x242070dbUL,0xc1bdceeeUL,
0xf57c0fafUL,0x4787c62aUL,0xa8304613UL,0xfd469501UL,
0x698098d8UL,0x8b44f7afUL,0xffff5bb1UL,0x895cd7beUL,
0x6b901122UL,0xfd987193UL,0xa679438eUL,0x49b40821UL,
0xf61e2562UL,0xc040b340UL,0x265e5a51UL,0xe9b6c7aaUL,
0xd62f105dUL,0x02441453UL,0xd8a1e681UL,0xe7d3fbc8UL,
0x21e1cde6UL,0xc33707d6UL,0xf4d50d87UL,0x455a14edUL,
0xa9e3e905UL,0xfcefa3f8UL,0x676f02d9UL,0x8d2a4c8aUL,
0xfffa3942UL,0x8771f681UL,0x6d9d6122UL,0xfde5380cUL,
0xa4beea44UL,0x4bdecfa9UL,0xf6bb4b60UL,0xbebfbc70UL,
0x289b7ec6UL,0xeaa127faUL,0xd4ef3085UL,0x04881d05UL,
0xd9d4d039UL,0xe6db99e5UL,0x1fa27cf8UL,0xc4ac5665UL,
0xf4292244UL,0x432aff97UL,0xab9423a7UL,0xfc93a039UL,
0x655b59c3UL,0x8f0ccc92UL,0xffeff47dUL,0x85845dd1UL,
0x6fa87e4fUL,0xfe2ce6e0UL,0xa3014314UL,0x4e0811a1UL,
0xf7537e82UL,0xbd3af235UL,0x2ad7d2bbUL,0xeb86d391UL
};

int MD5_S[64] = {
7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};

void md5(char *msg, int len, unsigned char out[16])
{
    unsigned char data[128];
    U32 M[16],a,b,c,d,A,B,C,D,F,g,temp;
    int newLen,i,j;

    newLen=len+1;
    while(newLen%64!=56) newLen++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    for(i=0;i<8;i++)
        data[newLen+i]=(unsigned char)(((U64)len*8)>>(8*i));

    A=0x67452301UL;
    B=0xefcdab89UL;
    C=0x98badcfeUL;
    D=0x10325476UL;

    for(i=0;i<newLen+8;i+=64)
    {
        for(j=0;j<16;j++)
        {
            M[j]=(U32)data[i+j*4] |
                 ((U32)data[i+j*4+1]<<8) |
                 ((U32)data[i+j*4+2]<<16) |
                 ((U32)data[i+j*4+3]<<24);
        }

        a=A;b=B;c=C;d=D;

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
            b=b+MD5_ROL(a+F+MD5_K[j]+M[g],MD5_S[j]);
            a=temp;
        }

        A+=a; B+=b; C+=c; D+=d;
    }

    for(i=0;i<4;i++)
    {
        out[i]=(A>>(8*i))&255;
        out[i+4]=(B>>(8*i))&255;
        out[i+8]=(C>>(8*i))&255;
        out[i+12]=(D>>(8*i))&255;
    }
}


/* =========================================================
   SHA-1
   ========================================================= */

#define SHA1_ROL(x,n) (((x)<<(n))|((x)>>(32-(n))))

void sha1(char *msg,int len,unsigned char out[20])
{
    unsigned char data[128];
    U32 w[80];
    U32 h0,h1,h2,h3,h4,a,b,c,d,e,f,k,t;
    int newLen,i,j;

    h0=0x67452301UL;
    h1=0xefcdab89UL;
    h2=0x98badcfeUL;
    h3=0x10325476UL;
    h4=0xc3d2e1f0UL;

    newLen=len+1;
    while(newLen%64!=56) newLen++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    {
        U64 bits=(U64)len*8;
        for(i=0;i<8;i++)
            data[newLen+7-i]=(unsigned char)(bits>>(8*i));
    }

    for(i=0;i<newLen+8;i+=64)
    {
        for(j=0;j<16;j++)
        {
            w[j]=((U32)data[i+j*4]<<24) |
                 ((U32)data[i+j*4+1]<<16) |
                 ((U32)data[i+j*4+2]<<8) |
                 data[i+j*4+3];
        }

        for(j=16;j<80;j++)
            w[j]=SHA1_ROL(w[j-3]^w[j-8]^w[j-14]^w[j-16],1);

        a=h0;b=h1;c=h2;d=h3;e=h4;

        for(j=0;j<80;j++)
        {
            if(j<20)
            {
                f=(b&c)|((~b)&d);
                k=0x5a827999UL;
            }
            else if(j<40)
            {
                f=b^c^d;
                k=0x6ed9eba1UL;
            }
            else if(j<60)
            {
                f=(b&c)|(b&d)|(c&d);
                k=0x8f1bbcdcUL;
            }
            else
            {
                f=b^c^d;
                k=0xca62c1d6UL;
            }

            t=SHA1_ROL(a,5)+f+e+k+w[j];

            e=d;
            d=c;
            c=SHA1_ROL(b,30);
            b=a;
            a=t;
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


/* =========================================================
   SHA-224 / SHA-256
   ========================================================= */

#define ROR32(x,n) ((x>>n)|(x<<(32-n)))
#define CH32(x,y,z) ((x&y)^(~x&z))
#define MAJ32(x,y,z) ((x&y)^(x&z)^(y&z))
#define E0(x) (ROR32(x,2)^ROR32(x,13)^ROR32(x,22))
#define E1(x) (ROR32(x,6)^ROR32(x,11)^ROR32(x,25))
#define S0(x) (ROR32(x,7)^ROR32(x,18)^(x>>3))
#define S1(x) (ROR32(x,17)^ROR32(x,19)^(x>>10))

U32 SHA_K[64] = {
0x428a2f98UL,0x71374491UL,0xb5c0fbcfUL,0xe9b5dba5UL,
0x3956c25bUL,0x59f111f1UL,0x923f82a4UL,0xab1c5ed5UL,
0xd807aa98UL,0x12835b01UL,0x243185beUL,0x550c7dc3UL,
0x72be5d74UL,0x80deb1feUL,0x9bdc06a7UL,0xc19bf174UL,
0xe49b69c1UL,0xefbe4786UL,0x0fc19dc6UL,0x240ca1ccUL,
0x2de92c6fUL,0x4a7484aaUL,0x5cb0a9dcUL,0x76f988daUL,
0x983e5152UL,0xa831c66dUL,0xb00327c8UL,0xbf597fc7UL,
0xc6e00bf3UL,0xd5a79147UL,0x06ca6351UL,0x14292967UL,
0x27b70a85UL,0x2e1b2138UL,0x4d2c6dfcUL,0x53380d13UL,
0x650a7354UL,0x766a0abbUL,0x81c2c92eUL,0x92722c85UL,
0xa2bfe8a1UL,0xa81a664bUL,0xc24b8b70UL,0xc76c51a3UL,
0xd192e819UL,0xd6990624UL,0xf40e3585UL,0x106aa070UL,
0x19a4c116UL,0x1e376c08UL,0x2748774cUL,0x34b0bcb5UL,
0x391c0cb3UL,0x4ed8aa4aUL,0x5b9cca4fUL,0x682e6ff3UL,
0x748f82eeUL,0x78a5636fUL,0x84c87814UL,0x8cc70208UL,
0x90befffaUL,0xa4506cebUL,0xbef9a3f7UL,0xc67178f2UL
};

void sha256_core(char *msg,int len,unsigned char out[32],int is224)
{
    unsigned char data[128];
    U32 w[64],h[8];
    U32 a,b,c,d,e,f,g,hh,t1,t2;
    int newLen,i,j;

    if(is224)
    {
        h[0]=0xc1059ed8UL;
        h[1]=0x367cd507UL;
        h[2]=0x3070dd17UL;
        h[3]=0xf70e5939UL;
        h[4]=0xffc00b31UL;
        h[5]=0x68581511UL;
        h[6]=0x64f98fa7UL;
        h[7]=0xbefa4fa4UL;
    }
    else
    {
        h[0]=0x6a09e667UL;
        h[1]=0xbb67ae85UL;
        h[2]=0x3c6ef372UL;
        h[3]=0xa54ff53aUL;
        h[4]=0x510e527fUL;
        h[5]=0x9b05688cUL;
        h[6]=0x1f83d9abUL;
        h[7]=0x5be0cd19UL;
    }

    newLen=len+1;
    while(newLen%64!=56) newLen++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    {
        U64 bits=(U64)len*8;
        for(i=0;i<8;i++)
            data[newLen+7-i]=(unsigned char)(bits>>(8*i));
    }

    for(i=0;i<newLen+8;i+=64)
    {
        for(j=0;j<16;j++)
        {
            w[j]=((U32)data[i+j*4]<<24) |
                 ((U32)data[i+j*4+1]<<16) |
                 ((U32)data[i+j*4+2]<<8) |
                 data[i+j*4+3];
        }

        for(j=16;j<64;j++)
            w[j]=S1(w[j-2])+w[j-7]+S0(w[j-15])+w[j-16];

        a=h[0];b=h[1];c=h[2];d=h[3];
        e=h[4];f=h[5];g=h[6];hh=h[7];

        for(j=0;j<64;j++)
        {
            t1=hh+E1(e)+CH32(e,f,g)+SHA_K[j]+w[j];
            t2=E0(a)+MAJ32(a,b,c);

            hh=g;
            g=f;
            f=e;
            e=d+t1;
            d=c;
            c=b;
            b=a;
            a=t1+t2;
        }

        h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;
        h[4]+=e;h[5]+=f;h[6]+=g;h[7]+=hh;
    }

    for(i=0;i<(is224?7:8);i++)
    {
        out[i*4]=(h[i]>>24)&255;
        out[i*4+1]=(h[i]>>16)&255;
        out[i*4+2]=(h[i]>>8)&255;
        out[i*4+3]=h[i]&255;
    }
}


/* =========================================================
   SHA-384 / SHA-512
   ========================================================= */

#define ROR64(x,n) ((x>>n)|(x<<(64-n)))
#define CH64(x,y,z) ((x&y)^(~x&z))
#define MAJ64(x,y,z) ((x&y)^(x&z)^(y&z))

#define BIG0(x) (ROR64(x,28)^ROR64(x,34)^ROR64(x,39))
#define BIG1(x) (ROR64(x,14)^ROR64(x,18)^ROR64(x,41))
#define SMALL0(x) (ROR64(x,1)^ROR64(x,8)^(x>>7))
#define SMALL1(x) (ROR64(x,19)^ROR64(x,61)^(x>>6))

U64 SHA512_K[80] = {
0x428a2f98d728ae22ULL,0x7137449123ef65cdULL,
0xb5c0fbcfec4d3b2fULL,0xe9b5dba58189dbbcULL,
0x3956c25bf348b538ULL,0x59f111f1b605d019ULL,
0x923f82a4af194f9bULL,0xab1c5ed5da6d8118ULL,
0xd807aa98a3030242ULL,0x12835b0145706fbeULL,
0x243185be4ee4b28cULL,0x550c7dc3d5ffb4e2ULL,
0x72be5d74f27b896fULL,0x80deb1fe3b1696b1ULL,
0x9bdc06a725c71235ULL,0xc19bf174cf692694ULL,
0xe49b69c19ef14ad2ULL,0xefbe4786384f25e3ULL,
0x0fc19dc68b8cd5b5ULL,0x240ca1cc77ac9c65ULL,
0x2de92c6f592b0275ULL,0x4a7484aa6ea6e483ULL,
0x5cb0a9dcbd41fbd4ULL,0x76f988da831153b5ULL,
0x983e5152ee66dfabULL,0xa831c66d2db43210ULL,
0xb00327c898fb213fULL,0xbf597fc7beef0ee4ULL,
0xc6e00bf33da88fc2ULL,0xd5a79147930aa725ULL,
0x06ca6351e003826fULL,0x142929670a0e6e70ULL,
0x27b70a8546d22ffcULL,0x2e1b21385c26c926ULL,
0x4d2c6dfc5ac42aedULL,0x53380d139d95b3dfULL,
0x650a73548baf63deULL,0x766a0abb3c77b2a8ULL,
0x81c2c92e47edaee6ULL,0x92722c851482353bULL,
0xa2bfe8a14cf10364ULL,0xa81a664bbc423001ULL,
0xc24b8b70d0f89791ULL,0xc76c51a30654be30ULL,
0xd192e819d6ef5218ULL,0xd69906245565a910ULL,
0xf40e35855771202aULL,0x106aa07032bbd1b8ULL,
0x19a4c116b8d2d0c8ULL,0x1e376c085141ab53ULL,
0x2748774cdf8eeb99ULL,0x34b0bcb5e19b48a8ULL,
0x391c0cb3c5c95a63ULL,0x4ed8aa4ae3418acbULL,
0x5b9cca4f7763e373ULL,0x682e6ff3d6b2b8a3ULL,
0x748f82ee5defb2fcULL,0x78a5636f43172f60ULL,
0x84c87814a1f0ab72ULL,0x8cc702081a6439ecULL,
0x90befffa23631e28ULL,0xa4506cebde82bde9ULL,
0xbef9a3f7b2c67915ULL,0xc67178f2e372532bULL,
0xca273eceea26619cULL,0xd186b8c721c0c207ULL,
0xeada7dd6cde0eb1eULL,0xf57d4f7fee6ed178ULL,
0x06f067aa72176fbaULL,0x0a637dc5a2c898a6ULL,
0x113f9804bef90daeULL,0x1b710b35131c471bULL,
0x28db77f523047d84ULL,0x32caab7b40c72493ULL,
0x3c9ebe0a15c9bebcULL,0x431d67c49c100d4cULL,
0x4cc5d4becb3e42b6ULL,0x597f299cfc657e2aULL,
0x5fcb6fab3ad6faecULL,0x6c44198c4a475817ULL
};

void sha512_core(char *msg,int len,unsigned char out[64],int is384)
{
    unsigned char data[256];
    U64 w[80],h[8];
    U64 a,b,c,d,e,f,g,hh,t1,t2,bits;
    int newLen,i,j,count;

    if(is384)
    {
        h[0]=0xcbbb9d5dc1059ed8ULL;
        h[1]=0x629a292a367cd507ULL;
        h[2]=0x9159015a3070dd17ULL;
        h[3]=0x152fecd8f70e5939ULL;
        h[4]=0x67332667ffc00b31ULL;
        h[5]=0x8eb44a8768581511ULL;
        h[6]=0xdb0c2e0d64f98fa7ULL;
        h[7]=0x47b5481dbefa4fa4ULL;
    }
    else
    {
        h[0]=0x6a09e667f3bcc908ULL;
        h[1]=0xbb67ae8584caa73bULL;
        h[2]=0x3c6ef372fe94f82bULL;
        h[3]=0xa54ff53a5f1d36f1ULL;
        h[4]=0x510e527fade682d1ULL;
        h[5]=0x9b05688c2b3e6c1fULL;
        h[6]=0x1f83d9abfb41bd6bULL;
        h[7]=0x5be0cd19137e2179ULL;
    }

    newLen=len+1;
    while(newLen%128!=112) newLen++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    bits=(U64)len*8;

    for(i=0;i<8;i++)
        data[newLen+15-i]=(unsigned char)(bits>>(8*i));

    for(i=0;i<newLen+16;i+=128)
    {
        for(j=0;j<16;j++)
        {
            w[j]=((U64)data[i+j*8]<<56) |
                 ((U64)data[i+j*8+1]<<48) |
                 ((U64)data[i+j*8+2]<<40) |
                 ((U64)data[i+j*8+3]<<32) |
                 ((U64)data[i+j*8+4]<<24) |
                 ((U64)data[i+j*8+5]<<16) |
                 ((U64)data[i+j*8+6]<<8) |
                 data[i+j*8+7];
        }

        for(j=16;j<80;j++)
            w[j]=SMALL1(w[j-2])+w[j-7]+
                 SMALL0(w[j-15])+w[j-16];

        a=h[0];b=h[1];c=h[2];d=h[3];
        e=h[4];f=h[5];g=h[6];hh=h[7];

        for(j=0;j<80;j++)
        {
            t1=hh+BIG1(e)+CH64(e,f,g)+SHA512_K[j]+w[j];
            t2=BIG0(a)+MAJ64(a,b,c);

            hh=g;
            g=f;
            f=e;
            e=d+t1;
            d=c;
            c=b;
            b=a;
            a=t1+t2;
        }

        h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;
        h[4]+=e;h[5]+=f;h[6]+=g;h[7]+=hh;
    }

    count=is384?6:8;

    for(i=0;i<count;i++)
    {
        out[i*8]=(h[i]>>56)&255;
        out[i*8+1]=(h[i]>>48)&255;
        out[i*8+2]=(h[i]>>40)&255;
        out[i*8+3]=(h[i]>>32)&255;
        out[i*8+4]=(h[i]>>24)&255;
        out[i*8+5]=(h[i]>>16)&255;
        out[i*8+6]=(h[i]>>8)&255;
        out[i*8+7]=h[i]&255;
    }
}


/* =========================================================
   PRINT HASH
   ========================================================= */

void printHash(unsigned char hash[],int length)
{
    int i;

    for(i=0;i<length;i++)
        printf("%02x",hash[i]);

    printf("\n");
}


/* =========================================================
   MAIN PROGRAM
   ========================================================= */

int main()
{
    char message[1000];
    int choice;

    unsigned char hash[64];

    printf("========================================\n");
    printf("       HASH ALGORITHM SELECTION\n");
    printf("========================================\n");

    printf("\nEnter message: ");
    fgets(message,sizeof(message),stdin);

    message[strcspn(message,"\n")]='\0';

    printf("\nSelect Algorithm:\n");
    printf("1. MD5\n");
    printf("2. SHA-1\n");
    printf("3. SHA-224\n");
    printf("4. SHA-256\n");
    printf("5. SHA-384\n");
    printf("6. SHA-512\n");

    printf("\nEnter choice: ");
    scanf("%d",&choice);

    printf("\n----------------------------------------\n");

    switch(choice)
    {
        case 1:
            md5(message,strlen(message),hash);

            printf("Algorithm    : MD5\n");
            printf("Digest Size  : 128 bits\n");
            printf("Digest       : ");
            printHash(hash,16);
            break;

        case 2:
            sha1(message,strlen(message),hash);

            printf("Algorithm    : SHA-1\n");
            printf("Digest Size  : 160 bits\n");
            printf("Digest       : ");
            printHash(hash,20);
            break;

        case 3:
            sha256_core(message,strlen(message),hash,1);

            printf("Algorithm    : SHA-224\n");
            printf("Digest Size  : 224 bits\n");
            printf("Digest       : ");
            printHash(hash,28);
            break;

        case 4:
            sha256_core(message,strlen(message),hash,0);

            printf("Algorithm    : SHA-256\n");
            printf("Digest Size  : 256 bits\n");
            printf("Digest       : ");
            printHash(hash,32);
            break;

        case 5:
            sha512_core(message,strlen(message),hash,1);

            printf("Algorithm    : SHA-384\n");
            printf("Digest Size  : 384 bits\n");
            printf("Digest       : ");
            printHash(hash,48);
            break;

        case 6:
            sha512_core(message,strlen(message),hash,0);

            printf("Algorithm    : SHA-512\n");
            printf("Digest Size  : 512 bits\n");
            printf("Digest       : ");
            printHash(hash,64);
            break;

        default:
            printf("Invalid choice!\n");
            return 0;
    }

    printf("----------------------------------------\n");

    return 0;
}
