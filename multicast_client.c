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
int sr;
int main()
{
    int udp = 0;
    struct sockaddr_in addr;
 
    udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(udp < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777); 
    addr.sin_addr.s_addr = inet_addr("224.0.0.15");

    sr = sendto (udp, buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));    
    printf("%s\n", buf);
    if(sr < 0)
    {
        perror("send");
        exit(5);
    }
    close(udp);
    return 0;
}

