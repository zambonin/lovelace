test: $(addsuffix .test, $(basename $(wildcard tests/*.in)))
%.test: %.in %.out
	./shs $< | cmp -s $(word 2, $?) -
