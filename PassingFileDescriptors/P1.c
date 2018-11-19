#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/socket.h>

void handle_error(char* msg) {do { perror(msg); exit(EXIT_FAILURE); } while(0);}


 // Structure of msghdr
//	 struct msghdr {
 //        void         *msg_name;       /* optional address */
 //        socklen_t     msg_namelen;    /* size of address */
 //        struct iovec *msg_iov;        /* scatter/gather array */
 //        size_t        msg_iovlen;     /* # elements in msg_iov */
 //        void         *msg_control;    /* ancillary data, see below */
 //        size_t        msg_controllen; /* ancillary data buffer len */
 //        int           msg_flags;      /* flags (unused) */
 //    };


// struct cmsghdr {
//         size_t cmsg_len;     Data byte count, including header
//         int    cmsg_level;   Originating protocol 
//         int    cmsg_type;   /* Protocol-specific type 
        
//         unsigned char cmsg_data[]; 
//     };


// struct iovec {
//                void  *iov_base;    /* Starting address of a buffer */
//                size_t iov_len;     /* Number of bytes to transfer */
//            };


static
void send_fd(int socket, int *fds, int n)  // send fd by socket
{
        struct msghdr msg = {0};
        struct cmsghdr *cmsg;
        char buf[CMSG_SPACE(sizeof(fds))], dup[256];
        // memset(buf, ‘\0’, sizeof(buf));
        struct iovec io = { .iov_base = &dup, .iov_len = sizeof(dup) };

        msg.msg_iov = &io;
        msg.msg_iovlen = 1;
        msg.msg_control = buf;
        msg.msg_controllen = sizeof(buf);

        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        cmsg->cmsg_len = CMSG_LEN(n * sizeof(int));

        memcpy ((int *) CMSG_DATA(cmsg), fds, n * sizeof (int));

        if (sendmsg (socket, &msg, 0) < 0)
                handle_error ("Failed to send message");
}

int
main(int argc, char *argv[]) {
        int sfd, fds[2];
        struct sockaddr_un addr;

        if (argc != 3) {
                fprintf (stderr, "Usage: %s <file-name1> <file-name2>\n", argv[0]);
                exit (1);
        }

        sfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sfd == -1)
               handle_error("Failed to create socket");

        memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, "/tmp/fd-pass.socket", sizeof(addr.sun_path) );

        fds[0] = open(argv[1], O_RDONLY);
        if (fds[0] < 0)
                handle_error("Failed to open file 1 reading \n");
        else
                fprintf (stdout, "Opened fd %d in parent\n", fds[0]);

        fds[1] = open(argv[2], O_RDONLY);
        if (fds[1] < 0)
                handle_error("Failed to open file 2 reading \n");
        else
                fprintf (stdout, "Opened fd %d in parent\n", fds[1]);

        if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
               handle_error("Failed to connect to socket \n");

        send_fd (sfd, fds, 2);

        exit(EXIT_SUCCESS);
}