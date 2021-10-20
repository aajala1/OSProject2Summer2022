// #define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <cstdlib>
#include <unistd.h>
#include "config.h"

using namespace std;

void *account_thread(void *params_ptr);

class IAccount
{
public:
  IAccount(string t)
  {
    set_type(t);
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

  string get_type(void)
  {
    return this->type;
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
  void set_type(string value)
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
    std::cout << "Account type: " << type << std::endl;
    std::cout << "Balance: " << balance << std::endl;
    std::cout << "# of withdrawals: " << no_withdrawals << std::endl;
    std::cout << "# of deposits: " << no_deposits << std::endl;
    std::cout << "# of rejections: " << no_rejected << std::endl;
  }

protected:
  int no_deposits = 0;
  int no_withdrawals = 0;
  int no_rejected = 0;
  int balance = 0;
  string type;
};

class CheckingAccount : public IAccount
{
public:
  CheckingAccount() : IAccount("checking")
  {
  }

  response deposit()
  {
    int amount = this->generate_amount(50, 100);
    cout << "\n\nAmount deposited for checking(50 - 100): " << amount << endl;
    cout << "prev balance: " << to_string(this->balance) << endl;
    this->balance += amount;
    cout << "new balance: " << to_string(this->balance) << endl;
    this->no_deposits++;
    string message = "DEPOSIT " + this->strToUpper(this->type) + " " + to_string(amount);
    cout << message << endl;

    response response = {true, message, amount, CREDIT};
    return response;
  }

  response deposit(int amount)
  {
    cout << "\nChecking deposit during transfer: " << amount << endl;
    cout << "---------------------------------------" << endl;
    cout << "prev balance: " << to_string(this->balance) << endl;
    this->balance += amount;
    cout << "new balance: " << to_string(this->balance) << endl;
    this->no_deposits++;
    string message = "DEPOSIT " + this->strToUpper(this->type) + " " + to_string(amount);
    cout << message << endl;

    response response = {true, message, amount, CREDIT};
    return response;
  }

  response withdraw()
  {
    int amount = generate_amount(50, 100);
    string message = "WITHDRAWAL " + this->strToUpper(this->type) + " " + to_string(amount);

    if (amount > this->balance)
    {
      message += " (REJECTED)";
      this->no_rejected++;
      cout << message << endl;

      response response = {false, message, amount, CANCELED};
      return response;
    }

    cout << "\nChecking withdrawing: " << amount << endl;
    cout << "---------------------------------------" << endl;
    cout << "prev balance " << this->balance << endl;
    balance -= amount;
    cout << "new balance " << this->balance << endl;
    this->no_withdrawals++;
    cout << message << endl;

    response response = {true, message, amount, DEBIT};
    return response;
  }

  response withdraw(int amount)
  {
    string message = "WITHDRAWAL " + this->strToUpper(this->type) + " " + to_string(amount);
    if (amount > this->balance)
    {
      message += " (REJECTED)";
      this->no_rejected++;
      cout << message << endl;

      response response = {false, message, amount, CANCELED};
      return response;
    }
    cout << "\nChecking withdrawing during transfer: " << amount << endl;
    cout << "---------------------------------------" << endl;
    cout << "prev balance " << this->balance << endl;
    balance -= amount;
    cout << "new balance " << this->balance << endl;
    this->no_withdrawals++;
    cout << message << endl;

    response response = {true, message, amount, DEBIT};
    return response;
  }
};

class SavingsAccount : public IAccount
{
public:
  SavingsAccount() : IAccount("savings")
  {
  }

  response deposit()
  {
    int amount = this->generate_amount(100, 150);
    cout << "\n\nAmount deposited for savings(100 - 150): " << amount << endl;
    cout << "prev balance: " << to_string(this->balance) << endl;
    this->balance += amount;
    cout << "new balance: " << to_string(this->balance) << endl;
    this->no_deposits++;
    string message = "DEPOSIT " + this->strToUpper(this->type) + " " + to_string(amount);

    response response = {true, message, amount, CREDIT};
    return response;
  }

  response deposit(int amount)
  {
    cout << "\nSavings deposit during transfer: " << amount << endl;
    cout << "---------------------------------------" << endl;
    cout << "Amount deposited for savings(100 - 150): " << amount << endl;
    cout << "prev balance: " << to_string(this->balance) << endl;
    this->balance += amount;
    cout << "new balance: " << to_string(this->balance) << endl;
    this->no_deposits++;
    string message = "DEPOSIT " + this->strToUpper(this->type) + " " + to_string(amount);
    cout << message << endl;

    response response = {true, message, amount, CREDIT};
    return response;
  }

  response withdraw()
  {
    int amount = this->generate_amount(100, 150);
    string message = "WITHDRAWAL " + this->strToUpper(this->type) + " " + to_string(amount);

    if (amount > this->balance)
    {
      message += " (REJECTED)";
      this->no_rejected++;
      cout << message << endl;
      response response = {false, message, amount, CANCELED};
      return response;
    }

    cout << "Savings withdrawal " << amount << endl;
    cout << "---------------------------------------" << endl;
    cout << "prev balance " << this->balance << endl;
    balance -= amount;
    cout << "new balance " << this->balance << endl;
    this->no_withdrawals++;
    cout << message << endl;

    response response = {true, message, amount, DEBIT};
    return response;
  }

  response withdraw(int amount)
  {
    string message = "WITHDRAWAL " + this->strToUpper(this->type) + " " + to_string(amount);

    if (amount > this->balance)
    {
      message += " (REJECTED)";
      this->no_rejected++;
      cout << message << endl;

      response response = {false, message, amount, CANCELED};
      return response;
    }
    cout << "\nsavings withdrawing during transfer: " << amount << endl;
    cout << "---------------------------------------" << endl;
    cout << "prev balance " << this->balance << endl;
    balance -= amount;
    cout << "new balance " << this->balance << endl;
    this->no_withdrawals++;
    cout << message << endl;

    response response = {true, message, amount, DEBIT};
    return response;
  }
};

extern void *account_thread(void *);

/* global application variables */
int buffer[BUF_SIZE];
sem_t buffer_access;

stats savings_account_stats;
stats checking_account_stats;

SavingsAccount savings_account;
CheckingAccount checking_account;

stats th_checking[THREAD_COUNT];
stats th_savings[THREAD_COUNT];

const ofstream thread_log_files[THREAD_COUNT];

static int thread_tracker = 0;

int main(int argc, char *argv[])
{
  // init_log_files(&thread_log_files, THREAD_COUNT);
  // mutex to access the buffer
  pthread_mutex_t mutex;

  // counting semaphores for buffer resources
  sem_t full;  // # of items in the buffer
  sem_t empty; // # of empty slots in the buffer
  void *status;

  cout << "arguments 01: " << argv[0] << " " << argv[1] << endl;

  if (argc != 2)
  {
    printf("Usage: %s max_loop_count\n", argv[0]);
    exit(1);
  }

  int loop_count = atoi(argv[1]);
  if (loop_count == 0)
  {
    printf("Usage: %s max_loop_count\n", argv[0]);
    exit(1);
  }

  srand(time(0)); /* help seed random function */

  pthread_mutex_init(&mutex, NULL);
  sem_init(&empty, 0, BUF_SIZE);
  sem_init(&full, 0, 0);

  pthread_t t_account_thread[THREAD_COUNT];

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  
  int i;
  for (i = 1; i <= THREAD_COUNT; i++)
  {
    thread_params *params = new thread_params;

    params->mutex_ptr = &mutex;
    params->loop_count = loop_count;
    params->thread_count = i;
    std::cout << "Current thread count: " << i << endl;
    int thread_id = pthread_create(&t_account_thread[i - 1], &attr, account_thread, (void *)params);
    if (thread_id)
    {
      std::cout << "unable to create thread " << thread_id << endl;
      exit(-1);
    }
    else
    {
      std::cout << "Thread " << i << " created" << endl;
    }
  }

  // free attribute and wait for the other threads
  // pthread_attr_destroy(&attr);
  for (i = 0; i < THREAD_COUNT; i++)
  {
    int thread_id = pthread_join(t_account_thread[i], &status);
    if (thread_id)
    {
      std::cout << "unable to create thread " << thread_id << endl;
      exit(-1);
    }
    else
    {
      std::cout << "Thread " << i << " joining......." << endl;
    }
  }

  cout << "thread tracker: " << thread_tracker << endl;
  pthread_exit(NULL);
}

// void *account_thread(void *params_ptr)
// {
//   stringstream output;
//   thread_params *params = (thread_params *)params_ptr;
//   output << "message from thread " << params->thread_count << endl;
//   cout << "thread content goes here" << endl;
//   pthread_mutex_lock(params->mutex_ptr);
//   log_message(output.str(), params->thread_count);
//   pthread_mutex_unlock(params->mutex_ptr);
//   pthread_exit(NULL);
// }

void *account_thread(void *params_ptr)
{
  thread_params *params = (thread_params *)params_ptr;
  pthread_mutex_lock(params->mutex_ptr);
  response response;
  for (int count = 0; count < params->loop_count; count++)
  {
    thread_tracker++;
    cout << "current active thread: " << params->thread_count << endl;
    params->operation_indicator = generate_random_operaton(1, 6);
    switch (params->operation_indicator)
    {
    case 1: /* deposit in checking account */
      response = checking_account.deposit();
      update_stats_info(checking_account_stats, response); /* updage global stats */
      update_stats_info(th_checking[params->thread_count], response);
      log_message(response.message, params->thread_count);
      break;
    case 2: /* withdraw from checking account */
      response = checking_account.withdraw();
      update_stats_info(checking_account_stats, response); /* updage global stats */
      update_stats_info(th_checking[params->thread_count], response);
      log_message(response.message, params->thread_count);
      break;
    case 3: /* deposit in savings account */
      response = savings_account.deposit();
      update_stats_info(checking_account_stats, response); /* updage global stats */
      update_stats_info(th_checking[params->thread_count], response);
      log_message(response.message, params->thread_count);
      break;
    case 4: /* withdraw from savings account */
      response = savings_account.withdraw();
      update_stats_info(savings_account_stats, response); /* updage global stats */
      update_stats_info(th_checking[params->thread_count], response);
      log_message(response.message, params->thread_count);
      break;
    case 5: /* transfer from checking to savings account */
      response = transfer_to<CheckingAccount, SavingsAccount>(checking_account, savings_account);
      if (response.type == CANCELED)
      {
        update_stats_info(checking_account_stats, response); /* updage global stats */
        update_stats_info(th_checking[params->thread_count], response);
        log_message(response.message, params->thread_count);
      }
      else
      {
        response.type = DEBIT;
        update_stats_info(checking_account_stats, response); /* updage global stats */
        update_stats_info(th_checking[params->thread_count], response);
        log_message(response.message, params->thread_count);

        response.type = CREDIT;
        update_stats_info(savings_account_stats, response); /* updage global stats */
        update_stats_info(th_checking[params->thread_count], response);
        log_message(response.message, params->thread_count);
      }

      break;
    case 6: /* transfer from savings to checking account */
      response = transfer_to<SavingsAccount, CheckingAccount>(savings_account, checking_account);
      if (response.type == CANCELED)
      {
        update_stats_info(savings_account_stats, response); /* updage global stats */
        update_stats_info(th_checking[params->thread_count], response);
        log_message(response.message, params->thread_count);
      }
      else
      {
        response.type = DEBIT;
        update_stats_info(savings_account_stats, response); /* update global stats */
        update_stats_info(th_checking[params->thread_count], response);
        log_message(response.message, params->thread_count);

        response.type = CREDIT;
        update_stats_info(checking_account_stats, response); /* update global stats */
        update_stats_info(th_checking[params->thread_count], response);
        log_message(response.message, params->thread_count);
      }
      break;
    }
  }

  update_thread_stats(th_checking[params->thread_count], checking_account);
  update_thread_stats(th_savings[params->thread_count], savings_account);

  std::string msg_checking = print_stats(th_checking[params->thread_count], checking_account.get_type());
  std::string msg_savings = print_stats(th_savings[params->thread_count], savings_account.get_type());

  log_message(msg_checking, params->thread_count);
  log_message(msg_savings, params->thread_count);

  pthread_mutex_unlock(params->mutex_ptr);
  pthread_exit(NULL);
}