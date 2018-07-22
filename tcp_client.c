#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

char buf[] = "Hello there!\n";

int main()
{
    int tcp;
    struct sockaddr_in addr;

    tcp = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5454); 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(tcp, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    send(tcp, buf, sizeof(buf), 0);
    recv(tcp, buf, sizeof(buf), 0);   
    printf("%s\n", buf);
    
    close(tcp);
    return 0;
}

