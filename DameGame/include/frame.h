#ifndef FRAME_H
#define FRAME_H

#include <stddef.h>

#include <stdio.h>
#include <string.h>

#include <sys/param.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <linux/if_ether.h> /* Ether protocol */
#include <net/if.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <arpa/inet.h>

#define MAX_PACKET_SIZE 1500    /* Maximum size of a packet */
#define ADDR_SIZE       6       /* Size of IP address */
#define DATA_TYPE_SIZE  4       /* Size of data type descripion */
#define DATA_SIZE       (MAX_PACKET_SIZE - 2*ADDR_SIZE - DATA_TYPE_SIZE) /* Size of data */

#define JAM_CHAR        ' '

typedef struct in_addr in_addr;

typedef struct {
    in_addr src;
    in_addr dest;
    char data_type[DATA_TYPE_SIZE + 1];
    char data[DATA_SIZE];
} frame;

/**
 * @brief Make a frame
 * @param src the source address
 * @param dest the destination address
 * @param datatype the type of the frame
 * @param data the data to send with the frame
 * @return
 */
frame make_frame(in_addr src, in_addr dest, const char *datatype, char * data);






#endif
