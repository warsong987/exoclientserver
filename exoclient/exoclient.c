#include "../unp.h"

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while (Fgets(sendline, MAXLINE, fp)!=NULL)
    {
        Writen(sockfd, sendline, strlen(sendline));

        if(Readline(sockfd, recvline, MAXLINE) == 0) {
            err_quit("str_cli: server terminated prematurely");
        }

        Fputs(recvline, stdout);
    }
    
}

int main(int argc, char **argv) 
{
    int     sockfd;
    struct  sockaddr_in servaddr;

    if(argc != 2)
        err_quit("usage: tcpcli<IPaddress>");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0) {
        err_quit("\nInvalid address/ Address not supported \n");
        
    }

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0) {
        err_sys("\nConnection Failed \n");
    }

    str_cli(stdin, sockfd);

    exit(0);

}

