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

extern void *account_thread(void *);

/* global application variables */

int buffer[BUF_SIZE];
sem_t buffer_access;
SavingsAccount savings_account_stats;
CheckingAccount checking_account_stats;

int main(int argc, char *argv[])
{
  // mutex to access the buffer
  pthread_mutex_t mutex;
  // counting semaphores for buffer resources
  sem_t full;  // # of items in the buffer
  sem_t empty; // # of empty slots in the buffer

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
  thread_params *params = new thread_params;

  params->loop_count = loop_count;
  params->operation_indicator = savings_account_stats.generate_amount(1, 6);

  pthread_mutex_init(&mutex, NULL);
  sem_init(&empty, 0, BUF_SIZE);
  sem_init(&full, 0, 0);

  pthread_t t_checking;
  pthread_t t_savings;

  pthread_attr_t attr;
  pthread_attr_init(&attr);

  pthread_create(&t_checking, &attr, account_thread, (void *)params);
  pthread_create(&t_savings, &attr, account_thread, (void *)params);

  pthread_join(t_checking, NULL);
  pthread_join(t_savings, NULL);

  return 0;
}
