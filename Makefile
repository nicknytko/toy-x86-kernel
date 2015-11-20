.PHONY: all kernel util docs

all: kernel util geninitrd

docs:
	cd docs && doxygen doxygen.conf

kernel:
	$(MAKE) -C src

util:
	$(MAKE) -C util/initrd

geninitrd:
	cd initrd && ./initrd-make
