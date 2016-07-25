#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include "sb.h"

extern int use_fences;
thrd_start_t thread_0(void * arg);
thrd_start_t thread_1(void * arg);

volatile int x = 0;
volatile int y = 0;
atomic_int synchronise;

result_t
sb_run(int run)
{
	synchronise = 0;
	x = 0;
	y = 0;

	thrd_t thread_0_ptr, thread_1_ptr;

	thrd_create(&thread_0_ptr, (thrd_start_t) &thread_0, NULL);
	thrd_create(&thread_1_ptr, (thrd_start_t) &thread_1, NULL);

	int x, y;
	thrd_join(thread_0_ptr, &x);
	thrd_join(thread_1_ptr, &y);

	if(x == 0 && y == 0) {
		return RESULT_WEAK_BEHAVIOUR;
	}
	return RESULT_NORMAL_BEHAVIOUR;
}

thrd_start_t
thread_0(void * arg)
{
	synchronise = 1;
	x = 1;
	if(use_fences)
		asm("mfence");

	thrd_exit(y);
}

thrd_start_t
thread_1(void * arg)
{
	while(synchronise == 0)
		;

	y = 1;
	if(use_fences)
		asm("mfence");

	thrd_exit(x);
}
