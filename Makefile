DIRS := $(wildcard */.)

all: $(DIRS)

$(DIRS):
	$(MAKE) -C $@

clean:
	$(foreach d,$(DIRS),$(MAKE) -C $d clean;)
