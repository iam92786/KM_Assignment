obj-m += hello.o
#EXP18 : Cross compiled Hello world Device Driver module and load in to BBB
all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/im-rt-lp-1148/KM_GITHUB/beagleboneblack-kernel M=`pwd` modules
	#make -C /lib/modules/`uname -r`/build M=$(shell pwd) modules
	#make -C /usr/src/linux M=$(shell pwd) modules
clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/im-rt-lp-1148/KM_GITHUB/beagleboneblack-kernel M=`pwd` clean
	#make -C /usr/src/linux M=$(shell pwd) clean
	make -C /lib/modules/`uname -r`/build M=$(shell pwd) clean
	
install:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/im-rt-lp-1148/KM_GITHUB/beagleboneblack-kernel M=`pwd` install
