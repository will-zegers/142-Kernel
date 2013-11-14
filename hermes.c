#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "hermes.h"
#define DEVICE_NAME "hermes"
#define BUF_LEN 80

static int Device_Open = 0;

static char Message[BUF_LEN];

static char *Message_Ptr;

static int sender = 0;
static int receiver = 0;

static int device_open(struct inode *inode, struct file *file)
{
	if (Device_Open)
		return -EBUSY;

	Device_Open++;
	
	Message_Ptr = Message;
	try_module_get(THIS_MODULE);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;

	module_put(THIS_MODULE);
	return 0;
}

static ssize_t device_read(struct file *file,
			   char __user * buffer,
			   size_t length,
			   loff_t * offset)
{
	int bytes_read = 0;

	if (*Message_Ptr == 0)
		return 0;

	while (length && *Message_Ptr) {

		put_user(*(Message_Ptr++), buffer++);
		length--;
		bytes_read++;
	}

	return bytes_read;
}

static ssize_t device_write(struct file *file,
                           const char __user * buffer,
                           size_t length, loff_t * offset)
{
	int i;

	for (i = 0; i < length && i < BUF_LEN; i++)
		get_user(Message[i], buffer + i);

	Message_Ptr = Message;

	return i;
}

long device_ioctl(struct file *file,
		 unsigned int ioctl_num,
		 unsigned long ioctl_param)
{
	int i;
	char *temp;
	char ch;

	switch (ioctl_num) {
	case IOCTL_SET_MSG:
		if (receiver) {
			temp = (char *)ioctl_param;

			get_user(ch, temp);
			for (i = 0; ch && i < BUF_LEN; i++, temp++)
				get_user(ch, temp);

			device_write(file, (char *)ioctl_param, i, 0);
			printk(KERN_ALERT "%s\n", (char *)ioctl_param);

			break;
		} else {
			printk(KERN_ALERT "No receivers have checked in!\n");
		}	

	case IOCTL_GET_MSG:
		if (sender) {	
			i = device_read(file, (char *)ioctl_param, 99, 0);

			put_user('\0', (char *)ioctl_param + i);
		} else {
			printk(KERN_ALERT "No senders have checked in!\n");
		}	
		break;
	
	case IOCTL_SENDER_IN:
		sender=1;
		break;
	
	case IOCTL_SENDER_OUT:
		sender=0;
		break;
	
	case IOCTL_RECEIVER_IN:
		receiver=1;
		break;
	case IOCTL_RECEIVER_OUT:
		receiver=0;
		break;
	}

	return 0;
}

struct file_operations Fops = {
	.read = device_read,
	.write = device_write,
	.unlocked_ioctl = device_ioctl,
	.open = device_open,
	.release = device_release,
};

int init_module()
{
	int ret_val;
	ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);

	if (ret_val < 0) {
		printk(KERN_ALERT "%s failed with %d\n",
		       "Sorry, registering the character device ", ret_val);
		return ret_val;
	}

	printk(KERN_ALERT "%s successfully registered with major dev# %d!\n", DEVICE_NAME, MAJOR_NUM);

	return 0;
}

void cleanup_module()
{
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}
