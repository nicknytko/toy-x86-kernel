.PHONY: all kernel util docs _iso iso geninitrd

all: kernel util geninitrd

docs:
	cd docs && doxygen doxygen.conf

kernel:
	$(MAKE) -C src

util:
	$(MAKE) -C util/initrd

_iso:
	cd bin && ./makeiso

iso: kernel _iso

geninitrd:
	cd initrd && ./initrd-make
