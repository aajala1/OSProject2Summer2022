//checking.h
#pragma once
#include <iostream>
#include <string.h>

using namespace std;

class CheckingAccount
{
public:
  CheckingAccount();

  /* deposit */
  string deposit();           // random withdrawal
  string deposit(int amount); // used during transfer

  /* withdrawal */
  string withdraw();           // random withdrawal
  string withdraw(int amount); // used during transfer

  /*getters */
  int get_no_deposit(void);
  int get_no_withdrawals(void);
  int get_no_rejected(void);
  int get_balance(void);

  /* setter */
  void set_no_deposits(int value);
  void set_no_withdrawals(int value);
  void set_no_rejected(int value);
  void set_balance(int value);
  void set_type(string value);

  /* helper functions */
  int generate_amount(int min, int max);

  string strToUpper(string input);

  void toString();

private:
  int no_deposits = 0;
  int no_withdrawals = 0;
  int no_rejected = 0;
  int balance = 0;
  string type;
};
