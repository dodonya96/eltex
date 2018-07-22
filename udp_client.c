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
    int udp;
    struct sockaddr_in addr;
    
    udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(udp < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5455); 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    mess = sendto (udp, buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));    
    printf("%s\n", buf);
    if(mess < 0)
    {
        perror("send");
        exit(3);
    }
    mess = recvfrom(udp, buf, sizeof(buf), 0, NULL, NULL);
    if(mess < 0)
    {
        perror("recv");
        exit(3);
    }
    printf("%s\n", buf);
    close(udp);
    return 0;
}
