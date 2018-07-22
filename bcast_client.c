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
    int broadcast = 1;
    
    udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(udp < 0)
    {
        perror("socket");
        exit(1);
    }

    if(setsockopt(udp, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
    {
        perror("broadcast");
        close(udp);
        exit(2);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5455); 
    addr.sin_addr.s_addr = inet_addr("127.0.0.255");
	
    sr = sendto (udp, buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));    
    printf("%s\n", buf);
    if(sr < 0)
    {
        perror("send");
        exit(3);
    }
    sr = recvfrom(udp, buf, sizeof(buf), 0, NULL, NULL);
    if(sr < 0)
    {
        perror("recv");
        exit(3);
    }
    printf("%s\n", buf);
    close(udp);
    return 0;
}

