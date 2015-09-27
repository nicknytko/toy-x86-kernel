ASMSRC = $(wildcard *.s)
CSRC = $(wildcard *.c)

SOURCES = $(CSRC:.c=.o) $(ASMSRC:.s=.o)

CFLAGS=-g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-melf_i386 -Tlink.ld
ASFLAGS=-felf -F dwarf -g

all: $(SOURCES) link

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
