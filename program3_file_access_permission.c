/*
 * Program 3: File Access Permission Simulation
 * Aim: To simulate file access permission based on user roles.
 *
 * Permissions:
 *  Admin   -> Read, Write, Delete
 *  Faculty -> Read, Write
 *  Student -> Read only
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char role[20];

    if (argc > 1) {
        strncpy(role, argv[1], sizeof(role) - 1);
        role[sizeof(role) - 1] = '\0';
    } else {
        printf("Enter Role: ");
        if (fgets(role, sizeof(role), stdin) == NULL) return 1;
        /* strip trailing newline */
        size_t len = strlen(role);
        if (len > 0 && role[len - 1] == '\n') role[--len] = '\0';
    }

    /* Convert to lowercase for case-insensitive comparison */
    for (int i = 0; role[i]; i++) {
        role[i] = tolower(role[i]);
    }

    printf("Permissions:\n");

    if (strcmp(role, "admin") == 0) {
        printf("Read, Write, Delete\n");
    } else if (strcmp(role, "faculty") == 0) {
        printf("Read, Write\n");
    } else if (strcmp(role, "student") == 0) {
        printf("Read Only\n");
    } else {
        printf("Invalid Role\n");
    }

    return 0;
}
