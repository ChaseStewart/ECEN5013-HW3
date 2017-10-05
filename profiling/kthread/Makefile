# Author: Chase E Stewart
#
# Makefile to create the profile_kthread module, named profile_kthread.ko
# Note: after compilation completes, call sudo insmod profile_kthread.ko to add module
obj-m += profile_kthread.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
