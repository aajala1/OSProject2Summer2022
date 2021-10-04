#include <iostream>
#include "checking.h"

using std::string;
using namespace std;

CheckingAccount::CheckingAccount()
                : IAccount()
{}
CheckingAccount::CheckingAccount(string t)
                : IAccount(t) 
{}
string CheckingAccount::deposit()
{
  int amount = this->generate_amount(50, 100);
  cout << "Amount deposited for checking(50 - 100): " << amount << endl;
  cout << "prev balance: " << to_string(this->balance) << endl;
  this->balance += amount;
  cout << "new balance: " << to_string(this->balance) << endl;
  this->no_deposits++;
  string message = "DEPOSIT " + this->strToUpper(this->type) + " " + to_string(amount);
  return message;
}

string CheckingAccount::deposit(int amount)
{
  cout << "\nChecking deposite during transfer" << endl;
  cout << "---------------------------------------" << endl;
  cout << "prev balance: " << to_string(this->balance) << endl;
  this->balance += amount;
  cout << "new balance: " << to_string(this->balance) << endl;
  this->no_deposits++;
  string message = "DEPOSIT " + this->strToUpper(this->type) + " " + to_string(amount);
  return message;
}

string CheckingAccount::withdraw()
{
  int amount = generate_amount(50, 100);
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

string CheckingAccount::withdraw(int amount)
{
  string message = "WITHDRAWAL " + this->strToUpper(this->type) + " " + to_string(amount);
  if (amount > this->balance)
  {
    message += " (REJECTED)";
    this->no_rejected++;
    return message;
  }
  cout << "\nChecking withdrawing during transfer" << endl;
  cout << "---------------------------------------" << endl;
  cout << "prev balance " << this->balance << endl;
  balance -= amount;
  cout << "new balance " << this->balance << endl;
  this->no_withdrawals++;
  return message;
}