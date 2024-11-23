// A simple C program to implement a bank management system using data structures

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A structure to store customer information
struct customer {
    int acc_no; // account number
    char name[50]; // name
    char address[100]; // address
    char phone[15]; // phone number
    float balance; // balance
    struct customer *next; // pointer to next customer
};

// A structure to store transaction information
struct transaction {
    int acc_no; // account number
    char type[10]; // type of transaction (deposit or withdraw)
    float amount; // amount of transaction
    struct transaction *next; // pointer to next transaction
};

// A global variable to store the head of the customer list
struct customer *head = NULL;

// A global variable to store the head of the transaction list
struct transaction *t_head = NULL;

// A function to create a new customer and add it to the list
void create_customer() {
    // Allocate memory for a new customer
    struct customer *new_customer = (struct customer *)malloc(sizeof(struct customer));
    // Prompt the user to enter the customer details
    printf("Enter the account number: ");
    scanf("%d", &new_customer->acc_no);
    printf("Enter the name: ");
    scanf("%s", new_customer->name);
    printf("Enter the address: ");
    scanf("%s", new_customer->address);
    printf("Enter the phone number: ");
    scanf("%s", new_customer->phone);
    printf("Enter the initial balance: ");
    scanf("%f", &new_customer->balance);
    // Set the next pointer to NULL
    new_customer->next = NULL;
    // If the list is empty, make the new customer the head
    if (head == NULL) {
        head = new_customer;
    }
    // Else, traverse the list and insert the new customer at the end
    else {
        struct customer *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_customer;
    }
    // Display a success message
    printf("Customer created successfully!\n");
}

// A function to display the details of a customer given the account number
void display_customer(int acc_no) {
    // Traverse the list and search for the customer with the given account number
    struct customer *temp = head;
    while (temp != NULL && temp->acc_no != acc_no) {
        temp = temp->next;
    }
    // If the customer is found, display the details
    if (temp != NULL) {
        printf("Account number: %d\n", temp->acc_no);
        printf("Name: %s\n", temp->name);
        printf("Address: %s\n", temp->address);
        printf("Phone number: %s\n", temp->phone);
        printf("Balance: %.2f\n", temp->balance);
    }
    // Else, display an error message
    else {
        printf("Customer not found!\n");
    }
}

// A function to deposit money to a customer account and record the transaction
void deposit(int acc_no, float amount) {
    // Traverse the list and search for the customer with the given account number
    struct customer *temp = head;
    while (temp != NULL && temp->acc_no != acc_no) {
        temp = temp->next;
    }
    // If the customer is found, update the balance and display a success message
    if (temp != NULL) {
        temp->balance += amount;
        printf("Deposit successful!\n");
        printf("New balance: %.2f\n", temp->balance);
    }
    // Else, display an error message
    else {
        printf("Customer not found!\n");
        return;
    }
    // Allocate memory for a new transaction
    struct transaction *new_transaction = (struct transaction *)malloc(sizeof(struct transaction));
    // Store the transaction details
    new_transaction->acc_no = acc_no;
    strcpy(new_transaction->type, "deposit");
    new_transaction->amount = amount;
    // Set the next pointer to NULL
    new_transaction->next = NULL;
    // If the transaction list is empty, make the new transaction the head
    if (t_head == NULL) {
        t_head = new_transaction;
    }
    // Else, traverse the list and insert the new transaction at the end
    else {
        struct transaction *t_temp = t_head;
        while (t_temp->next != NULL) {
            t_temp = t_temp->next;
        }
        t_temp->next = new_transaction;
    }
}

// A function to withdraw money from a customer account and record the transaction
void withdraw(int acc_no, float amount) {
    // Traverse the list and search for the customer with the given account number
    struct customer *temp = head;
    while (temp != NULL && temp->acc_no != acc_no) {
        temp = temp->next;
    }
    // If the customer is found, check if the balance is sufficient and update the balance
    if (temp != NULL) {
        if (temp->balance >= amount) {
            temp->balance -= amount;
            printf("Withdrawal successful!\n");
            printf("New balance: %.2f\n", temp->balance);
        }
        // Else, display an error message
        else {
            printf("Insufficient balance!\n");
            return;
        }
    }
    // Else, display an error message
    else {
        printf("Customer not found!\n");
        return;
    }
    // Allocate memory for a new transaction
    struct transaction *new_transaction = (struct transaction *)malloc(sizeof(struct transaction));
    // Store the transaction details
    new_transaction->acc_no = acc_no;
    strcpy(new_transaction->type, "withdraw");
    new_transaction->amount = amount;
    // Set the next pointer to NULL
    new_transaction->next = NULL;
    // If the transaction list is empty, make the new transaction the head
    if (t_head == NULL) {
        t_head = new_transaction;
    }
    // Else, traverse the list and insert the new transaction at the end
    else {
        struct transaction *t_temp = t_head;
        while (t_temp->next != NULL) {
            t_temp = t_temp->next;
        }
        t_temp->next = new_transaction;
    }
}

// A function to display the transaction history of a customer given the account number
void display_transactions(int acc_no) {
    // Traverse the transaction list and search for the transactions with the given account number
    struct transaction *t_temp = t_head;
    int count = 0; // a variable to count the number of transactions
    while (t_temp != NULL) {
        if (t_temp->acc_no == acc_no) {
            // Display the transaction details
            printf("Transaction %d:\n", ++count);
            printf("Type: %s\n", t_temp->type);
            printf("Amount: %.2f\n", t_temp->amount);
        }
        t_temp = t_temp->next;
    }
    // If no transactions are found, display a message
    if (count == 0) {
        printf("No transactions found!\n");
    }
}

// A function to display the menu and prompt the user to choose an option
void menu() {
    int choice; // a variable to store the user's choice
    int acc_no; // a variable to store the account number
    float amount; // a variable to store the amount
    // Display the menu options
    printf("Welcome to the bank management system!\n");
    printf("Please choose an option:\n");
    printf("1. Create a new customer\n");
    printf("2. Display a customer's details\n");
    printf("3. Deposit money to a customer's account\n");
    printf("4. Withdraw money from a customer's account\n");
    printf("5. Display a customer's transaction history\n");
    printf("6. Exit the program\n");
    // Prompt the user to enter the choice
    printf("Enter your choice: ");
    scanf("%d", &choice);
    // Perform the corresponding action based on the choice
    switch (choice) {
        case 1:
            // Create a new customer
            create_customer();
            break;
        case 2:
            // Display a customer's details
            printf("Enter the account number: ");
            scanf("%d", &acc_no);
            display_customer(acc_no);
            break;
        case 3:
            // Deposit money to a customer's account
            printf("Enter the account number: ");
            scanf("%d", &acc_no);
            printf("Enter the amount to deposit: ");
            scanf("%f", &amount);
            deposit(acc_no, amount);
            break;
        case 4:
            // Withdraw money from a customer's account
            printf("Enter the account number: ");
            scanf("%d", &acc_no);
            printf("Enter the amount to withdraw: ");
            scanf("%f", &amount);
            withdraw(acc_no, amount);
            break;
        case 5:
            // Display a customer's transaction history
            printf("Enter the account number: ");
            scanf("%d", &acc_no);
            display_transactions(acc_no);
            break;
        case 6:
            // Exit the program
            printf("Thank you for using the bank management system!\n");
            exit(0);
            break;
        default:
            // Display an error message for invalid choice
            printf("Invalid choice
