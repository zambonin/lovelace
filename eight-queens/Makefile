test: t1 t2 t3 t4

t1:
	cmp -s <(./nq 8) <(echo "Solutions = 92")

t2:
	cmp -s <(./nq 4) <(echo "Solutions = 2")

t3:
	cmp -s <(./nq 3) <(echo "Solutions = 0")

t4:
	cmp -s <(./nq 12) <(echo "Solutions = 14200")
