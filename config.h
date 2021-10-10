#pragma once
#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;

const int BUF_SIZE = 1024;
const int THREAD_COUNT = 2;
enum TRANS_TYPE
{
  CANCELED,
  CREDIT,
  DEBIT,
  TRANSFER
};

struct stats
{
  int no_deposits = 0;
  int no_withdrawals = 0;
  int no_rejected = 0;
  int balance = 0;
};

int generate_random_operaton(int min, int max)
{
  int random_operation = min + (std::rand() % (max - min + 1));
  return random_operation;
}

// structure of our params
struct thread_params
{
  pthread_mutex_t *mutex_ptr;
  int loop_count;
  int operation_indicator;
};

struct response
{
  bool success;
  string message;
  int data; /* amount */
  int type = CREDIT | DEBIT | CANCELED | TRANSFER;
};

template <class T, class U>
response transfer_to(T &current_account, U &target_account)
{
  int amount = current_account.generate_amount(100, 200);
  string message = "TRANSFER " + current_account.strToUpper(current_account.get_type()) + " TO " + current_account.strToUpper(target_account.get_type()) + " " + std::to_string(amount);

  // withdraw from our current this->savings_account
  if (current_account.get_balance() < amount)
  {                                   // reject transfer
    current_account.withdraw(amount); /* update rejection in current account */
    message += " (REJECTED)";
    response response = {true, message, amount, CANCELED};
    return response;
  }
  else
  {
    current_account.withdraw(amount);
    target_account.deposit(amount);
  }
  response response = {true, message, amount, TRANSFER};
  return response;
}

int get_new_balance(int current_balance, response res)
{
  switch (res.type)
  {
  case CREDIT:
    return current_balance + res.data;
    break;
  case DEBIT:
    return current_balance - res.data;
    break;
  default:
    return current_balance;
  }
}

void update_stats_info(stats &stats, response res)
{
  stats.balance = get_new_balance(stats.balance, res);
  stats.no_deposits += res.type == CREDIT ? 1 : 0;
  stats.no_rejected += res.type == CREDIT ? 1 : 0;
  stats.no_withdrawals += res.type == DEBIT ? 1 : 0;
}

template <class U>
void update_thread_stats(stats &stats, U &account)
{
  stats.balance = account.get_balance();
  stats.no_deposits = account.get_no_deposit();
  stats.no_rejected = account.get_no_rejected();
  stats.no_withdrawals = account.get_no_withdrawals();
}

void print_stats(stats &stats, string type)
{
  std::cout << "\n============== Thread summary for " << type << " account =================" << endl;
  std::cout << "Balance: " << stats.balance << std::endl;
  std::cout << "# of withdrawals: " << stats.no_withdrawals << std::endl;
  std::cout << "# of deposits: " << stats.no_deposits << std::endl;
  std::cout << "# of rejections: " << stats.no_rejected << std::endl;
  std::cout << "------------------------------------------------" << endl;
}
