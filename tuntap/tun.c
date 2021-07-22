#include <net/if.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <linux/if_tun.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>


int tun_alloc(int flags) {

    struct ifreq ifr;
    int fd, err;

    if ((fd = open("/dev/net/tun", O_RDWR)) < 0) {
        return fd;
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = flags;

    if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
        close(fd);
        return err;
    }

    return fd;
}

int main(int argc, char *argv[]) {

    int tun_fd, nread;
    char buffer[1500];

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *        IFF_NO_PI - Do not provide packet information
     */
    tun_fd = tun_alloc(IFF_TUN | IFF_NO_PI);

    if (tun_fd < 0) {
        perror("Allocating interface");
        exit(1);
    }

    while (1) {
        nread = read(tun_fd, buffer, sizeof(buffer));
        if (nread < 0) {
            perror("Reading from interface");
            close(tun_fd);
            exit(1);
        }

        printf("Read %d bytes from tun/tap device %s\n", nread, buffer);
    }
    return 0;
}
