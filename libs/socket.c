#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <memory.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
//#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "tools/socket.h"

int send_result(char *socket_path,  char* buf, int buf_len)
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
            close(sd);
            break;
        }

        if (send(sd, buf, buf_len, 0) > 0) {
            status = 1;
        }
        close(sd);
    } while (0);
    return status;
}
