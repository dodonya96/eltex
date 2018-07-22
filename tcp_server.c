#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int tcp, cd;
    struct sockaddr_in addr;
    char buf[1024];
    int mess;

    tcp = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5454);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(tcp, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(tcp, 1);
    
    while(1)
    {
        cd = accept(tcp, NULL, NULL);
        if(cd < 0)
        {
            perror("accept");
            exit(3);
        }

        while(1)
        {
            mess = recv(cd, buf, 1024, 0);
            if(mess <= 0) break;
	    printf("%s\n",buf);
            send(cd, buf, mess, 0);
        }
    
        close(cd);
    }
    close(tcp);
    return 0;
}

