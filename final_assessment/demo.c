#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/uaccess.h>

static int gpio_in = 11;
static int gpio_out = 10; // Par defaut : broche 10
module_param(gpio_in, int, 0644);
int count = 0;
int data_present = 0;
wait_queue_head_t my_queue;
DECLARE_WAIT_QUEUE_HEAD(my_queue);

static dev_t gpio_dev;
static struct cdev gpio_cdev;
static struct class *gpio_class = NULL;
static int gpio_irq = 0;

static int gpio_read(struct file *filp, char *buffer, size_t length, loff_t *offset);
ssize_t my_read(struct file *, char __user *, size_t, loff_t *);

static struct file_operations fops_gpio = {
    .owner = THIS_MODULE,
    .read = gpio_read,
};

static irqreturn_t switch_handler(int irq, void *id)
{
    printk("inside the handler\n");
    count++;
    data_present = 1;
    wake_up(&my_queue);
    printk("The count is %d \n", count);
    return IRQ_HANDLED;
}

static int __init gpio_init(void)
{
    int err;
    gpio_irq = gpio_to_irq(gpio_in);

    printk("interrupt request number:%d", gpio_irq);

    if ((err = gpio_request(gpio_in, THIS_MODULE->name)) != 0)
    {
        printk("err:%d\n", err);
        return err;
    }
    if ((err = gpio_request(gpio_out, THIS_MODULE->name)) != 0)
        return err;
    if ((err = gpio_direction_output(gpio_out, 0)) != 0)
    {
        gpio_free(gpio_out);
        return err;
    }
    if ((err = gpio_direction_input(gpio_in)) != 0)
    {
        printk("err:%d\n", err);
        gpio_free(gpio_in);
        return err;
    }
    printk("err:%d\n", err);

    if ((err = alloc_chrdev_region(&gpio_dev, 0, 1, THIS_MODULE->name)) < 0)
    {
        gpio_free(gpio_in);
        return err;
    }

    gpio_class = class_create(THIS_MODULE, "class_gpio");
    if (IS_ERR(gpio_class))
    {
        unregister_chrdev_region(gpio_dev, 1);
        gpio_free(gpio_in);
        return -EINVAL;
    }

    device_create(gpio_class, NULL, gpio_dev, NULL, THIS_MODULE->name);

    cdev_init(&gpio_cdev, &fops_gpio);

    if ((err = cdev_add(&gpio_cdev, gpio_dev, 1)) != 0)
    {
        device_destroy(gpio_class, gpio_dev);
        class_destroy(gpio_class);
        unregister_chrdev_region(gpio_dev, 1);
        gpio_free(gpio_in);
        return err;
    }

    if ((err = request_irq(gpio_irq, switch_handler, 0, THIS_MODULE->name, 0)) != 0)
    {
        gpio_free(gpio_in);
        gpio_free(gpio_out);
        return err;
    }
    irq_set_irq_type(gpio_irq, IRQF_TRIGGER_RISING);
    return 0;
}

static void __exit gpio_exit(void)
{
    cdev_del(&gpio_cdev);
    device_destroy(gpio_class, gpio_dev);
    class_destroy(gpio_class);
    unregister_chrdev_region(gpio_dev, 1);
    gpio_free(gpio_in);
    free_irq(gpio_irq, THIS_MODULE->name);
    gpio_free(gpio_out);
}

static int gpio_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    char chaine[32];
    int lg;
    snprintf(chaine, 32, "%d", gpio_get_value(gpio_in));
    lg = strlen(chaine) + 1;
    if (lg > length)
        return -ENOMEM;
    if (copy_to_user(buffer, chaine, lg) != 0)
        return -EFAULT;
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
    return lg;
}

module_init(gpio_init);
module_exit(gpio_exit);
MODULE_LICENSE("GPL");
