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
    char buf[1024];
    socklen_t size_addr;
    size_addr = sizeof(addr_save);
    
    udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(udp < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5455);
    addr.sin_addr.s_addr = inet_addr("127.0.0.255"); 

    if(bind(udp, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
	while(1)
    {
        recvfrom(udp, buf, sizeof(buf), 0, (struct sockaddr *)&addr_save, &size_addr);
	printf("%s\n", buf);
	
    }
    close(udp);
    return 0;
}
