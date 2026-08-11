#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long U32;
typedef unsigned long long U64;

/* ================= MD5 ================= */

#define ROL32(x,n) (((x)<<(n))|((x)>>(32-(n))))

U32 MK[64]={
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

int MS[64]={
7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};

void md5(char *msg,int len,unsigned char out[16])
{
    unsigned char data[128];
    U32 M[16],a,b,c,d,A,B,C,D,F,g,temp;
    int n,i,j;

    n=len+1;
    while(n%64!=56)n++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    for(i=0;i<8;i++)
        data[n+i]=(unsigned char)(((U64)len*8)>>(8*i));

    A=0x67452301UL;
    B=0xefcdab89UL;
    C=0x98badcfeUL;
    D=0x10325476UL;

    for(i=0;i<n+8;i+=64)
    {
        for(j=0;j<16;j++)
            M[j]=(U32)data[i+j*4]|
                 ((U32)data[i+j*4+1]<<8)|
                 ((U32)data[i+j*4+2]<<16)|
                 ((U32)data[i+j*4+3]<<24);

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
            b=b+ROL32(a+F+MK[j]+M[g],MS[j]);
            a=temp;
        }

        A+=a;B+=b;C+=c;D+=d;
    }

    for(i=0;i<4;i++)
    {
        out[i]=A>>(8*i);
        out[i+4]=B>>(8*i);
        out[i+8]=C>>(8*i);
        out[i+12]=D>>(8*i);
    }
}


/* ================= SHA-1 ================= */

#define ROL(x,n) (((x)<<(n))|((x)>>(32-(n))))

void sha1(char *msg,int len,unsigned char out[20])
{
    unsigned char data[128];
    U32 w[80];
    U32 h0,h1,h2,h3,h4,a,b,c,d,e,f,k,t;
    int n,i,j;

    h0=0x67452301UL;
    h1=0xefcdab89UL;
    h2=0x98badcfeUL;
    h3=0x10325476UL;
    h4=0xc3d2e1f0UL;

    n=len+1;
    while(n%64!=56)n++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    {
        U64 bits=(U64)len*8;
        for(i=0;i<8;i++)
            data[n+7-i]=(unsigned char)(bits>>(8*i));
    }

    for(i=0;i<n+8;i+=64)
    {
        for(j=0;j<16;j++)
            w[j]=((U32)data[i+j*4]<<24)|
                 ((U32)data[i+j*4+1]<<16)|
                 ((U32)data[i+j*4+2]<<8)|
                 data[i+j*4+3];

        for(j=16;j<80;j++)
            w[j]=ROL(w[j-3]^w[j-8]^w[j-14]^w[j-16],1);

        a=h0;b=h1;c=h2;d=h3;e=h4;

        for(j=0;j<80;j++)
        {
            if(j<20){f=(b&c)|(~b&d);k=0x5a827999UL;}
            else if(j<40){f=b^c^d;k=0x6ed9eba1UL;}
            else if(j<60){f=(b&c)|(b&d)|(c&d);k=0x8f1bbcdcUL;}
            else{f=b^c^d;k=0xca62c1d6UL;}

            t=ROL(a,5)+f+e+k+w[j];

            e=d;
            d=c;
            c=ROL(b,30);
            b=a;
            a=t;
        }

        h0+=a;h1+=b;h2+=c;h3+=d;h4+=e;
    }

    for(i=0;i<4;i++)
    {
        out[i]=h0>>(24-8*i);
        out[i+4]=h1>>(24-8*i);
        out[i+8]=h2>>(24-8*i);
        out[i+12]=h3>>(24-8*i);
        out[i+16]=h4>>(24-8*i);
    }
}


/* ================= SHA-256 ================= */

#define RR(x,n) ((x>>n)|(x<<(32-n)))
#define CH(x,y,z) ((x&y)^(~x&z))
#define MAJ(x,y,z) ((x&y)^(x&z)^(y&z))
#define E0(x) (RR(x,2)^RR(x,13)^RR(x,22))
#define E1(x) (RR(x,6)^RR(x,11)^RR(x,25))
#define S0(x) (RR(x,7)^RR(x,18)^(x>>3))
#define S1(x) (RR(x,17)^RR(x,19)^(x>>10))

U32 K256[64]={
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

void sha256(char *msg,int len,unsigned char out[32])
{
    unsigned char data[128];
    U32 w[64],h[8];
    U32 a,b,c,d,e,f,g,hh,t1,t2;
    int n,i,j;

    h[0]=0x6a09e667UL;h[1]=0xbb67ae85UL;
    h[2]=0x3c6ef372UL;h[3]=0xa54ff53aUL;
    h[4]=0x510e527fUL;h[5]=0x9b05688cUL;
    h[6]=0x1f83d9abUL;h[7]=0x5be0cd19UL;

    n=len+1;
    while(n%64!=56)n++;

    memset(data,0,sizeof(data));
    memcpy(data,msg,len);
    data[len]=0x80;

    {
        U64 bits=(U64)len*8;
        for(i=0;i<8;i++)
            data[n+7-i]=(unsigned char)(bits>>(8*i));
    }

    for(i=0;i<n+8;i+=64)
    {
        for(j=0;j<16;j++)
            w[j]=((U32)data[i+j*4]<<24)|
                 ((U32)data[i+j*4+1]<<16)|
                 ((U32)data[i+j*4+2]<<8)|
                 data[i+j*4+3];

        for(j=16;j<64;j++)
            w[j]=S1(w[j-2])+w[j-7]+S0(w[j-15])+w[j-16];

        a=h[0];b=h[1];c=h[2];d=h[3];
        e=h[4];f=h[5];g=h[6];hh=h[7];

        for(j=0;j<64;j++)
        {
            t1=hh+E1(e)+CH(e,f,g)+K256[j]+w[j];
            t2=E0(a)+MAJ(a,b,c);

            hh=g;g=f;f=e;e=d+t1;
            d=c;c=b;b=a;a=t1+t2;
        }

        h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;
        h[4]+=e;h[5]+=f;h[6]+=g;h[7]+=hh;
    }

    for(i=0;i<8;i++)
    {
        out[i*4]=h[i]>>24;
        out[i*4+1]=h[i]>>16;
        out[i*4+2]=h[i]>>8;
        out[i*4+3]=h[i];
    }
}


/* ================= FILE READING ================= */

long getFileSize(char *filename)
{
    FILE *fp;
    long size;

    fp=fopen(filename,"rb");

    if(fp==NULL)
        return -1;

    fseek(fp,0,SEEK_END);
    size=ftell(fp);
    fclose(fp);

    return size;
}


/* ================= MAIN ================= */

int main()
{
    char filename[100];
    char *data;
    long size;
    FILE *fp;

    unsigned char md5Hash[16];
    unsigned char sha1Hash[20];
    unsigned char sha256Hash[32];

    clock_t start,end;

    double md5Time;
    double sha1Time;
    double sha256Time;

    printf("============================================\n");
    printf("       HASH ALGORITHM PERFORMANCE\n");
    printf("============================================\n");

    printf("\nEnter file name: ");
    scanf("%99s",filename);

    size=getFileSize(filename);

    if(size<0)
    {
        printf("\nError: Cannot open file!\n");
        return 1;
    }

    printf("\nFile Size: %ld bytes\n",size);

    fp=fopen(filename,"rb");

    if(fp==NULL)
    {
        printf("Cannot open file!\n");
        return 1;
    }

    data=(char *)malloc(size+1);

    if(data==NULL)
    {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return 1;
    }

    fread(data,1,size,fp);
    data[size]='\0';

    fclose(fp);

    /* MD5 */
    start=clock();
    md5(data,size,md5Hash);
    end=clock();

    md5Time=(double)(end-start)*1000/CLOCKS_PER_SEC;

    /* SHA-1 */
    start=clock();
    sha1(data,size,sha1Hash);
    end=clock();

    sha1Time=(double)(end-start)*1000/CLOCKS_PER_SEC;

    /* SHA-256 */
    start=clock();
    sha256(data,size,sha256Hash);
    end=clock();

    sha256Time=(double)(end-start)*1000/CLOCKS_PER_SEC;

    printf("\n============================================\n");
    printf("Algorithm     Digest Size     Time (ms)\n");
    printf("============================================\n");

    printf("MD5           128 bits        %.6f\n",md5Time);
    printf("SHA-1         160 bits        %.6f\n",sha1Time);
    printf("SHA-256       256 bits        %.6f\n",sha256Time);

    printf("============================================\n");

    printf("\nNote: SHA-384 and SHA-512 require the\n");
    printf("64-bit SHA-512 core. Their digest sizes are:\n");
    printf("SHA-384 : 384 bits\n");
    printf("SHA-512 : 512 bits\n");

    free(data);

    return 0;
}
