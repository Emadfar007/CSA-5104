#include <stdio.h>
#include <string.h>

int main()
{
    char password[20], input[20];
    char message[100], hidden[100];

    printf("Set Password: ");
    scanf("%s", password);

    printf("Enter Secret Message: ");
    scanf("%s", message);

    // Hide Message
    strcpy(hidden, message);
    printf("\nMessage Hidden Successfully!\n");

    // Extract Message
    printf("\nEnter Password to Extract: ");
    scanf("%s", input);

    if(strcmp(password, input) == 0)
        printf("Hidden Message: %s\n", hidden);
    else
        printf("Wrong Password! Access Denied.\n");

    return 0;
}
