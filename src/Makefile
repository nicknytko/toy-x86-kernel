ASMSRC = $(wildcard *.s) $(wildcard */*.s) $(wildcard */*/*.s)
CSRC = $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c)

SOURCES = $(CSRC:.c=.o) $(ASMSRC:.s=.o)
BINARY=../bin/kernel

CFLAGS=-g -I. -m32 -std=c99 -fno-builtin -fno-stack-protector -lgcc -ffreestanding -Wall -Wextra -fno-exceptions
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
