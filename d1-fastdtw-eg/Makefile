all: fastdtw

fastdtw: dtw_performance.c pattern_tracker.c DTW.c mylist.c
	$(CC) -o fastdtw dtw_performance.c pattern_tracker.c DTW.c mylist.c -lrt -lpthread -lm -Wall
clean:
	rm fastdtw

