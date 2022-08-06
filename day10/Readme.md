## Lab Assignments

### Blocking IO, Shared Interrupts and Bottom Halves

	Write a module implement blocking IO and that shares its IRQ with your Mouse interrupt. 

	a. You can generate a Mouse interrupts by press any key in Mouse.
	b. When ever read method invokes driver going to blocking stage.
	c. Make it use a top half and a bottom half.
	d. Check /proc/interrupts while it is loaded.
	e. Have the module keep track of the number of times the interrupt's halves are called.
	f. Implement the bottom half using  tasklets & work queues.
