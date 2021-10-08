//checking.h
#pragma once
#include <iostream>
#include <string.h>
#include "account.h"

using namespace std;

class CheckingAccount : public IAccount
{
public:
  CheckingAccount();

  /* deposit */
  string deposit();           // random withdrawal
  string deposit(int amount); // used during transfer

  /* withdrawal */
  string withdraw();           // random withdrawal
  string withdraw(int amount); // used during transfer
};
