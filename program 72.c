#include <stdio.h>
#include <string.h>

struct Email
{
    char sender[100];
    char subject[200];
    float spamProbability;
    float hamProbability;
};

int main()
{
    struct Email email;

    printf("=====================================================\n");
    printf("      Naive Bayes Spam Classifier Simulation\n");
    printf("=====================================================\n");

    printf("Enter Sender Email : ");
    scanf("%99s", email.sender);

    getchar();

    printf("Enter Email Subject : ");
    fgets(email.subject, sizeof(email.subject), stdin);

    printf("Enter Spam Probability (0-1): ");
    scanf("%f", &email.spamProbability);

    printf("Enter Legitimate Email Probability (0-1): ");
    scanf("%f", &email.hamProbability);

    printf("\n=====================================================\n");
    printf("Email Details\n");
    printf("=====================================================\n");

    printf("Sender             : %s\n", email.sender);
    printf("Subject            : %s", email.subject);
    printf("Spam Probability   : %.2f\n", email.spamProbability);
    printf("Ham Probability    : %.2f\n", email.hamProbability);

    printf("\n=====================================================\n");
    printf("Classification Result\n");
    printf("=====================================================\n");

    if(email.spamProbability > email.hamProbability)
    {
        printf("Email Classification : SPAM\n");
        printf("Naive Bayes Decision : Spam Probability is Higher\n");
    }
    else if(email.hamProbability > email.spamProbability)
    {
        printf("Email Classification : LEGITIMATE\n");
        printf("Naive Bayes Decision : Ham Probability is Higher\n");
    }
    else
    {
        printf("Email Classification : UNCERTAIN\n");
        printf("Both probabilities are equal.\n");
    }

    return 0;
}
