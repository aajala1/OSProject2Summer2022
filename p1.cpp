#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include "config.h"

using namespace std;

class IAccount
{
public:
  int no_deposits = 0;
  int no_withdrawals = 0;
  int no_rejected = 0;
  int balance = 0;
  string type;

  IAccount(string t)
  {
    set_type(t);
  }

  /* getters */
  int get_no_deposit(void)
  {
    return this->no_deposits;
  }

  int get_no_withdrawals(void)
  {
    return this->no_withdrawals;
  }

  int get_no_rejected(void)
  {
    return this->no_rejected;
  }

  int get_balance(void)
  {
    return this->balance;
  }

  /* setter */
  void set_no_deposits(int value)
  {
    this->no_deposits = value;
  }

  void set_no_withdrawals(int value)
  {
    this->no_withdrawals = value;
  }
  void set_no_rejected(int value)
  {
    this->no_rejected = value;
  }
  void set_balance(int value)
  {
    this->balance = value;
  }
  void set_type(string value)
  {
    this->type = value;
  }

  /* methods */
  int generate_amount(int min, int max)
  {
    int amount = min + (std::rand() % (max - min + 1));
    return amount;
  }

  string strToUpper(string input)
  {
    for (int i = 0; i < input.size(); i++)
    {
      input.at(i) = toupper(input.at(i));
    }
    return input;
  }

  void toString()
  {
    std::cout << "Account type: " << type << std::endl;
    std::cout << "Balance: " << balance << std::endl;
    std::cout << "# of withdrawals: " << no_withdrawals << std::endl;
    std::cout << "# of deposits: " << no_deposits << std::endl;
    std::cout << "# of rejections: " << no_rejected << std::endl;
  }
};

class CheckingAccount : public IAccount
{
public:
  CheckingAccount() : IAccount("checking")
  {
  }

  string deposit()
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

  string deposit(int amount)
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

  string withdraw()
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

  string withdraw(int amount)
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
};

class SavingsAccount : public IAccount
{
public:
  SavingsAccount() : IAccount("savings")
  {
  }

  string deposit()
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

  string deposit(int amount)
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

  string withdraw()
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

  string withdraw(int amount)
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
};

extern void *account_thread(void *);

/* global application variables */
int buffer[5];
sem_t buffer_access;
SavingsAccount savings_account_stats;
CheckingAccount checking_account_stats;


int main(int argc, char *argv[])
{

  

  checking_account_stats.deposit();
  savings_account_stats.toString();
  checking_account_stats.toString();

  return 0;
}
