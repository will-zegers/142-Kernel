#include "hermes.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

void main()
{
	int file_desc, ret_val;
	char message[42];
	while(1) {

		file_desc = open(DEVICE_FILE_NAME, 0);
		if (file_desc < 0) {
			printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
			exit(-1);
		}

		ioctl(file_desc, IOCTL_RECEIVER_IN, NULL);
		close(file_desc);

		sleep(10);
	
		file_desc = open(DEVICE_FILE_NAME, 0);
	        ret_val = ioctl(file_desc, IOCTL_GET_MSG, message);

		if (ret_val < 0) {
			printf("ioctl_get_msg failed:%d\n", ret_val);
			exit(-1);
		}

		printf("Message received: %s\n", message);
		
		ioctl(file_desc, IOCTL_SENDER_OUT, NULL);
		close(file_desc);
	}
}
