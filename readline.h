#ifndef __READLINE_H
#define __READLINE_H

#include <sys/types.h>

/*
 * reads a line from a file (eats '\r\n' pair if found)
 * fd - file descriptor
 * buf - buffer to write null-term string into
 * max - max number of characters to write into buffer includes null term
 * returns number of bytes written into buffer (inc null term), -1 error
 */
ssize_t readline(int fd, char *buf, ssize_t max);

#endif

/* To read all the lines of a file in a loop:

    int fid = open(filename, O_RDONLY);
    char buf[256];
    while (readline(fid, buf, sizeof(buf)) > 0)
        printf("'%s'\n", buf);
    close(fid);

*/
