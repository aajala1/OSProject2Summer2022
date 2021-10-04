//account.h
#pragma once
#include <iostream>
#include "account.h"
using std::string;

class SavingsAccount: public IAccount
{
public:
  // SavingsAccount(): IAccount("savings")
  // {
  // }
    SavingsAccount();
    SavingsAccount(string);

  /* deposit */
  string deposit();// random withdrawal
  string deposit(int amount);// used during transfer

  /* withdrawal */
  string withdraw(); // random withdrawal
  string withdraw(int amount); // used during transfer
};
