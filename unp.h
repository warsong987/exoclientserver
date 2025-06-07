#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>

#define	MAXLINE		     4096
#define	SERV_PORT		 9877	
#define	LISTENQ		     1024

void	 Writen(int, void *, size_t);
ssize_t	 writen(int, const void *, size_t);
void	 err_sys(const char *, ...);
void     err_quit(const char *fmt, ...);

ssize_t	 readline(int, void *, size_t);
ssize_t	 Readline(int, void *, size_t);
void	 Fclose(FILE *);
FILE	*Fdopen(int, const char *);
char	*Fgets(char *, int, FILE *);
FILE	*Fopen(const char *, const char *);
void	 Fputs(const char *, FILE *);