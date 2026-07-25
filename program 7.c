#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main() {
    char plain[500], cipher[500], key[26], temp[26];
    int freq[26] = {0}, i, j;

    // Generate random key
    for(i = 0; i < 26; i++)
        temp[i] = 'A' + i;

    srand(time(NULL));
    for(i = 25; i >= 0; i--) {
        j = rand() % (i + 1);
        char t = temp[i];
        temp[i] = temp[j];
        temp[j] = t;
    }

    for(i = 0; i < 26; i++)
        key[i] = temp[i];

    printf("Random Key:\n");
    for(i = 0; i < 26; i++)
        printf("%c->%c ", 'A' + i, key[i]);

    printf("\n\nEnter a paragraph:\n");
    fgets(plain, sizeof(plain), stdin);

    // Encrypt
    for(i = 0; plain[i] != '\0'; i++) {
        if(isalpha(plain[i])) {
            if(isupper(plain[i]))
                cipher[i] = key[plain[i] - 'A'];
            else
                cipher[i] = tolower(key[plain[i] - 'a']);

            freq[toupper(cipher[i]) - 'A']++;
        }
        else
            cipher[i] = plain[i];
    }
    cipher[i] = '\0';

    printf("\nEncrypted Text:\n%s\n", cipher);

    printf("\nLetter Frequencies:\n");
    for(i = 0; i < 26; i++)
        if(freq[i] > 0)
            printf("%c : %d\n", 'A' + i, freq[i]);

    // Top 3 frequent letters
    printf("\nTop 3 Frequent Letters:\n");
    for(i = 0; i < 3; i++) {
        int max = -1, pos = -1;
        for(j = 0; j < 26; j++) {
            if(freq[j] > max) {
                max = freq[j];
                pos = j;
            }
        }
        if(pos != -1) {
            printf("%d. %c : %d times\n", i + 1, 'A' + pos, max);
            freq[pos] = -1;
        }
    }

    return 0;
}
