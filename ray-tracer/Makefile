test: $(addsuffix .test, $(basename $(wildcard tests/*.in)))
%.test: %.in %.ppm
	./rt $< | cmp -s $(word 2, $?) -
