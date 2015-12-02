ASMSRC = $(wildcard *.s) $(wildcard */*.s)
CSRC = $(wildcard *.c) $(wildcard */*.c)

SOURCES = $(CSRC:.c=.o) $(ASMSRC:.s=.o)
BINARY=../bin/kernel

CFLAGS=-g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -ffreestanding -lgcc
LDFLAGS=-melf_i386 -Tlink.ld
ASFLAGS=-felf -F dwarf -g

all: $(SOURCES) link

clean:
	rm $(BINARY)
	find . -name "*.o" | xargs rm

link:
	ld $(LDFLAGS) -o $(BINARY) $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
