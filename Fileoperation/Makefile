obj-m := fileops.o
KDIR = /usr/src/linux-headers-$(shell uname -r)

all:
	make -C $(KDIR) M=$(shell pwd) modules
clean: 
	make -C $(KDIR) M=$(shell pwd) clean
