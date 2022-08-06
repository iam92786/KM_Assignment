#include<linux/fs.h>
#include<linux/kernel.h>    //printk
#include<linux/module.h>    //modules
#include<linux/kdev_t.h>
#include<linux/init.h>

ssize_t my_read(struct file *, char __user *, size_t, loff_t *);
ssize_t my_write(struct file *, const char __user *, size_t, loff_t *);
int my_open(struct inode *, struct file *);
int my_close(struct inode *, struct file *);


//structure initialization
struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_close
};

ssize_t my_read(struct file *flip, char __user *usr, size_t size, loff_t *off)
{
    printk("my_read() %d %s\n",__LINE__,__FILE__);
    return 0;
}

ssize_t my_write(struct file *flip, const char __user *usr, size_t size, loff_t *off)
{
    printk("my_write() %d %s\n",__LINE__,__FILE__);
    return size;
}
\
int my_open(struct inode *ino, struct file *flip)
{
    printk("my_open() %d %s\n",__LINE__,__FILE__);
    return 0;
}

int my_close(struct inode *ino, struct file *flip)
{
    printk("my_close() %d %s\n",__LINE__,__FILE__);
    return 0;
}


int char_init(void)
{
    int ret;

    ret = register_chrdev(60,"mycahr",&fops);
    if( ret < 0)
    {
        printk("register_charderv() failed ! ");
        return -1;
    }

    return 0;
}

void char_exit(void)
{
    unregister_chrdev(60,"mychar");
    printk("Unregister_chardev\n");
}


module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");