#include <unistd.h>
#include <assert.h>
#include "readline.h"

ssize_t readline(int fd, char *buf, ssize_t max)
{
    ssize_t total = 0;  /* total bytes read */
    int ret = 0;

    /* read char at time until newline (or EOF) */
    while (total < max && (ret = read(fd, buf, 1)) == 1
            && buf[0] != '\r' && buf[0] != '\n') {
        total++;
        buf++;
    }
    if (total == 0) return (0);  /* nothing left */
    if (ret < 0) return (-1);   /* error */

    /* if \r then \n sure to follow (maybe?) */
    if (buf[0] == '\r') {
        assert(read(fd, buf, 1) == 1);
        total++;
    }

    buf[0] = '\0';
    return(total + 1);
}
