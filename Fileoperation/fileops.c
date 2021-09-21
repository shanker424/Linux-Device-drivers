#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/device.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>

dev_t dev = 0;
static struct cdev my_cdev;
static struct class *dev_class;

static int __init scd_init(void);
static void __exit scd_exit(void);

static int scd_open(struct inode *, struct file *fop);
static int scd_close(struct inode *, struct file *fop);
static ssize_t scd_write(struct file *fop, const char __user *buf, size_t len, loff_t *loff);
static ssize_t scd_read(struct file *fop, char __user *buf, size_t len, loff_t *loff);

struct file_operations fops = {
.owner = THIS_MODULE,
.open = scd_open,
.release = scd_close,
.write = scd_write,
.read = scd_read,
 };
 
 static int scd_open(struct inode *inode, struct file *fop)
 {
 	pr_info("device is opened !!!\n");
 	return 0;
 }
 
 
 static int scd_close(struct inode *inode, struct file *fop)
 {
 	pr_info("device closed successfully !!!\n");
 	return 0;
 }
 
 
 static ssize_t scd_write(struct file *fop, const char __user *buf, size_t len, loff_t *loff)
 {
 		pr_info("device write function is called !!!\n");
 		return len;
 } 
 
 static ssize_t scd_read(struct file *fop, char __user *buf, size_t len, loff_t *loff)
 {
 		pr_info("device read function is called !!!\n");
 		return 0;
 }
 
 
 
 static int __init scd_init(void)
 {
 	if((alloc_chrdev_region(&dev,0,1, "my_driver"))<0)
 	{
 		pr_info("device cant be allocated \n");
 		return -1;
 	}
 	pr_info("device is allocated successfully with Major: %d, Minor: %d !!!", MAJOR(dev), MINOR(dev));
 	
 	cdev_init(&my_cdev, &fops);
 	if(cdev_add(&my_cdev,dev, 1) <0)
 	{	pr_info("device cant be added to system \n");
 		goto r_class;
 	}
 	if(dev_class = class_create(THIS_MODULE, "my_driver") == NULL)
 	{
 		pr_info("class can't be created \n");
 		goto r_class;
 	}
 	if(device_create(dev_class, NULL, dev, NULL, "my_driver") == NULL)
 	{
 		pr_info("device cant be created \n");
 		goto r_device;
 	}
 	pr_info("device inserted successfully\n");
 	
 	r_device:
 		class_destroy(dev_class);
 	r_class:
 		unregister_chrdev_region(dev,1);		
 		return -1;
 }
 
 static void __exit scd_exit(void)
 {
 	device_destroy(dev_class, dev);
 	class_destroy(dev_class);
 	cdev_del(&my_cdev);
 	unregister_chrdev_region(dev,1);
 	pr_info("device removed successfully.... \n");
 
 }
 
 module_init(scd_init);
 module_exit(scd_exit);
 
 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("shanker");
 MODULE_DESCRIPTION("simple char device driver");
 MODULE_VERSION("1.3");
