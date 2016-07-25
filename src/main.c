#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coww.h"
#include "sb.h"
#include "results.h"

#define VERSION "0.1"

void parse_params(int argc, char * argv[]);

int max_itr = 10000;
int quiet = 0;
int use_fences = 0;

int
main(int argc, char * argv[])
{
	int count = 0;
	parse_params(argc, argv);

	for(int i = 0; i < max_itr; i++) {
		result_t res = sb_run(i);
		count += res == RESULT_WEAK_BEHAVIOUR ? 1 : 0;
		if(!quiet && res == RESULT_WEAK_BEHAVIOUR) {
			printf("[SB]   Attempt %d showed weak behaviour\r\n", i);
		}
		if(!quiet && i % (max_itr / 100)) {
			printf("%.2f%%\r", ((float)i / max_itr) * 100);
		}
	}

	printf("[SB]   %d (%0.2f%%) instances of weak behaviour observed.\n", count, ((float)count / max_itr) * 100);

	count = 0;
	for(int i = 0; i < max_itr; i++) {
		result_t res = coww_run(i);
		count += res == RESULT_WEAK_BEHAVIOUR ? 1 : 0;
		if(!quiet && res == RESULT_WEAK_BEHAVIOUR) {
			printf("[SB]   Attempt %d showed weak behaviour\r\n", i);
		}
		if(!quiet && i % (max_itr / 100)) {
			printf("%.2f%%\r", ((float)i / max_itr) * 100);
		}
	}

	printf("[CoWW] %d (%0.2f%%) instances of weak behaviour observed.\n", count, ((float)count / max_itr) * 100);

	return 0;
}

void
parse_params(int argc, char * argv[])
{
	for(int i = 0; i < argc; i++)
	{
		if(strstr(argv[i], "-q")) {
			quiet = 1;
		}
		if(strstr(argv[i], "-v")) {
				printf("Litmus Tests:\r\n");
				printf("  Version: " VERSION "\r\n");
				printf("  Compiled: " __DATE__ " " __TIME__ " with " __COMPILER__ " " __VERSION__ ".\r\n");
				#ifdef __STDC_NO_THREADS__
					printf("  Using pthreads wrapped with \"c11threads.h\".\r\n");
				#else
					printf("  Using \"<threads.h>\"\r\n");
				#endif
				exit(0);
		}
		if(strstr(argv[i], "-I")) {
			i++;
			max_itr = atoi(argv[i]);
		}
		if(strstr(argv[i], "-f")) {
			use_fences = 1;
		}

		if(strstr(argv[i], "-h") || strstr(argv[i], "-?")) {
			printf("Litmus Tests:\r\n");
			printf("  Tests the current architecture for various behaviours.\r\n");
			printf("  Options:\r\n");
			printf("    -q        Quiet mode, do not output completed percent\r\n");
			printf("    -I <n>    Execute <n> test itterations\r\n");
			printf("    -f        Use fences to prevent weak memory behaviours\r\n");
			printf("    -v        Display version and exit\r\n");
			printf("    -h        Display this help and exit\r\n");
			printf("    -?        Display this help and exit\r\n");
		}
	}
}
