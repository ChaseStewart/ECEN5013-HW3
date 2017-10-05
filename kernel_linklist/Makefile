# Author: Chase E Stewart
#
# Makefile to create the kernel_linklist module, named print_kthreads.ko
# Note: after compilation completes, call sudo insmod print_kthreads.ko to add module

obj-m += print_kthreads.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
