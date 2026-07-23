/*
 * Program 2: Login Authentication
 * Aim: To create a simple login authentication program using a
 *      username and password.
 *
 * Store a predefined username and password.
 * Ask the user to enter login credentials.
 * Display whether login is successful or unsuccessful.
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char storedUsername[50] = "admin";
    char storedPassword[50] = "admin123";
    char username[50], password[50];

    if (argc > 2) {
        /* allow non-interactive testing: program username password */
        strncpy(username, argv[1], sizeof(username) - 1);
        username[sizeof(username) - 1] = '\0';
        strncpy(password, argv[2], sizeof(password) - 1);
        password[sizeof(password) - 1] = '\0';
    } else {
        printf("Username : ");
        if (fgets(username, sizeof(username), stdin) == NULL) return 1;
        /* strip newline / carriage return */
        size_t len = strlen(username);
        if (len > 0 && (username[len - 1] == '\n' || username[len - 1] == '\r')) {
            username[--len] = '\0';
            if (len > 0 && username[len - 1] == '\r') username[--len] = '\0';
        }

        printf("Password : ");
        if (fgets(password, sizeof(password), stdin) == NULL) return 1;
        len = strlen(password);
        if (len > 0 && (password[len - 1] == '\n' || password[len - 1] == '\r')) {
            password[--len] = '\0';
            if (len > 0 && password[len - 1] == '\r') password[--len] = '\0';
        }
    }

    if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
        printf("Login Successful\n");
    } else {
        printf("Invalid Username or Password\n");
    }

    return 0;
}
