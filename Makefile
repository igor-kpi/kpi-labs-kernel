ifneq ($(KERNELRELEASE),)

ccflags-y := -std=gnu11
obj-m   := test1/hello.o

else

KDIR ?= $$PWD/kbuild

default:
	$(MAKE) -C $(KDIR) M=$$PWD
install:
	$(MAKE) -C $(KDIR) M=$$PWD modules_install
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

endif
