#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

char buf[] = "Hello there!\n";
int mess;
int main()
{
    int sock;
    struct sockaddr_in addr;
    
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5455); 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    mess = sendto (sock, buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));    
    printf("%s\n", buf);
    if(mess < 0)
    {
        perror("send");
        exit(3);
    }
    mess = recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL);
    if(mess < 0)
    {
        perror("recv");
        exit(3);
    }
    printf("%s\n", buf);
    close(sock);
    return 0;
}
