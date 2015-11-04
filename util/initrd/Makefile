CSRC = $(wildcard *.cpp)
SOURCES = $(CSRC:.cpp=.o)
BINARY=initrd
CFLAGS=-g
CC=g++

all: $(SOURCES) link

clean:
	-rm *.o

.cpp:
	$(CC) -c -o $@ $< $(CFLAGS)

link:
	$(CC) $(SOURCES) -o $(BINARY) $(LDFLAGS)
