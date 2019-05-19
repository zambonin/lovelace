.NOTPARALLEL:
test: $(addsuffix .test, $(basename $(wildcard tests/*.in)))
%.test: %.in %.out
	./gou $< | cmp -s $(word 2, $?) -
