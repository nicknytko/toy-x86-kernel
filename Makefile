.PHONY: all kernel util

all: kernel util

kernel:
	$(MAKE) -C src

util:
	$(MAKE) -C util/initrd
