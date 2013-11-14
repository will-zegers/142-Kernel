#include "ioctl.h"

main()
{
	int file_desc, ret_val;
	char *msg = (char *)malloc(80 * sizeof(char));
	
	while (1) {
	
		printf("Message to send: ");
		scanf("%s", msg);
		
		file_desc = open(DEVICE_FILE_NAME, 0);
		ioctl(file_desc, IOCTL_SENDER_IN, NULL);
		if (file_desc < 0) {
			printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
			exit(-1);
		}


		ioctl_set_msg(file_desc, msg);

		ioctl(file_desc, IOCTL_RECEIVER_OUT, NULL);
		close(file_desc);
	}
}
