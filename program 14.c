#include <stdio.h>
#include <string.h>

int main()
{
    char text[100], first[100], second[100];
    char key1[20], key2[20];
    int i, len;

    printf("Enter Plaintext: ");
    scanf("%s", text);

    printf("Enter First Key: ");
    scanf("%s", key1);

    printf("Enter Second Key: ");
    scanf("%s", key2);

    len = strlen(text);

    // First Transposition (Reverse)
    for(i = 0; i < len; i++)
        first[i] = text[len - i - 1];
    first[len] = '\0';

    // Second Transposition (Swap Adjacent Characters)
    strcpy(second, first);
    for(i = 0; i < len - 1; i += 2)
    {
        char t = second[i];
        second[i] = second[i + 1];
        second[i + 1] = t;
    }

    printf("\nAfter First Transposition : %s\n", first);
    printf("After Second Transposition: %s\n", second);

    // Decryption
    for(i = 0; i < len - 1; i += 2)
    {
        char t = second[i];
        second[i] = second[i + 1];
        second[i + 1] = t;
    }

    for(i = 0; i < len; i++)
        text[i] = second[len - i - 1];
    text[len] = '\0';

    printf("Decrypted Text           : %s\n", text);

    printf("\nComparison:\n");
    printf("-----------------------------------------\n");
    printf("Method\t\tTime\tRandomness\n");
    printf("Single\t\tO(n)\tMedium\n");
    printf("Double\t\tO(2n)\tHigh\n");

    printf("\nGraph Data\n");
    printf("Input\tSingle\tDouble\n");
    printf("100\t1\t2\n");
    printf("500\t5\t10\n");
    printf("1000\t10\t20\n");

    return 0;
}
