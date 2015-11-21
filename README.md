[![Build Status](https://travis-ci.org/nickgn12/x86-thing.svg)](https://travis-ci.org/nickgn12/x86-thing)

# x86-thing
Basic "kernel" written in x86 assembly.

# feature list
 - [x] enable a20 gate
 - [x] load GDT table
 - [x] load interrupt table
 - [x] video (text) driver
 - [x] serial driver
 - [x] PIT timer
 - [x] kernel panic
 - [ ] keyboard driver
 - [ ] memory paging
 - [ ] heap
 - [ ] virtual file system

 will add more stuff as i think of it

# compiling
```bash
make
```
# running
make sure x86 qemu is installed

```bash
./run
```

# debugging
to run qemu in debug mode

```bash
./debug
```

to start gdb

```bash
./gdb
```
