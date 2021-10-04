//checking.h
#pragma once
#include <iostream>
#include "account.h"
using std::string;

class CheckingAccount: public IAccount
{
public:
  // CheckingAccount(): IAccount("checking")
  // {
  // }
  CheckingAccount();
  CheckingAccount(string);
  

  /* deposit */
  string deposit();// random withdrawal
  string deposit(int amount);// used during transfer

  /* withdrawal */
  string withdraw(); // random withdrawal
  string withdraw(int amount); // used during transfer
};
