#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "common/socket.h"

int send_result(char *socket_path,  char* buf, int buf_len, char *recv_message, int recv_message_len)
{
    struct sockaddr_un serveraddr;
    int sd;

    int status = 0;
    do {
        sd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sd < 0) {
            break;
        }

        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sun_family = AF_UNIX;
        strcpy(serveraddr.sun_path, socket_path);

        if (connect(sd, (struct sockaddr *)&serveraddr, SUN_LEN(&serveraddr)) < 0) {
            break;
        }

        if (write(sd, buf, buf_len) < 0) {
            break;
        }

        if (recv_message_len) {
            int readLen = read(sd, recv_message, recv_message_len);
            if (readLen < 0) {
                break;
            }
            recv_message[readLen] = '\0';
        }

        status = 1;
        close(sd);
    } while (0);
    return status;
}
