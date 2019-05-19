test: fisher average

fisher: FISHFILE := $(shell mktemp)
fisher:
	python knn.py tests/fisher_{data,test}set.csv $(FISHFILE) 5
	cmp -s tests/fisher_output.csv $(FISHFILE)

average: AVGFILE := $(shell mktemp)
average:
	python knn.py tests/average_{data,test}set.csv $(AVGFILE) 13
	cmp -s tests/average_output.csv $(AVGFILE)
