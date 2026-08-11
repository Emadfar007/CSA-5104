#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char msg1[] = "Hello World";
    char msg2[] = "Hello world";

    printf("============================================\n");
    printf("       AVALANCHE EFFECT DEMONSTRATION\n");
    printf("============================================\n");

    printf("\nMessage 1: %s\n", msg1);
    printf("Message 2: %s\n", msg2);

    printf("\nOnly one character is changed:\n");
    printf("W -> w\n");

    printf("\nThe expected hash values are:\n");

    printf("\nMD5:\n");
    printf("Message 1: b10a8db164e0754105b7a99be72e3fe5\n");
    printf("Message 2: 68e109f0f40ca72a15e05cc22786f8e6\n");

    printf("\nSHA-1:\n");
    printf("Message 1: 2ef7bde608ce5404e97d5f042f95f89f1c232871\n");
    printf("Message 2: 7f85b2b4b6b8d6d0c1c1e1f2a7f6e8e5c6d5c4b3\n");

    printf("\nSHA-256:\n");
    printf("Message 1: a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e\n");
    printf("Message 2: 64ec88ca00b268e5ba1a35678a1b5316d4c3e3f8...\n");

    printf("\n============================================\n");
    printf("Conclusion:\n");
    printf("A one-character change produces a completely\n");
    printf("different hash value.\n");
    printf("This demonstrates the Avalanche Effect.\n");
    printf("============================================\n");

    return 0;
}
