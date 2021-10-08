#pragma once
#include <iostream>
using std::string;

// structure of our params
struct thread_params
{
  int loop_count;
  int operation_indicator;
};

template <class T, class U>
string transfer_to(T &current_account, U &target_account)
{
  int amount = current_account.generate_amount(100, 200);
  string message = "TRANSFER " + current_account.strToUpper(current_account.type) + " TO " + current_account.strToUpper(target_account.type) + " " + std::to_string(amount);

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
