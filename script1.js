class BankAccount {
    constructor(accountHolder, balance) {
        this.accountHolder = accountHolder;
        this.balance = parseFloat(balance);
    }
}

class Transaction {
    constructor(type, amount) {
        this.type = type;
        this.amount = parseFloat(amount);
    }
}

class Queue {
    constructor() {
        this.transactions = [];
    }

    enqueue(transaction) {
        if (this.transactions.length < 100) {
            this.transactions.push(transaction);
        } else {
            alert("Queue is full. Cannot process more transactions.");
        }
    }

    dequeue() {
        return this.transactions.shift();
    }

    isEmpty() {
        return this.transactions.length === 0;
    }
}

let bankAccount = null;
let transactionQueue = new Queue();

function createAccount() {
    const accountHolder = document.getElementById("accountHolder").value;
    const balance = document.getElementById("balance").value;

    if (accountHolder && balance) {
        bankAccount = new BankAccount(accountHolder, balance);
        displayOutput(`Account created for ${accountHolder} with initial balance $${balance}`);
    } else {
        alert("Please fill out all account details.");
    }
}

function addTransaction() {
    const type = document.getElementById("transactionType").value;
    const amount = document.getElementById("transactionAmount").value;

    if (!bankAccount) {
        alert("Please create an account first.");
        return;
    }

    if (amount > 0) {
        const transaction = new Transaction(type, amount);
        transactionQueue.enqueue(transaction);
        displayOutput(`Added ${type} transaction of $${amount}`);
    } else {
        alert("Please enter a valid transaction amount.");
    }
}

function processTransactions() {
    if (!bankAccount) {
        alert("Please create an account first.");
        return;
    }

    while (!transactionQueue.isEmpty()) {
        const transaction = transactionQueue.dequeue();
        if (transaction.type === "credit") {
            bankAccount.balance += transaction.amount;
            displayOutput(`Amount credited: $${transaction.amount}. New balance: $${bankAccount.balance}`);
        } else if (transaction.type === "debit") {
            if (transaction.amount > bankAccount.balance) {
                displayOutput("Transaction cannot take place. Insufficient balance.");
            } else {
                bankAccount.balance -= transaction.amount;
                displayOutput(`Amount debited: $${transaction.amount}. New balance: $${bankAccount.balance}`);
            }
        }
    }
}

function displayOutput(message) {
    const outputDiv = document.getElementById("output");
    const messageElement = document.createElement("p");
    messageElement.textContent = message;
    outputDiv.appendChild(messageElement);
}
