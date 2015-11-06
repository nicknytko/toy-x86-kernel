.PHONY: all kernel util

all: kernel util geninitrd

kernel:
	$(MAKE) -C src

util:
	$(MAKE) -C util/initrd

geninitrd:
	cd initrd && ./initrd-make
