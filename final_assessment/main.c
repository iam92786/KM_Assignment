#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/irq.h>


static int switch_interupt = 0;
static int count = 0;
static int gpio_irq = 0;

//interrupt
wait_queue_head_t my_queue;
DECLARE_WAIT_QUEUE_HEAD(my_queue);

static int gpio_in = 11; // Par defaut : broche 10
//module_param(gpio_in, int, 0644);

static dev_t          gpio_dev;
static struct cdev    gpio_cdev;
static struct class * gpio_class = NULL;

static int gpio_read(struct file * filp, char * buffer, size_t length, loff_t * offset);

static struct file_operations fops_gpio = {
		.owner   =  THIS_MODULE,
		.read    =  gpio_read,
	};


irqreturn_t handler_irq_gpio(int irq, void * ident)
{
	printk("inside the handler\n");
    count++;
    switch_interupt = 1;
    wake_up(&my_queue);
    printk("The count is %d \n", count);

	return IRQ_HANDLED;
}


static int __init gpio_init (void)
{
	int err;

	if ((err = gpio_request(gpio_in, THIS_MODULE->name)) != 0) {
	printk("err:%d\n",err);
		return err;
	}

	printk("err:%d\n",err);
	if ((err = gpio_direction_input(gpio_in)) != 0) {
	printk("err:%d\n",err);
		gpio_free(gpio_in);
		return err;
	}
	printk("err:%d\n",err);


	if ((err = alloc_chrdev_region(& gpio_dev, 0, 1, THIS_MODULE->name)) < 0) {
		gpio_free(gpio_in);
		return err;
	}

/*    err = register_chrdev(60,"mychar", &fops_gpio);
	if(err < 0)
	{
		printk("Device could not be registered\n");
		return -EPERM;
	}
*/
	gpio_class = class_create(THIS_MODULE, "class_gpio");
	if (IS_ERR(gpio_class)) {
		unregister_chrdev_region(gpio_dev, 1);
		gpio_free(gpio_in);
		return -EINVAL;
	}

	device_create(gpio_class, NULL, gpio_dev, NULL, THIS_MODULE->name);

	cdev_init(& gpio_cdev, & fops_gpio);

	if ((err = cdev_add(& gpio_cdev, gpio_dev, 1)) != 0) {
		device_destroy(gpio_class, gpio_dev);
		class_destroy(gpio_class);
		unregister_chrdev_region(gpio_dev, 1);
		gpio_free(gpio_in);
		return err;
	}

	//gpio irq
	gpio_irq = gpio_to_irq(gpio_in);
	printk("interrupt request number:%d",gpio_irq);

    if ((err = request_irq(gpio_irq, handler_irq_gpio, 0 , THIS_MODULE->name, 0)) != 0) {
    gpio_free(gpio_in);
    //gpio_free(gpio_out);
    return err;
  	}
	irq_set_irq_type(gpio_irq, IRQF_TRIGGER_RISING);




	return 0;
}

static void __exit gpio_exit (void)
{
	free_irq(gpio_irq, THIS_MODULE->name);
	cdev_del(& gpio_cdev);
	device_destroy(gpio_class, gpio_dev);
	class_destroy(gpio_class);
	unregister_chrdev_region(gpio_dev, 1);
	gpio_free(gpio_in);
}

static int gpio_read(struct file * filp, char * buffer, size_t length, loff_t * offset)
{
	printk("Reading from device\n");
	if (switch_interupt == 0)
    {
        printk("%s:%s\n", __FILE__, __func__);
        if (wait_event_interruptible(my_queue, (switch_interupt == 1)))
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
	switch_interupt = 0;
    return 0;
}

module_init(gpio_init);
module_exit(gpio_exit);
MODULE_LICENSE("GPL");
