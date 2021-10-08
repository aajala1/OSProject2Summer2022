#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include "checking.h"
#include "savings.h"
#include "config.h"

using namespace std;

// extern void *account_thread(void *);

/* global application variables */
<<<<<<< HEAD

int buffer[BUF_SIZE];
sem_t buffer_access;
SavingsAccount savings_account_stats;
CheckingAccount checking_account_stats;
=======
// int buffer[5];
// sem_t buffer_access;
>>>>>>> 4dd6e60574990377fe18cdd1dcbd78a986d7731d

int main(int argc, char *argv[])
{

  SavingsAccount savings_account_stats;
  CheckingAccount checking_account_stats;

  // checking_account_stats.deposit();
  savings_account_stats.toString();
  checking_account_stats.toString();

  return 0;
}
