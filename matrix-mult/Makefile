auto: $(basename $(wildcard *.c))

.NOTPARALLEL:
test: $(addsuffix .test, $(basename $(wildcard tests/*.in*)))
%.test: %.in1 %.in2 %.out
	./smm $< $(word 2, $?) | cmp -s $(word 3, $?) -
