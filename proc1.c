#include "hermes.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

main()
{
	int file_desc, ret_val;
	char *msg = (char *)malloc(42 * sizeof(char));
	
	while (1) {
	
		printf("Message to send: ");
		scanf("%s", msg);
		
		file_desc = open(DEVICE_FILE_NAME, 0);
		ioctl(file_desc, IOCTL_SENDER_IN, NULL);
		if (file_desc < 0) {
			printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
			exit(-1);
		}

		ret_val = ioctl(file_desc, IOCTL_SET_MSG, msg);

	        if (ret_val < 0) {
	                printf("ioctl_set_msg failed:%d\n", ret_val);
	                exit(-1);
 	       }


		ioctl(file_desc, IOCTL_RECEIVER_OUT, NULL);
		close(file_desc);
	}
}
