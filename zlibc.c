#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <sys/resource.h>
#include <unistd.h>
#include <sys/syscall.h>

/*
 * read string from file.
 */
int zlibc_read_file_once(const char* path, char** str, size_t length) {
    int ret = -1;
    char* buf = NULL;
    int fd;
    int count;

    fd = open(path, NULL);
    if( fd <= 0) {
        printf("zlibc_read_file: open %s failed.\n", path);
        goto READ_FILE_OUT;
    }

    buf = (char*) malloc(length * sizeof(char));
    if (buf == NULL){
        printf("zlibc_read_file: malloc failed.\n");
        goto READ_FILE_OUT1;
    }
    memset(buf, 0 , length);

    ret = read(fd, buf, length);
    if(ret > 0) {
        printf("zlibc_read_file: read %d bytes.\n", ret);
	*str = buf;
	goto READ_FILE_OUT1;
    }

    printf("zlibc_read_file: read failed.\n");

    free(buf);

READ_FILE_OUT1:
    close(fd);

READ_FILE_OUT:
    return ret;
}
