test: t1 t2 t3 t4

t1:
	cmp -s <(./fibonacci 10) <(echo "fibonacci(10) = 55")

t2:
	cmp -s <(./iterative_scan 10 +) <(echo "3 4 7 9 13 17 20 25 29 33 ")

t3:
	./merge_sort 10

t4:
	cmp -s <(./rand_comparing 10) <(echo "a[i] < b[i] 6 times")
