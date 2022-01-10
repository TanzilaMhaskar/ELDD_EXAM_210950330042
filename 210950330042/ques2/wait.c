/*wait queue*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h> 
#include <linux/kdev_t.h>
#include <linux/fs.h> 
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/wait.h>
#include <linux/semaphore.h>
#define Name waitstatic

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TANZILA");
MODULE_DESCRIPTION("Wait queue static");
//intialize sem
struct semaphore sample_sem;

//decalring wait queue
DECLARE_WAIT_QUEUE_HEAD(wq);

int Name_open(struct inode *inode,struct file *filp);
int Name_release(struct inode *inode,struct file *filp);
ssize_t Name_write(struct file *filp,const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t Name_read(struct file *filp,char __user *Ubuff, size_t count, loff_t *offp);

dev_t Mydev=0;
struct file_operations fops=
{
 .owner  = THIS_MODULE,
 .open   = Name_open,
 .read   = Name_read,
 .write  = Name_write,
 .release= Name_release,
 };
 
 struct cdev *my_cdev;
 
 //flag for wait queue
 int flag =0;
 
 char kbuff[50];
 static int __init chardevice_init(void)
{
 int value;
 int MAJOR,MINOR;
 value= alloc_chrdev_region(&Mydev,0,1,"waitstatic");
 MAJOR=MAJOR(Mydev);
 MINOR=MINOR(Mydev);
 printk(KERN_ALERT "\nThis is init function\n");
 printk(KERN_ALERT "\nThe Major no. is= %d and Minor no. is =%d\n",MAJOR,MINOR);
 
 if(value<0)
 {
 printk(KERN_ALERT "\n The region is not obtain \n");
 return(-1);
 }
 my_cdev = cdev_alloc();
 my_cdev ->ops = &fops;
  
 value= cdev_add(my_cdev,Mydev,1);
 if(value<0)
 {
 printk(KERN_ALERT "\n The char device as not been obtain \n");
 unregister_chrdev_region(Mydev,1);
 }
 
 //intialize wait queue
 init_waitqueue_head(&wq);
 
 sema_init(&sample_sem ,1);
 return 0;
 }
 
 
 void __exit chardevice_exit(void)
 {
 int MAJOR,MINOR;
 MAJOR=MAJOR(Mydev);
 MINOR=MINOR(Mydev);
 printk(KERN_ALERT "\nThe Major no. is= %d and Minor no. is=%d\n",MAJOR,MINOR);
 unregister_chrdev_region(Mydev,1);
 cdev_del(my_cdev);
 printk(KERN_ALERT "\n Unregister the stuff GOODBYE!! \n");
 return;
}

int Name_open(struct inode *inode,struct file *filp)
{
printk(KERN_ALERT "\nThis is kernel open call\n");
return 0;
}

//write
ssize_t Name_write(struct file *filp,const char __user *Ubuff, size_t count, loff_t *offp)
{
unsigned long result;
ssize_t retval;

wait_event(wq,flag==0);
down(&sample_sem);
result=copy_from_user(kbuff,(char *)Ubuff,sizeof(kbuff));
up(&sample_sem);
wake_up(&wq);


if(result==0)
{
 printk(KERN_ALERT "\nMessage from user to kernel:\n %s \n",kbuff);
 printk(KERN_ALERT "\nData Succefully written\n");
 retval =count;
 return retval;
 }
 else if(result >0)
 {
 printk(KERN_ALERT "\nMessage from user:\n %s \n",kbuff);
 printk(KERN_ALERT "\nData some part is copied\n");
 retval =(count-result);
 return retval;
 }
 else 
 {
 printk(KERN_ALERT "\nError writting Data\n");
 retval =-EFAULT;
 return retval;
 }
 }
 
 //read
ssize_t Name_read(struct file *filp,char __user *Ubuff, size_t count, loff_t *offp)
{

unsigned long result;
ssize_t retval;
result = copy_to_user((char *)Ubuff,&kbuff,sizeof(kbuff));
flag ++;

if(result==0)
{
printk(KERN_ALERT "\nData reading Succefully \n");

retval =count;
return retval;
}
else if(result >0)
 {
 printk(KERN_ALERT "\nMessage from user:\n %s \n",kbuff);
 printk(KERN_ALERT "\nPart of reading data available\n");
 retval =(count-result);
 return retval;
 }
 else 
 {
 printk(KERN_ALERT "\nError Reading Data\n");
 retval =-EFAULT;
 return retval;
 }
 }
int Name_release(struct inode *inode,struct file *filp)
{
printk(KERN_ALERT "\nThis is kernel release call\n");

return 0;
}

module_init(chardevice_init);
module_exit(chardevice_exit);




 
 
 

   
