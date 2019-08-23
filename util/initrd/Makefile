CSRC = $(wildcard *.cpp)
SOURCES = $(CSRC:.cpp=.o)
BINARY=initrd
CFLAGS=-g
CC=g++

all: $(SOURCES) link

clean:
	-rm *.o
	-rm $(AUTODEPS)

.cpp:
	$(CC) -c -o $@ $< $(CFLAGS)

link: $(SOURCES)
	$(CC) $(SOURCES) -o $(BINARY) $(LDFLAGS)

%.o: %.cpp %.d
	$(CC) $(CFLAGS) -c -o $@ $<

%.d: %.cpp
	$(CC) $(CFLAGS) -MM -MT"$@ $(@:.d=.o)" -MP -MF $@ $<

# create a list of auto dependencies
AUTODEPS:= $(patsubst %.o,%.d, $(SOURCES))

 # include by auto dependencies
-include $(AUTODEPS)

