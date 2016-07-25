#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include "sb.h"

thrd_start_t thread_0(void * arg);
thrd_start_t thread_1(void * arg);

volatile int x = 0;
volatile int y = 0;
atomic_int synchronise;
atomic_int return_value;

result_t
sb_run(int run)
{
	synchronise = 0;
	x = 0;
	return_value = 0;

	thrd_t thread_0_ptr, thread_1_ptr;

	thrd_create(&thread_0_ptr, (thrd_start_t) &thread_0, NULL);
	thrd_create(&thread_1_ptr, (thrd_start_t) &thread_1, (void *) &return_value);

	if(return_value > 1) {
		return RESULT_BEHAVIOUR_INCORRECT;
	}
	return RESULT_BEHAVIOUR_CORRECT;
}

thrd_start_t
thread_0(void * arg)
{
	synchronise = 1;
	x = 1;

	if(y == 0) {
		return_value++;
	}

	thrd_exit(0);
}

thrd_start_t
thread_1(void * arg)
{
	while(synchronise == 0)
		;

	y = 1;

	if(x == 0) {
		return_value++;
	}

	thrd_exit(0);
}
