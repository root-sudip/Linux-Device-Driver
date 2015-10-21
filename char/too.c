#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>  
/*#include <linux/device.h> */ 

int compare_string(char *first,const char *second) {
   while (*first == *second) {
      if (*first == '\0' || *second == '\0')
         break;
 
      first++;
      second++;
   }
 
   if (*first == '\0' && *second == '\0')
      return 0;
   else
      return -1;
}

int count = 1;
static char message[246];
static short size_of_message;
int fopen(struct inode *f,struct file *ff){
	
	printk(KERN_ALERT "%s OPENING (%d) Time \n",__FUNCTION__,count);
	count++;
	return 0;
}

int frelease(struct inode *f,struct file *ff)
{
	printk(KERN_ALERT "Inside the %s function \n",__FUNCTION__);
	return 0;
}

static ssize_t freadd(struct file *file,char __user *buff,size_t count,loff_t *position)
{
	int error_count = 0;
   // copy_to_user has the format ( * to, *from, size) and returns 0 on success
   error_count = copy_to_user(buff, message, size_of_message);
 
   if (error_count==0){            // if true then have success
      printk(KERN_INFO "EBBChar: Sent %d characters to the user\n", size_of_message);
      return 0;  // clear the position to the start and return 0
   }
   else {
      printk(KERN_INFO "EBBChar: Failed to send %d characters to the user\n", error_count);
      return -EFAULT;              // Failed -- return a bad address message (i.e. -14)
   }
}


static ssize_t fwrite(struct file *filep, const char *buffer, size_t len, loff_t *offset){
	if(compare_string("key",buffer)==0){
	sprintf(message, "%s \n", buffer);   // appending received string with its length
   size_of_message = strlen(message);                 // store the length of the stored message
   printk(KERN_INFO "EBBChar: Received %d characters from the user\n", size_of_message);
   return len;
}

else
{
	return -EINVAL;
}
}


struct file_operations fop={
	.owner = THIS_MODULE,
	.open  = fopen,
	.read =freadd,
	.release = frelease,
	.write = fwrite,
};

static int load(void){
	printk(KERN_ALERT "Driver is loaded \n");
	register_chrdev(240,"chr_dev",&fop);
	return 0;
}
static void unload(void){
	printk(KERN_ALERT "Driver unload \n");
	unregister_chrdev(240,"chr_dev");
}


module_init(load);
module_exit(unload);