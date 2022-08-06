>>Load module	insmod			module_init()
>>Open device	fopen			file_operations: open
>>Close device	fread 			file_operations: read
>>Write device	fwrite 			file_operations: write
>>Close device 	fclose 			file_operations: release
>>Remove module 	rmmod			module_exit()



//_____________________________________________________________________//


>>> Inside kernel source tree:

	$ make M=drivers/input/keyboard/ modules

>>> Outside Kernel source tree:

	Makefile contains the below kernel build system syntax.
		obj-m := hello.o

	$ make -C <KER_DIR> M=<PWD> modules



