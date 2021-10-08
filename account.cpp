#include <iostream>
#include "account.h"
#include <string.h>

using namespace std;

IAccount::IAccount(string t)
{
  set_type(t);
}

/* getters */
int IAccount::get_no_deposit(void)
{
  return this->no_deposits;
}

int IAccount::get_no_withdrawals(void)
{
  return this->no_withdrawals;
}

int IAccount::get_no_rejected(void)
{
  return this->no_rejected;
}

int IAccount::get_balance(void)
{
  return this->balance;
}

/* setter */
void IAccount::set_no_deposits(int value)
{
  this->no_deposits = value;
}

void IAccount::set_no_withdrawals(int value)
{
  this->no_withdrawals = value;
}
void IAccount::set_no_rejected(int value)
{
  this->no_rejected = value;
}
void IAccount::set_balance(int value)
{
  this->balance = value;
}
void IAccount::set_type(string value)
{
  this->type = value;
}

/* methods */
int IAccount::generate_amount(int min, int max)
{
  int amount = min + (std::rand() % (max - min + 1));
  return amount;
}

string IAccount::strToUpper(string input)
{
  for (int i = 0; i < input.size(); i++)
  {
    input.at(i) = toupper(input.at(i));
  }
  return input;
}

void IAccount::toString()
{
  std::cout << "Account type: " << type << std::endl;
  std::cout << "Balance: " << balance << std::endl;
  std::cout << "# of withdrawals: " << no_withdrawals << std::endl;
  std::cout << "# of deposits: " << no_deposits << std::endl;
  std::cout << "# of rejections: " << no_rejected << std::endl;
}
