/*
 * atomic.c
 *
 *  Created on: 2010-11-28
 *      Author: Joel J
 */


#include "rtx.h"

#define ON  1
#define OFF 0

int change;
//Details:
//=====================================================================
//We decided not to have the atomic function keep track of if
//multiple atomic(ON)'s are called on the current process.
//It is assumed that atomic(ON) and atomic(OFF) will always be provided
//in conjugates surrounding a function.

void atomic(change){
static sigset_t x;
static sigset_t y;

if (change == ON){
//Need to create an atomic count variable to keep track of if a process has atomic(on)twice.
//if (atomic_count == 0){
sigemptyset (&x);
sigaddset(&x, SIGINT);
sigaddset(&x, SIGALRM);
sigaddset(&x, SIGUSR1);
sigaddset(&x, SIGUSR2);
sigprocmask(SIG_BLOCK, &x, NULL/*&y*/);
//Use sigset_t y when debugging instead of null to keep track of
//previously blocked signals if needed
//}
//else{
// atomic_count = atomic_count+1;
//}
}
else{
//if(atomic_count == 1){
sigprocmask(SIG_UNBLOCK, &x, NULL/*&y*/);
//}
//else{
// atomic_count = atomic_count-1;
//}
}
}
