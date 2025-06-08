#include "unp.h"

void sig_chld(int signo)
{
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, 1))>0)
    {
        printf("child %d terminated\en", pid);
    }
    
    return;
}