// This file is a thorough implementation of the header file bank account
#include <stdlib.h>
#include <string.h>
#include "bank_account.h"

struct BankAcc {
    char name[100];
    double balance; // Hidden from the outside!
};

BankAcc* create(const char* name, double initial_balance) {
    BankAcc* acc = malloc(sizeof(BankAcc));
    if (acc) {
        strncpy(acc->name, name, 99);
        acc->balance = (initial_balance > 0) ? initial_balance : 0;
    }
    return acc;
}

void deposit(BankAcc* account, double amount) {
    if (amount > 0) {
        account->balance += amount; // We can access .balance here
    }
}

double get_balance(BankAcc* account) {
    return account->balance;
}

void destroy_account(BankAcc* account) {
    free(account);
}