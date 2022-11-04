//Write a module implement blocking IO and that shares its IRQ with your Mouse interrupt. 
Ans:


*mouse interrupt handler*/ 
#include <linux/kernel.h> /* printk */
#include <linux/module.h>/* This Header contains the necessary stuff for the Module */
#include <linux/init.h> /* Required header for the Intialization and Cleanup Functionalities....  */
#include <linux/fs.h> /* struct file_operations, struct file and struct inode */
#include <linux/kdev_t.h>
#include <linux/wait.h>  /* wait_event() , wait_event_interruptible(), wait_event_timeout() , wait_event_interruptible_timeout()  */
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/io.h>
int id;
int count=0; 
#define NAME "mouse"
int data_present=0;
wait_queue_head_t my_queue;
DECLARE_WAIT_QUEUE_HEAD(my_queue); 
dev_t temp;
ssize_t slpy_read(struct file *, char __user *, size_t, loff_t *);
ssize_t slpy_write(struct file *, const char __user *, size_t, loff_t *);
int slpy_open(struct inode *, struct file *);
int slpy_close(struct inode *, struct file *); 
struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = slpy_read,
    .open = slpy_open,
    .release = slpy_close
}; 
/*Device methods */
ssize_t slpy_read(struct file *filp, char __user *usr, size_t size, loff_t *off)
{
    printk("Reading from device\n");
    if(data_present == 0)
    {
        printk("Process %d (%s) Going to Sleep\n",current->pid,current->comm);
        // Data is not available
//        wait_event(my_queue,(data_present==1)); // uninterruptible sleep
        printk(KERN_INFO "Process awaken - Now Data is available\n");
        if(wait_event_interruptible(my_queue,(data_present==1)))
        {
        // error
        printk(KERN_ERR "Signal Occurs\n");
        }
        else
        {
        //success
        printk(KERN_INFO "Process awaken - Now Data is available\n");
        }
    }
    else
    {
    printk(KERN_INFO "Data is available\n");
    }
    return 0; //-EPERM;
} 
int slpy_open(struct inode *ino, struct file *filp)
{
    printk("device opened\n");
    return 0;
}
static irqreturn_t mouse_handler(int irq, void *id)
{
    printk("Trying to write into the device\n");
    printk("Process %d (%s) Going to Wakeup\n",current->pid,current->comm);
    data_present=1;
    wake_up(&my_queue);
        return IRQ_HANDLED;
} 
int slpy_close(struct inode *ino, struct file *filp)
{
    printk("device closed\n");
    return 0;
} 
static int slpy_init(void)
{
    int result,rv;
    result = register_chrdev(60, NAME, &fops);
    rv = request_irq(12, mouse_handler, IRQF_SHARED, "swathi",&id);    
        if (result < 0)
        {
                printk ("device could not be registered\n");
               return 0;
        }
    return 0; 
}
static void slpy_exit(void)
{
    unregister_chrdev(60, NAME);
    free_irq(12,&id);
    printk("simple_slpy unregistered\n");
} 
module_init(slpy_init);
module_exit(slpy_exit);

