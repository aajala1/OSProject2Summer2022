#include <iostream>

using std::string;
extern int buffer[sizeof(Account)];
extern sem_t buffer_access;
// global stats for saving account
extern Account savings_account_stats("savings");
extern Account checking_account_stats("checking");

void *savings_account(void *s_account)
{
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
}