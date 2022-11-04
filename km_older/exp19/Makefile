obj-m += gpio-input.o
obj-m += gpio-interrupt.o
obj-m += gpio-output.o

KBUILD_CFLAGS   += -g

ARCH=arm
CROSS_COMPILE=arm-linux-gnueabihf-

all:
	make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -C /home/im-rt-lp-1148/KM_GITHUB/beagleboneblack-kernel M=`pwd` modules
 
clean:
	make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -C /home/im-rt-lp-1148/KM_GITHUB/beagleboneblack-kernel M=`pwd` clean
