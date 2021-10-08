#include <iostream>
#include "checking.h"
#include <string.h>

using namespace std;

CheckingAccount::CheckingAccount()
{
  set_type("savings");
}

/* getters */
int CheckingAccount::get_no_deposit(void)
{
  return this->no_deposits;
}

int CheckingAccount::get_no_withdrawals(void)
{
  return this->no_withdrawals;
}

int CheckingAccount::get_no_rejected(void)
{
  return this->no_rejected;
}

int CheckingAccount::get_balance(void)
{
  return this->balance;
}

/* setter */
void CheckingAccount::set_no_deposits(int value)
{
  this->no_deposits = value;
}

void CheckingAccount::set_no_withdrawals(int value)
{
  this->no_withdrawals = value;
}
void CheckingAccount::set_no_rejected(int value)
{
  this->no_rejected = value;
}
void CheckingAccount::set_balance(int value)
{
  this->balance = value;
}
void CheckingAccount::set_type(string value)
{
  this->type = value;
}

// helper functions
int CheckingAccount::generate_amount(int min, int max)
{
  int amount = min + (std::rand() % (max - min + 1));
  return amount;
}

string CheckingAccount::strToUpper(string input)
{
  for (int i = 0; i < input.size(); i++)
  {
    input.at(i) = toupper(input.at(i));
  }
  return input;
}

void CheckingAccount::toString()
{
  std::cout << "Account type: " << this->type << std::endl;
  std::cout << "Balance: " << this->balance << std::endl;
  std::cout << "# of withdrawals: " << this->no_withdrawals << std::endl;
  std::cout << "# of deposits: " << this->no_deposits << std::endl;
  std::cout << "# of rejections: " << this->no_rejected << std::endl;
}

/* other main functions */

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