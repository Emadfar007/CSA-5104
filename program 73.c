#include <stdio.h>
#include <string.h>

struct SpamDetection
{
    char sender[100];
    char subject[200];
    float svmAccuracy;
    float nbAccuracy;
    char classification[20];
};

int main()
{
    struct SpamDetection email;

    printf("=====================================================\n");
    printf(" SVM vs Naive Bayes Spam Detection Comparison\n");
    printf("=====================================================\n");

    printf("Enter Sender Email : ");
    scanf("%99s", email.sender);

    getchar();

    printf("Enter Email Subject : ");
    fgets(email.subject, sizeof(email.subject), stdin);

    printf("Enter SVM Accuracy (%%): ");
    scanf("%f", &email.svmAccuracy);

    printf("Enter Naive Bayes Accuracy (%%): ");
    scanf("%f", &email.nbAccuracy);

    printf("Enter Email Classification (SPAM/LEGITIMATE): ");
    scanf("%19s", email.classification);

    printf("\n=====================================================\n");
    printf("Spam Detection Report\n");
    printf("=====================================================\n");

    printf("Sender                : %s\n", email.sender);
    printf("Subject               : %s", email.subject);
    printf("Email Classification  : %s\n", email.classification);

    printf("\nMachine Learning Accuracy\n");
    printf("------------------------------\n");
    printf("Support Vector Machine : %.2f%%\n", email.svmAccuracy);
    printf("Naive Bayes           : %.2f%%\n", email.nbAccuracy);

    printf("\n=====================================================\n");
    printf("Comparison Result\n");
    printf("=====================================================\n");

    if(email.svmAccuracy > email.nbAccuracy)
    {
        printf("Best Algorithm : Support Vector Machine (SVM)\n");
        printf("Accuracy Difference : %.2f%%\n",
               email.svmAccuracy - email.nbAccuracy);
    }
    else if(email.nbAccuracy > email.svmAccuracy)
    {
        printf("Best Algorithm : Naive Bayes\n");
        printf("Accuracy Difference : %.2f%%\n",
               email.nbAccuracy - email.svmAccuracy);
    }
    else
    {
        printf("Both Algorithms have the Same Accuracy.\n");
    }

    return 0;
}
