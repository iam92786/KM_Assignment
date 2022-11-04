/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page   : www.facebook.com/kernelmasters                   *
 *      Website         : www.kernelmasters.org                            *
 *  Conducting Workshops on - Embedded Linux & Device Drivers Training.    *
 *  -------------------------------------------------------------------    *
 *  Tel : 91-9949062828, Email : kishore@kernelmasters.org                 *    
 *                                                                         *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation. No warranty is attached; we cannot take *
 *   responsibility for errors or fitness for use.                         *
 ***************************************************************************/
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/uaccess.h>

static int gpio_in = 11; // Par defaut : broche 10
module_param(gpio_in, int, 0644);

static dev_t          gpio_dev;
static struct cdev    gpio_cdev;
static struct class * gpio_class = NULL;

static int gpio_read(struct file * filp, char * buffer, size_t length, loff_t * offset);

static struct file_operations fops_gpio = {
    .owner   =  THIS_MODULE,
    .read    =  gpio_read,
  };

static int __init gpio_init (void)
{
  int err;

  if ((err = gpio_request(gpio_in, THIS_MODULE->name)) != 0) {
    return err;
  }

  if ((err = gpio_direction_input(gpio_in)) != 0) {
    gpio_free(gpio_in);
    return err;
  }

  if ((err = alloc_chrdev_region(& gpio_dev, 0, 1, THIS_MODULE->name)) < 0) {
    gpio_free(gpio_in);
    return err;
  }

  gpio_class = class_create(THIS_MODULE, "class_example");
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
  return 0;
}

static void __exit gpio_exit (void)
{
  cdev_del(& gpio_cdev);
  device_destroy(gpio_class, gpio_dev);
  class_destroy(gpio_class);
  unregister_chrdev_region(gpio_dev, 1);
  gpio_free(gpio_in);
}

static int gpio_read(struct file * filp, char * buffer, size_t length, loff_t * offset)
{
  char chaine[32];
  int lg;
  snprintf(chaine, 32, "%d", gpio_get_value(gpio_in));
  lg = strlen(chaine) + 1;
  if (lg > length)
    return -ENOMEM;
  if (copy_to_user(buffer, chaine, lg) != 0)
    return -EFAULT;
  return lg;
}

module_init(gpio_init);
module_exit(gpio_exit);
MODULE_LICENSE("GPL");

