#include <iostream>
#include "checking.h"
#include "account.h"
#include "savings.h"
#include <semaphore.h>
#include <pthread.h>

extern int buffer[5];
extern sem_t buffer_access;
// global stats for saving account
extern SavingsAccount savings_account_stats;
extern CheckingAccount checking_account_stats;


void * checking_thread(void * account_ptr)
{
  CheckingAccount *checking_account = (CheckingAccount *)account_ptr;
}