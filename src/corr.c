#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include "corr.h"
#include "results.h"

void thread_0(void * arg);
void thread_1(void * arg);

volatile int x;

volatile int synchronise;

volatile int return_value;

void 
corr_run(int run)
{
	synchronise = 0;
	x = 1;
	return_value = 0;

	thrd_t thread_0_ptr, thread_1_ptr;

	thrd_create(&thread_0_ptr, (void *) &thread_0, NULL);
	thrd_create(&thread_1_ptr, (void *) &thread_1, (void *) &return_value);

    // pthread_join(thread_0_ptr, NULL);
    // pthread_join(thread_1_ptr, NULL);


	while(return_value == 0)
		;
	
	printf("[CoRR]  Attempt %d showed weak behaviour\r\n", *((int*)run));
}

void 
thread_0(void * arg) 
{
	synchronise = 1;
	register int a = x;
	register int b = 2;
	x = 1;

	pthread_exit(0);
}

void 
thread_1(void * arg)
{
	while(synchronise == 0)
		;

	if(x == 1)
		return_value = RESULT_BEHAVIOUR_INCORRECT;
	else 
		return_value = RESULT_BEHAVIOUR_CORRECT;

	pthread_exit(0);
}