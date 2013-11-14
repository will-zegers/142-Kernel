#ifndef HERMES_H
#define HERMES_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100

#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)

#define IOCTL_GET_MSG _IOR(MAJOR_NUM, 1, char *)

#define IOCTL_SENDER_IN _IOR(MAJOR_NUM, 2, char *)

#define IOCTL_SENDER_OUT _IOR(MAJOR_NUM, 3, char *)

#define IOCTL_RECEIVER_IN _IOR(MAJOR_NUM, 4, char *)

#define IOCTL_RECEIVER_OUT _IOR(MAJOR_NUM, 5, char *)

#define DEVICE_FILE_NAME "hermes"

#endif
