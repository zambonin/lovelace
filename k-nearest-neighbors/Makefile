TMPFILE := $(shell mktemp)

test: fisher average

fisher:
	python knn.py tests/fisher_{data,test}set.csv $(TMPFILE) 5
	cmp -s tests/fisher_output.csv $(TMPFILE)

average:
	python knn.py tests/average_{data,test}set.csv $(TMPFILE) 13
	cmp -s tests/average_output.csv $(TMPFILE)
