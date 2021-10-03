#include <iostream>
#include "savings.h"

using std::string;
using namespace std;

string SavingsAccount::deposit()
{
  int amount = this->generate_amount(100, 150);
  cout << "Amount deposited for savings(100 - 150): " << amount << endl;
  cout << "prev balance: " << to_string(this->balance) << endl;
  this->balance += amount;
  cout << "new balance: " << to_string(this->balance) << endl;
  this->no_deposits++;
  string message = "DEPOSIT " + this->strToUpper(this->type) + " " + to_string(amount);
  return message;
}

string SavingsAccount::deposit(int amount)
{
  cout << "\nSavings deposit during transfer" << endl;
  cout << "---------------------------------------" << endl;
  cout << "Amount deposited for savings(100 - 150): " << amount << endl;
  cout << "prev balance: " << to_string(this->balance) << endl;
  this->balance += amount;
  cout << "new balance: " << to_string(this->balance) << endl;
  this->no_deposits++;
  string message = "DEPOSIT " + this->strToUpper(this->type) + " " + to_string(amount);
  return message;
}

string SavingsAccount::withdraw()
{
  int amount = this->generate_amount(100, 150);
  string message = "WITHDRAWAL " + this->strToUpper(this->type) + " " + to_string(amount);

  if (amount > this->balance)
  {
    message += " (REJECTED)";
    this->no_rejected++;
    return message;
  }

  cout << "prev balance " << this->balance << endl;
  balance -= amount;
  cout << "new balance " << this->balance << endl;
  this->no_withdrawals++;
  return message;
}

string SavingsAccount::withdraw(int amount)
{
  string message = "WITHDRAWAL " + this->strToUpper(this->type) + " " + to_string(amount);

  if (amount > this->balance)
  {
    message += " (REJECTED)";
    this->no_rejected++;
    return message;
  }
  cout << "\nsavings withdrawing during transfer" << endl;
  cout << "---------------------------------------" << endl;
  cout << "prev balance " << this->balance << endl;
  balance -= amount;
  cout << "new balance " << this->balance << endl;
  this->no_withdrawals++;
  return message;
}