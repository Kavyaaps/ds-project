#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum size for the queue
#define MAX_QUEUE_SIZE 100

// BankAccount structure
struct BankAccount {
    char account_holder[50];
    float balance;
};

// Transaction structure (to store debit or credit transactions)
struct Transaction {
    char type[10]; // "credit" or "debit"
    float amount;
};

// Queue structure to handle transactions
struct Queue {
    struct Transaction transactions[MAX_QUEUE_SIZE];
    int front;
    int rear;
};

// Function to initialize the queue
void initQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is full
int isFull(struct Queue *q) {
    return (q->rear == MAX_QUEUE_SIZE - 1);
}

// Function to check if the queue is empty
int isEmpty(struct Queue *q) {
    return (q->front == -1 || q->front > q->rear);
}

// Function to add a transaction to the queue
void enqueue(struct Queue *q, struct Transaction t) {
    if (isFull(q)) {
        printf("Queue is full. Cannot process more transactions.\n");
        return;
    }
    if (q->front == -1) q->front = 0;  // Set front to 0 if first element is inserted
    q->rear++;
    q->transactions[q->rear] = t;
}

// Function to remove a transaction from the queue
struct Transaction dequeue(struct Queue *q) {
    struct Transaction emptyTransaction = {"", 0};
    if (isEmpty(q)) {
        printf("Queue is empty. No transactions to process.\n");
        return emptyTransaction;
    }
    struct Transaction t = q->transactions[q->front];
    q->front++;
    return t;
}

// Function to process the transactions from the queue
void processTransactions(struct BankAccount *account, struct Queue *q) {
    while (!isEmpty(q)) {
        struct Transaction t = dequeue(q);
        if (strcmp(t.type, "credit") == 0) {
            account->balance += t.amount;
            printf("Amount credited: %.2f. New balance: %.2f\n", t.amount, account->balance);
        } else if (strcmp(t.type, "debit") == 0) {
            if (t.amount > account->balance) {
                printf("Transaction cannot take place. Insufficient balance.\n");
            } else {
                account->balance -= t.amount;
                printf("Amount debited: %.2f. New balance: %.2f\n", t.amount, account->balance);
            }
        }
    }
}

int main() {
    struct BankAccount account;
    struct Queue queue;
    struct Transaction transaction;
    int num_transactions, i;
    
    initQueue(&queue);

    // Get user input for account details
    printf("Enter the account holder's name: ");
    fgets(account.account_holder, sizeof(account.account_holder), stdin);
    account.account_holder[strcspn(account.account_holder, "\n")] = '\0'; // Remove newline

    printf("Enter the current amount in the account: ");
    scanf("%f", &account.balance);

    // Get number of transactions
    printf("Enter the number of transactions: ");
    scanf("%d", &num_transactions);

    // Input the transactions
    for (i = 0; i < num_transactions; i++) {
        printf("Enter transaction type (credit/debit): ");
        scanf("%s", transaction.type);

        printf("Enter transaction amount: ");
        scanf("%f", &transaction.amount);

        // Add the transaction to the queue
        enqueue(&queue, transaction);
    }

    // Process all transactions in the queue
    processTransactions(&account, &queue);

    return 0;
} 
