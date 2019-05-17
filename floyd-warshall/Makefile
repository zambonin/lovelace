test: $(addsuffix .test, $(basename $(wildcard tests/*.in)))
%.test: %.in %.out
	./fw $< | cmp -s $(word 2, $?) -
	python fw.py $< | cmp -s $(word 2, $?) -
