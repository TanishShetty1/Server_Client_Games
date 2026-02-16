#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>


#define BUFSIZE 1024

int recv_line(int socket_fd,char* buffer,int max_len)
{
    int i = 0;
    char c = '\0';
    int n;

    while(i<max_len-1)
    {
        n = recv(socket_fd,&c,1,0);

        if(n>0)
        {
            if(c=='\n') break;

            if(c!='\r')
            {
                buffer[i] = c;
                i++;
            }
        }
        else if(n == 0)
        {
            break;
        }
        else
        {
            return -1;
        }
    }
    buffer[i] = '\0';
    return i;
}

int main(int argc,char* argv)
{
    int port = atoi(argv[1]);
    char* ip_address = argv[2];
    int fd;
    struct sockaddr_in address;
    fd = socket(AF_INET,SOCK_STREAM,0);

    if(fd <0 ) {perror("Socket Failure"); exit(1);}

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET,ip_address,&(address.sin_addr));

    if(connect(fd,(sockaddr *)&address,sizeof(address))<0){perror"connection failed";exit(1);}
    char buffer[BUFSIZE];
    memset(buf,0,sizeof(buf));

    int bytes_received = recv_line(fd,buffer,sizeof(buffer));
    return 0;
}