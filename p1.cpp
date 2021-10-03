#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

template <class T, class U>
string transfer_to(T &current_account, U &target_account)
{
  int amount = current_account.generate_amount(100, 200);
  string message = "TRANSFER " + current_account.strToUpper(current_account.type) + " TO " + current_account.strToUpper(target_account.type) + " " + to_string(amount);

  // withdraw from our current this->savings_account
  if (current_account.balance < amount)
  { // reject transfer
    current_account.withdraw(amount);
    message += " (REJECTED)";
  }
  else
  {
    current_account.withdraw(amount);
    target_account.deposit(amount);
  }
  return message;
}

class Account
{
public:
  int no_deposits = 0;
  int no_withdrawals = 0;
  int no_rejected = 0;
  int balance = 0;
  string type;

  Account(string t)
  {
    setType(t);
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
  void setType(string value)
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
    cout << "Account type: " << this->type << endl;
    cout << "Balance: " << this->balance << endl;
    cout << "# of withdrawals: " << this->no_withdrawals << endl;
    cout << "# of deposits: " << this->no_deposits << endl;
    cout << "# of rejections: " << this->no_rejected << endl;
  }
};

class SavingAccount : public Account
{
public:
  SavingAccount() : Account("savings")
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

class CheckingAccount : public Account
{
public:
  CheckingAccount() : Account("checking")
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

int buffer[sizeof(Account)];
sem_t buffer_access;
// global stats for saving account
SavingAccount savings_account_stats;
CheckingAccount checking_account_stats;

int main(int argc, char *argv[])
{
  SavingAccount savings_account;
  CheckingAccount checking_account;
  srand(time(0));
  int input;

  do
  {
    cout << "Enter 1 to continue, 0 to quit: ";
    cin >> input;

    int size = 4;

    // deposit into checking
    for (int i = 0; i < size; i++)
      cout << checking_account.deposit() << endl;

    // // // deposit into savings
    // for (int i = 0; i < size; i++)
    //   cout << savings_account.deposit() << endl;

    // for (int i = 0; i < size; i++)
    //   cout << checking_account.deposit() << endl;

    // cout << transfer_to<SavingAccount, CheckingAccount>(savings_account, checking_account) << endl;
    cout << transfer_to<CheckingAccount, SavingAccount>(checking_account, savings_account) << endl;

    checking_account.toString();
    savings_account.toString();

  } while (input == 1);

  return 0;
}
