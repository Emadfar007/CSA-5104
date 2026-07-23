/*
 * Program 4: Bell-LaPadula Access Checker
 * Aim: To simulate access control using the Bell-LaPadula security model.
 *
 * Security Levels (low to high):
 *  1. Public
 *  2. Confidential
 *  3. Secret
 *  4. Top Secret
 *
 * Rules:
 *  - No Read Up   : A subject cannot read an object at a higher level.
 *  - No Write Down: A subject cannot write to an object at a lower level.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Returns the numeric rank of a security level, or -1 if invalid */
int getLevel(char *level) {
    /* normalize spaces are already handled since we read line by line */
    if (strcmp(level, "Public") == 0) return 1;
    if (strcmp(level, "Confidential") == 0) return 2;
    if (strcmp(level, "Secret") == 0) return 3;
    if (strcmp(level, "Top Secret") == 0) return 4;
    return -1;
}

void toProperCase(char *str) {
    /* Leaves the string as entered; comparison is done as-is */
}

int main(int argc, char *argv[]) {
    char userLevelStr[30];
    char fileLevelStr[30];
    char operation[10];
    int userLevel, fileLevel;

    if (argc > 3) {
        strncpy(userLevelStr, argv[1], sizeof(userLevelStr) - 1);
        userLevelStr[sizeof(userLevelStr) - 1] = '\0';
        strncpy(fileLevelStr, argv[2], sizeof(fileLevelStr) - 1);
        fileLevelStr[sizeof(fileLevelStr) - 1] = '\0';
        strncpy(operation, argv[3], sizeof(operation) - 1);
        operation[sizeof(operation) - 1] = '\0';
    } else {
        printf("User Level : ");
        fgets(userLevelStr, sizeof(userLevelStr), stdin);
        userLevelStr[strcspn(userLevelStr, "\n")] = '\0';

        printf("File Level : ");
        fgets(fileLevelStr, sizeof(fileLevelStr), stdin);
        fileLevelStr[strcspn(fileLevelStr, "\n")] = '\0';

        printf("Operation : ");
        fgets(operation, sizeof(operation), stdin);
        operation[strcspn(operation, "\n")] = '\0';
    }

    userLevel = getLevel(userLevelStr);
    fileLevel = getLevel(fileLevelStr);

    if (userLevel == -1 || fileLevel == -1) {
        printf("Invalid Security Level Entered\n");
        return 0;
    }

    if (strcmp(operation, "Read") == 0) {
        if (fileLevel > userLevel) {
            printf("Access Denied\n");
            printf("Reason : No Read Up\n");
        } else {
            printf("Access Granted\n");
        }
    } else if (strcmp(operation, "Write") == 0) {
        if (fileLevel < userLevel) {
            printf("Access Denied\n");
            printf("Reason : No Write Down\n");
        } else {
            printf("Access Granted\n");
        }
    } else {
        printf("Invalid Operation\n");
    }

    return 0;
}
