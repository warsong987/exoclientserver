#include "../unp.h"
#include "../sum.h"

void str_cli(FILE *fp, int sockfd)
{
	char			sendline[MAXLINE];
	struct args		args;
	struct result	result;

	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		if (sscanf(sendline, "%ld%ld", &args.arg1, &args.arg2) != 2) {
			printf("invalid input: %s", sendline);
			continue;
		}
		Writen(sockfd, &args, sizeof(args));

		if (Readn(sockfd, &result, sizeof(result)) == 0)
			err_quit("str_cli: server terminated prematurely");

		printf("%ld\n", result.sum);
	}
}

int main(int argc, char **argv) 
{
    int     i, sockfd[5];
    struct  sockaddr_in servaddr;

    if(argc != 2)
        err_quit("usage: tcpcli<IPaddress>");

    for(i = 0; i < 5; i++)
    {  
        sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0) {
            err_quit("\nInvalid address/ Address not supported \n");
            
        }

        if(connect(sockfd[i], (struct sockaddr*)&servaddr, sizeof(servaddr))<0) {
            err_sys("\nConnection Failed \n");
        }
    }

    str_cli(stdin, sockfd[0]);

    exit(0);

}

