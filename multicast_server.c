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


int main()
{
    int udp = 0;
    struct sockaddr_in addr, addr_save;
    
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.15");
    mreq.imr_interface.s_addr = inet_addr("10.0.2.15"); 

    char buf[1024] = "Hello!";
    socklen_t size_addr;
    size_addr = sizeof(addr_save);

    udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(udp < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = inet_addr("224.0.0.15"); 

    if(bind(udp, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(4);
    }  
    
	if(setsockopt(udp, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("multicast");
        close(udp);
        exit(5);
    }
    
	while(1)
    {		
        recvfrom(udp, buf, sizeof(buf), 0, (struct sockaddr *)&addr_save, &size_addr);
	printf("%s\n", buf);
    }
    close(udp);
    return 0;
}
