#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sb.h"
#include "results.h"

#define VERSION "0.0"

void parse_params(int argc, char * argv[]);

int max_itr = 100000;
int quiet = 0;

int
main(int argc, char * argv[])
{
	parse_params(argc, argv);

	for(int i = 0; i < max_itr; i++) {
		if(sb_run(i) == RESULT_BEHAVIOUR_INCORRECT) {
			printf("[SB]   Attempt %d showed weak behaviour\r\n", i);
		}
		if(quiet == 0 && i % (max_itr / 1000)) {
			printf("%.2f%%\r", ((float)i / max_itr) * 100);
		}
	}

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
				printf("Version: " VERSION "\r\n");
				exit(0);
		}
		if(strstr(argv[i], "-I")) {
			i++;
			max_itr = atoi(argv[i]);
		}
		if(strstr(argv[i], "-h") || strstr(argv[i], "-?")) {
			printf("Litmus Tests:\r\n");
			printf("  Tests the current architecture for various behaviours.\r\n");
			printf("  Options:\r\n");
			printf("    -q        Quiet mode, do not output completed percent\r\n");
			printf("    -v        Display version and exit\r\n");
			printf("    -h        Display this help and exit\r\n");
			printf("    -?        Display this help and exit\r\n");
		}
	}
}