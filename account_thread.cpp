#include <iostream>
#include "checking.h"
#include "account.h"
#include "savings.h"
#include <semaphore.h>
#include <pthread.h>
#include "config.h"

extern int buffer[5];
extern sem_t buffer_access;
// global stats for saving account
extern SavingsAccount savings_account_stats;
extern CheckingAccount checking_account_stats;

void *account_thread(void *params_ptr)
{
  thread_params *params = (thread_params *)params_ptr;

  switch (params->operation_indicator)
  {
  case 1: /* deposit in checking account */
    checking_account_stats.deposit();
    break;
  case 2: /* withdraw from checking account */
    checking_account_stats.withdraw();
    break;
  case 3: /* deposit in savings account */
    savings_account_stats.deposit();
    break;
  case 4: /* withdraw from savings account */
    savings_account_stats.withdraw();
    break;
  case 5: /* transfer from checking to savings account */
    transfer_to<CheckingAccount, SavingsAccount>(checking_account_stats, savings_account_stats);
    break;
  case 6: /* transfer from savings to checking account */
    transfer_to<SavingsAccount, CheckingAccount>(savings_account_stats, checking_account_stats);
    break;
  }
}