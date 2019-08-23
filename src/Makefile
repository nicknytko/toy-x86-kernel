ASMSRC = $(wildcard *.s) $(wildcard */*.s) $(wildcard */*/*.s)
CSRC = $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c)

SOURCES = $(CSRC:.c=.o) $(ASMSRC:.s=.o)
BINARY=../bin/kernel
OBJS = $(CSRC:.c=.o)

CFLAGS=-g -I. -m32 -std=c99 -fno-builtin -fno-stack-protector -lgcc -ffreestanding -Wall -Wextra -fno-exceptions
LDFLAGS=-melf_i386 -Tlink.ld
ASFLAGS=-felf -F dwarf -g

all: $(SOURCES) link

clean:
	rm $(BINARY)
	find . -name "*.o" | xargs rm
	find . -name "*.d" | xargs rm

link:
	ld $(LDFLAGS) -o $(BINARY) $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

# create a list of auto dependencies
AUTODEPS:= $(patsubst %.o,%.d, $(OBJS))

 # include by auto dependencies
-include $(AUTODEPS)

%.o: %.c %.d
	$(CC) $(CFLAGS) -c -o $@ $<

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT"$@ $(@:.d=.o)" -MP -MF $@ $<

