#include "unp.h"

ssize_t writen(int fd, const void *vprt, size_t n)
{
    size_t          nleft;
    ssize_t         nwritten;
    const char      *ptr;

    ptr = vprt;
    nleft = n;

    while (nleft > 0)
    {
        if((nwritten = write(fd, ptr, nleft))<=0) {
            if(nwritten<0 && errno == EINTR)
                nwritten = 0;
            else
                return(-1);
        }

        nleft   -= nwritten;
        ptr     += nwritten;
    }

    return n;
}

void Writen(int fd, void *ptr, size_t nbytes)
{
    if(writen(fd, ptr, nbytes)!=nbytes)
        err_sys("writen error");
}