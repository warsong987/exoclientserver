#include	    "unp.h"

#include	    <stdarg.h>
#include	    <syslog.h>

int             daemon_proc;

static void     err_doit(int, int, const char *, va_list);

void err_sys(const char *fmt, ...) {
    va_list         ap;

    va_start(ap, fmt);
    err_doit(1, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}

void err_quit(const char *fmt, ...) {
    va_list     ap;

    va_start(ap, fmt);
    err_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
    int errno_save, n;
    char buf[MAXLINE+1];

    errno_save = errno;
    vsnprintf(buf, MAXLINE, fmt, ap);

    n = strlen(buf);

    if(errnoflag)
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));

    strcat(buf, "\n");

    if (daemon_proc){
        syslog(level, buf);
    } else {
        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    }
    return;  
}