// This is a header file which we can use in the next c file which implements this
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

// Forward declaration: The compiler knows this exists, but not what's in it.
typedef struct BankAcc BankAcc;

// Public "Methods"
BankAcc* create(const char* name, double initial_balance);
void deposit(BankAcc* account, double amount);
double get_balance(BankAcc* account);
void destroy_account(BankAcc* account);

#endif