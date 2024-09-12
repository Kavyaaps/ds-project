#include <stdio.h>
#include <stdlib.h>

// BankAccount structure
struct BankAccount {
    char account_holder[50];
    float balance;
};

// Function to process the debit transaction
void processDebit(struct BankAccount* account, float debit_amount) {
    if (debit_amount > account->balance) {
        printf("Transaction cannot take place. Insufficient balance.\n");
    } else {
        account->balance -= debit_amount;
        printf("Amount debited: %.2f. New balance: %.2f\n", debit_amount, account->balance);
    }
}

int main() {
    struct BankAccount account;
    char credited;
    float debit_amount;
    float credited_amount;

    // Get user inputs
    printf("Enter the account holder's name: ");
    fgets(account.account_holder, sizeof(account.account_holder), stdin);

    printf("Enter the current amount in the account: ");
    scanf("%f", &account.balance);

    printf("Enter the amount you want to debit: ");
    scanf("%f", &debit_amount);

    // Check if any amount has been credited
    printf("Has any amount been credited (yes/no)? ");
    scanf(" %c", &credited);  // space before %c to handle newline character

    if (credited == 'y' || credited == 'Y') {
        printf("Enter the credited amount: ");
        scanf("%f", &credited_amount);
        account.balance += credited_amount;
        printf("Amount credited: %.2f. New balance: %.2f\n", credited_amount, account.balance);
    }

    // Process the debit transaction
    processDebit(&account, debit_amount);

    return 0;
}