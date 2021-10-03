//account.h
#pragma once
#include <iostream>
using std::string;

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
  int get_no_deposit(void);

  int get_no_withdrawals(void);

  int get_no_rejected(void);

  int get_balance(void);

  /* setter */
  void set_no_deposits(int value);

  void set_no_withdrawals(int value);
  void set_no_rejected(int value);
  void set_balance(int value);
  void setType(string value);

  /* methods */
  int generate_amount(int min, int max);

  string strToUpper(string input);

  void toString();
};
