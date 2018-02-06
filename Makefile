DIRS := $(wildcard */.)

all: $(DIRS)

$(DIRS):
	$(MAKE) -C $@

test: all
	$(foreach d,$(wildcard */.),$(MAKE) -C $d test;)

clean:
	$(foreach d,$(DIRS),$(MAKE) -C $d clean;)
