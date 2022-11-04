/*
Day 10 / Assignment
### Blocking IO, Shared Interrupts and Bottom Halves

	Write a module implement blocking IO and that shares its IRQ with your Mouse interrupt. 

	a. You can generate a Mouse interrupts by press any key in Mouse.
	b. When ever read method invokes driver going to blocking stage.
	c. Make it use a top half and a bottom half.
	d. Check /proc/interrupts while it is loaded.
	e. Have the module keep track of the number of times the interrupt's halves are called.
	f. Implement the bottom half using  tasklets & work queues.

*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/io.h>

int id;
dev_t device_number;
int count = 0;
int data_present = 0;
wait_queue_head_t my_queue;
DECLARE_WAIT_QUEUE_HEAD(my_queue);

ssize_t my_read(struct file *, char __user *, size_t, loff_t *);
int my_open(struct inode *, struct file *);
int my_close(struct inode *, struct file *);

struct file_operations fops = {
    .read = my_read,
    .open = my_open,
    .release = my_close};

ssize_t my_read(struct file *fptr, char __user *usr, size_t size, loff_t *off)
{
    printk("Reading from device\n");
    if (data_present == 0)
    {
        printk("%s:%s\n", __FILE__, __func__);
        if (wait_event_interruptible(my_queue, (data_present == 1)))
        {
            printk(KERN_ERR "Signal Occurs\n");
        }
        else
        {
            printk(KERN_INFO "Process awaken - Now Data is available\n");
        }
    }
    else
    {
        printk(KERN_INFO "Data is available\n");
    }
    return 0;
}
int my_open(struct inode *node, struct file *fptr)
{
    printk("device opened\n");
    return 0;
}

int my_close(struct inode *node, struct file *fptr)
{
    printk("device closed\n");
    return 0;
}

static irqreturn_t mouse_handler(int irq, void *id)
{
    printk("inside the handler\n");
    count++;
    data_present = 1;
    wake_up(&my_queue);
    printk("The count is %d \n", count);
    return IRQ_HANDLED;
}

static int my_init(void)
{
    int result, rv;
    result = register_chrdev(60, "mouse_interrupt", &fops);
    rv = request_irq(12, mouse_handler, IRQF_SHARED, "Rajesh", &id);

    if (result < 0)
    {
        printk("Device could not be registered\n");
        return 0;
    }
    printk("Driver registered with major %d\n", MAJOR(device_number));
    return 0;
}

static void my_exit(void)
{
    unregister_chrdev(60, "mouse_interrupt");
    free_irq(12, &id);
    printk("unregistered\n");
}

module_init(my_init);
module_exit(my_exit);