/*
 * Program 1: Password Strength Checker
 * Aim: To write a program that checks whether a password is strong or weak.
 *
 * A strong password should have:
 *  - At least 8 characters
 *  - One uppercase letter
 *  - One lowercase letter
 *  - One digit
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char password[100];
    int hasUpper = 0, hasLower = 0, hasDigit = 0;
    int length;

    if (argc > 1) {
        /* allow non-interactive test via argv[1] */
        strncpy(password, argv[1], sizeof(password) - 1);
        password[sizeof(password) - 1] = '\0';
        length = strlen(password);
    } else {
        printf("Enter Password: ");
        if (fgets(password, sizeof(password), stdin) == NULL) {
            printf("No input received.\n");
            return 1;
        }

        /* remove trailing newline if present */
        length = strlen(password);
        if (length > 0 && password[length - 1] == '\n') {
            password[length - 1] = '\0';
            length--;
        }
    }

    for (int i = 0; i < length; i++) {
        unsigned char c = (unsigned char)password[i];
        if (isupper(c))
            hasUpper = 1;
        if (islower(c))
            hasLower = 1;
        if (isdigit(c))
            hasDigit = 1;
    }

    int okLength = (length >= 8);

    if (okLength && hasUpper && hasLower && hasDigit) {
        printf("Password is Strong.\n");
    } else {
        printf("Password is Weak. The password failed the following checks:\n");
        if (!okLength)
            printf(" - Minimum length of 8 characters\n");
        if (!hasUpper)
            printf(" - At least one uppercase letter\n");
        if (!hasLower)
            printf(" - At least one lowercase letter\n");
        if (!hasDigit)
            printf(" - At least one digit\n");
    }

    return 0;
}
