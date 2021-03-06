#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#ifndef SW
#include "vhdlCStubs.h"
#endif

#define ORDER 4

void Exit(int sig)
{
	fprintf(stderr, "## Break! ##\n");
	exit(0);
}

int main(int argc, char* argv[])
{
	uint8_t result, expected_result;
	signal(SIGINT,  Exit);
  	signal(SIGTERM, Exit);

	uint8_t idx;
	for(idx = 0; idx < ORDER; idx++)
	{
		uint8_t val = idx;
		expected_result = 3*val;
		write_uint8("in_data",val);
		
	}

	for(idx = 0; idx < ORDER; idx++)
	{
		uint8_t val = idx;
		expected_result = 3*val;
		result = read_uint8("out_data");
		fprintf(stdout,"Result = %x, expected = %x.\n", result,expected_result);
	}


	return(0);
}
