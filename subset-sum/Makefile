test: t1 t2 t3 t4

t1:
	cmp -s <(./ss 10 53 32 10) <(echo "Number of subsets = 3")

t2:
	cmp -s <(./ss 30 100 146 20) <(echo "Number of subsets = 1343")

t3:
	cmp -s <(./ss 32 1000 2000 1) <(echo "Number of subsets = 870")

t4:
	cmp -s <(./ss 300 138000 58820 1) <(echo "Number of subsets = 1233")
