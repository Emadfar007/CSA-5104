#include <stdio.h>
#include <string.h>

int main()
{
    char customer[50];
    char merchant[50];
    char gateway[50];
    char order[100];

    printf("============================================\n");
    printf("        SET PROTOCOL SIMULATION\n");
    printf("============================================\n");

    printf("\nEnter Customer Name: ");
    fgets(customer, sizeof(customer), stdin);
    customer[strcspn(customer, "\n")] = '\0';

    printf("Enter Merchant Name: ");
    fgets(merchant, sizeof(merchant), stdin);
    merchant[strcspn(merchant, "\n")] = '\0';

    printf("Enter Payment Gateway: ");
    fgets(gateway, sizeof(gateway), stdin);
    gateway[strcspn(gateway, "\n")] = '\0';

    printf("Enter Order Details: ");
    fgets(order, sizeof(order), stdin);
    order[strcspn(order, "\n")] = '\0';

    printf("\n============================================\n");
    printf("          SET TRANSACTION PROCESS\n");
    printf("============================================\n");

    /* Customer */
    printf("\n1. CUSTOMER\n");
    printf("Customer: %s\n", customer);
    printf("Order: %s\n", order);
    printf("Customer sends order and payment request.");

    /* Certificate Authority */
    printf("\n2. CERTIFICATE AUTHORITY\n");
    printf("CA verifies customer certificate.\n");
    printf("CA verifies merchant certificate.\n");
    printf("Certificates are VALID.");

    /* Merchant */
    printf("\n3. MERCHANT\n");
    printf("Merchant: %s\n", merchant);
    printf("Order received successfully.\n");
    printf("Merchant forwards payment information.");

    /* Payment Gateway */
    printf("\n4. PAYMENT GATEWAY\n");
    printf("Gateway: %s\n", gateway);
    printf("Payment information received.\n");
    printf("Payment authentication successful.\n");
    printf("Payment approved.");

    /* Merchant confirmation */
    printf("\n5. MERCHANT\n");
    printf("Payment confirmation received.\n");
    printf("Order processing started.");

    /* Customer confirmation */
    printf("\n6. CUSTOMER\n");
    printf("Transaction completed successfully.");

    printf("\n============================================\n");
    printf("        SET TRANSACTION SUCCESSFUL\n");
    printf("============================================\n");

    return 0;
}
