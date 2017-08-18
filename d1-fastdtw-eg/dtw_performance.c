#include "pattern_tracker.h"
#include "DTW.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void fill_random_pattern(int reqnb, char *handle)
{
	int i;
	int offset, len;
	short int type;

	for(i=0; i< reqnb; i++)
	{
		//random offset
		offset = rand(); //something between 0 and 2GB
		len = (rand() %  4194304) + 1; //something between 1 and 4MB
		type = rand() % 2;
		add_request_to_pattern(i, offset, len, type, handle);
	}
}
long int get_nanoelapsed(struct timespec t1)
{
	struct timespec t2;
	clock_gettime(CLOCK_MONOTONIC,&t2);
	return ((t2.tv_nsec - t1.tv_nsec) + ((t2.tv_sec - t1.tv_sec)*1000000000L));
}



int main(int argc, char *argv[])
{
	int i, reqnb, seed;
	struct timespec start;
	char *handle;
	struct access_pattern_t *pattern1, *pattern2;
    long long int result;


	if (argc < 3)
	{
		printf("Usage: ./%s\tpatterns_size\trandom_seed\n", argv[0]);
		exit(-1);
	}
	else
	{
		reqnb = atoi(argv[1]);
        seed = atoi(argv[2]);
	}

	//make a random handle for our patterns
	srand(seed);
	handle = malloc(sizeof(char)*20); //random handle
	for(i=0; i < 20; i++)
		handle[i] = (char) ((rand() % 58) + 65);
	pattern_tracker_init(); //empty pattern

	//generate access patterns filled with random requests
	fill_random_pattern(reqnb, handle);
	pattern1 = get_current_pattern();
	fill_random_pattern(reqnb, handle);
	pattern2 = get_current_pattern();

	//how long to compare them?
	clock_gettime(CLOCK_MONOTONIC, &start);
	result = FastDTW(pattern1, pattern2);
	printf("Result %lld\nwith time %ld\n", result, get_nanoelapsed(start));

	free(handle);
	free_access_pattern_t(&pattern1);
	free_access_pattern_t(&pattern2);
}
