#! /bin/bash
qemu-system-i386 -s -S -kernel kernel -initrd ../initrd/initrd.tar -monitor stdio -serial stdio
