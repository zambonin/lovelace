test:
	cmp -s <(./fibonacci 10) <(echo "fibonacci(10) = 55")
	cmp -s <(./iterative_scan 10 +) <(echo "3 4 7 9 13 17 20 25 29 33 ")
	./merge_sort 10
	cmp -s <(./rand_comparing 10) <(echo "a[i] < b[i] 6 times")
