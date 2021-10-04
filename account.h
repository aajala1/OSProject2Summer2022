//account.h
#pragma once
#include <iostream>
using std::string;
using namespace std;

//abstract class or interface
class IAccount
{
public:
  int no_deposits;
  int no_withdrawals;
  int no_rejected;
  int balance;
  string type;

  IAccount();
  IAccount(string);


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
  void set_type(string value);

  /* methods */
  int generate_amount(int min, int max);

  string strToUpper(string input);

  void toString();

  /* virtural functions */
  /* deposit */
  virtual string deposit() = 0;           // random withdrawal
  virtual string deposit(int amount) = 0; // used during transfer

  /* withdrawal */
  virtual string withdraw() = 0;           // random withdrawal
  virtual string withdraw(int amount) = 0; // used during transfer
};
