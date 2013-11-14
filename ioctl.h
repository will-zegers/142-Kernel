#ifndef IOCTL_H 
#define IOCTL_H

#include "hermes.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

ioctl_set_msg(int file_desc, char *message)
{
	int ret_val;

	ret_val = ioctl(file_desc, IOCTL_SET_MSG, message);

	if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
}

ioctl_get_msg(int file_desc)
{
	int ret_val;
	char message[100];

	ret_val = ioctl(file_desc, IOCTL_GET_MSG, message);

	if (ret_val < 0) {
		printf("ioctl_get_msg failed:%d\n", ret_val);
		exit(-1);
	}

	printf("get_msg message:%s\n", message);
}
#endif
