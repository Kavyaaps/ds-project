// Toggle the credited amount field based on user input
function toggleCreditAmount() {
    const credited = document.getElementById('credited').value;
    const creditSection = document.getElementById('credit_section');
    if (credited === 'yes') {
        creditSection.style.display = 'block';
    } else {
        creditSection.style.display = 'none';
    }
}

// Process the debit transaction with validation checks
function processTransaction() {
    const accountHolder = document.getElementById('account_holder').value;
    let balance = parseFloat(document.getElementById('balance').value);
    const debitAmount = parseFloat(document.getElementById('debit_amount').value);
    const credited = document.getElementById('credited').value;
    let creditedAmount = 0;

    // Validation checks
    if (accountHolder.trim() === "") {
        alert("Please enter the account holder's name.");
        return;
    }
    if (isNaN(balance) || balance < 0) {
        alert("Please enter a valid balance.");
        return;
    }
    if (isNaN(debitAmount) || debitAmount <= 0) {
        alert("Please enter a valid debit amount.");
        return;
    }
    if (credited === 'yes') {
        creditedAmount = parseFloat(document.getElementById('credited_amount').value);
        if (isNaN(creditedAmount) || creditedAmount <= 0) {
            alert("Please enter a valid credited amount.");
            return;
        }
        balance += creditedAmount;  // Add credited amount to balance
        alert(`Amount credited: ${creditedAmount.toFixed(2)}. New balance: ${balance.toFixed(2)}`);
    }

    // Process the debit transaction
    let result = "";
    if (debitAmount > balance) {
        result = "Transaction cannot take place. Insufficient balance.";
        document.getElementById('success_message').style.display = 'none';  // Hide success message
    } else {
        balance -= debitAmount;
        result = `Amount debited: ${debitAmount.toFixed(2)}. New balance: ${balance.toFixed(2)}`;
        document.getElementById('success_message').style.display = 'block';  // Show success message
    }

    document.getElementById('result').innerText = result;
}
