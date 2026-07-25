#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plain[500], cipher[500], decrypt[500], key[100];
    int i, j, klen;

    printf("Enter Plaintext: ");
    fgets(plain, sizeof(plain), stdin);
    plain[strcspn(plain, "\n")] = 0;

    printf("Enter Keyword: ");
    scanf("%s", key);
    klen = strlen(key);

    // Encryption
    for(i = 0, j = 0; plain[i]; i++) {
        if(isalpha(plain[i])) {
            char base = isupper(plain[i]) ? 'A' : 'a';
            cipher[i] = ((plain[i]-base)+(toupper(key[j%klen])-'A'))%26 + base;
            j++;
        } else
            cipher[i] = plain[i];
    }
    cipher[i] = '\0';

    printf("\nCiphertext: %s\n", cipher);

    // Decryption
    for(i = 0, j = 0; cipher[i]; i++) {
        if(isalpha(cipher[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';
            decrypt[i] = ((cipher[i]-base)-(toupper(key[j%klen])-'A')+26)%26 + base;
            j++;
        } else
            decrypt[i] = cipher[i];
    }
    decrypt[i] = '\0';

    printf("Decrypted Text: %s\n", decrypt);

    // Basic Kasiski Analysis
    printf("\nRepeated 3-letter sequences:\n");
    int found = 0;
    for(i = 0; i < strlen(cipher)-2; i++) {
        for(j = i+3; j < strlen(cipher)-2; j++) {
            if(cipher[i]==cipher[j] &&
               cipher[i+1]==cipher[j+1] &&
               cipher[i+2]==cipher[j+2]) {

                printf("%.3s found at %d and %d  Distance = %d\n",
                       &cipher[i], i, j, j-i);
                printf("Estimated Key Length ˜ %d\n", j-i);
                found = 1;
            }
        }
    }

    if(!found)
        printf("No repeated sequences found. Unable to estimate key length.\n");

    return 0;
}
