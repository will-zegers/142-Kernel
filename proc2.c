#include "ioctl.h"

void main()
{
	int file_desc, ret_val;
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
		ioctl_get_msg(file_desc);
		ioctl(file_desc, IOCTL_SENDER_OUT, NULL);
		close(file_desc);
	}
}
