#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <sys/resource.h>
#include <unistd.h>
#include <sys/syscall.h>

int my_read_file() {
    int ret = 0;
    char* cmdline = NULL;
    int fd;
    int count;

    cmdline = (char*) malloc(1024 * sizeof(char));
    if (cmdline == NULL){
        printf("fast_init: malloc failed.\n");
        return ret;
    }
    memset(cmdline, 0 , 1024);

    fd = open(CMD_PATH, NULL);
    if( fd <= 0) {
        printf("fast_init: open %s failed.\n", CMD_PATH);
        goto ERR1;
    }

    count = read(fd, cmdline, 1024);
    if(!count) {
        printf("fast_init: read failed.\n");
        goto ERR;
    }

    if(strstr(cmdline, BOOT_DEV_SD) != NULL) {
        ret = 1;
    }

ERR:
    close(fd);
ERR1:
    free(cmdline);

    return ret;
}
