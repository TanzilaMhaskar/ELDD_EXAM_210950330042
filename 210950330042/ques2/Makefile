obj-m := wait.o
KER = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
	
all:
	$(MAKE) -C $(KER) M=$(PWD) modules
	gcc -o writer writer.c
	gcc -o reader reader.c
	
install:
	$(MAKE) -C $(KER) M=$(PWD) modules_install
	
clean:
	$(MAKE) -C $(KER) M=$(PWD) clean
	rm -rf writer
	rm -rf reader
	
