	obj-m := ioctl.o
	KERNELDIR = /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o reader reader.c
	gcc -o writer writer.c
	gcc -o application application.c
	
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf reader
	rm -rf writer
	rm -rf application
	


