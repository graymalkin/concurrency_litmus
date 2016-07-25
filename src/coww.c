#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __STDC_NO_THREADS__
	#include "c11threads.h"
#else
	#include <threads.h>
#endif

#include "sb.h"

extern int use_fences;
thrd_start_t coww_thread_0(void * arg);
thrd_start_t coww_thread_1(void * arg);

volatile int coww_x = 0;
volatile int coww_y = 0;
atomic_int coww_synchronise;

result_t
coww_run(int run)
{
	coww_synchronise = 0;
	coww_x = 0;
	coww_y = 0;

	thrd_t thread_0_ptr, thread_1_ptr;

	thrd_create(&thread_0_ptr, (thrd_start_t) &coww_thread_0, NULL);
	thrd_create(&thread_1_ptr, (thrd_start_t) &coww_thread_1, NULL);

	int k, l;
	thrd_join(thread_0_ptr, &k);
	thrd_join(thread_1_ptr, &l);

	if(k == 0 && coww_x == 1) {
		return RESULT_WEAK_BEHAVIOUR;
	}
	return RESULT_NORMAL_BEHAVIOUR;
}

thrd_start_t
coww_thread_0(void * arg)
{
	coww_synchronise = 1;
	coww_x = 1;
	register int a = coww_x;
	register int b = coww_y;

	// 0 if a == 0 && b == 0
	thrd_exit(a + b);
	__builtin_unreachable();
}

thrd_start_t
coww_thread_1(void * arg)
{
	while(coww_synchronise == 0)
		;

	coww_x = 2;
	coww_y = 2;
	if(use_fences)
		asm("mfence");

	thrd_exit(coww_x);
	__builtin_unreachable();
}
