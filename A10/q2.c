#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"
typedef volatile int spinlock_t;

const int N = 100000;
int cnt = 0;
spinlock_t aLock = 0;

uthread_t t0, t1, t2;

void countUp() {
  lock(&aLock);
  for (int i=0; i<N; i++)
    cnt += 1;
  unlock(&aLock);
}

void countDown() {
  lock(&aLock);
  for (int i=0; i<N; i++)
    cnt -= 1;
  unlock(&aLock);
}

void* count(void* v) {
  countUp();
  countDown();
  return NULL;
}

int main(int arg, char** arv) {
  uthread_init(4);
  t0 = uthread_create(count, NULL);
  t1 = uthread_create(count, NULL);
  t2 = uthread_create(count, NULL);
  uthread_join (t0, NULL);
  uthread_join (t1, NULL);
  uthread_join (t2, NULL);
  printf("cnt = %d %s\n", cnt, cnt==0? "": "XXX");
}

void lock(spinlock_t * lock) {

  int already_held = 1;
  do {

    while (*lock) {}
      asm volatile ("xchg %0, %1\n" : "=m" (*lock), "=r" (already_held) : "1" (already_held));

  } while (already_held);
}

void unlock(spinlock_t * lock) {

  *lock = 0;
}