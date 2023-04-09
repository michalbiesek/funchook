#define _GNU_SOURCE

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "include/funchook.h"

// funchook function
static int (*socket_func)(int domain, int type, int protocol);

static int
socket_hook(int domain, const void *type, int protocol) {
    int sockfd;

    fprintf(stderr, "socket_hook start\n");
    sockfd = socket_func(AF_INET, SOCK_STREAM, 0);
    fprintf(stderr, "socket_hook end\n");
    return sockfd;
}

static void
ftest(void) {
    funchook_t *funchook = funchook_create();

    socket_func = socket;
    int res = funchook_prepare(funchook, (void**)&socket_func, socket_hook);

    res = funchook_install(funchook, 0);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    close(sockfd);

    funchook_uninstall(funchook, 0);

    res = funchook_destroy(funchook);
}

int
main(int argc, char* argv[]) {
    printf("Starting test  %s\n", argv[0]);
    ftest();
    return 0;
}
