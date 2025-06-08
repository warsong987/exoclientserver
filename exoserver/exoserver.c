#include "../unp.h"
#include "../sum.h"

void str_echo(int sockfd)
{
	ssize_t			n;
	struct args		args;
	struct result	result;

	for ( ; ; ) {
		if ( (n = Readn(sockfd, &args, sizeof(args))) == 0)
			return;

		result.sum = args.arg1 + args.arg2;
		Writen(sockfd, &result, sizeof(result));
	}
}

int main(int argc, char **argv) {

    int                 listenfd, connfd;
    pid_t               childpid;
    socklen_t           clilen;
    void                sig_chld(int);

    struct sockaddr_in  cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenfd == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    bzero(&servaddr, sizeof(servaddr));
   
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(listenfd, LISTENQ)) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    Signal(SIGCHLD, sig_chld);

    printf("Server listening on port %d\n", SERV_PORT);
    
    for(;;){
        clilen = sizeof(cliaddr);
        if(( connfd = accept(listenfd, (struct sockaddr *)&cliaddr, (socklen_t*)&clilen)) < 0){
            if(errno == EINTR){
                continue;
            } else {
                err_sys("accept error");
            }
        }
      
        if((childpid = fork())==0){
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }

    return 0;
}