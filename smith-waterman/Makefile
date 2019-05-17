test: $(addsuffix .test, $(basename $(wildcard tests/*.in*)))
%.test: %.in1 %.in2 %.out
	./sw $< $(word 2, $?) | cmp -s $(word 3, $?) -
	./sw+ $< $(word 2, $?) | cmp -s $(word 3, $?) -
