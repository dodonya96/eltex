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
#include <netinet/udp.h>

struct udphdr udp_str;
char buf[64];
char str[1024];
int sr;

int main()
{
    int raw = 0;
    struct sockaddr_in addr;

    raw = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(raw < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5455); 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	udp_str.source = htons(25455);
	udp_str.dest = htons(5455);
	udp_str.len = htons(sizeof(str));
	udp_str.check = 0;
	memcpy(str, &udp_str, sizeof(str));
	strcpy(buf + sizeof(udp_str), "Hello!");

    sr = sendto (raw, &str, sizeof(str), 0, (struct sockaddr*)&addr, sizeof(addr)); 
    if(sr < 0)
    {
        perror("send");
        exit(2);
    }
    while(1){
	    sr = recvfrom(raw, buf, sizeof(buf), 0, NULL, NULL);
	    if(sr < 0)
	    {
	        perror("recv");
	        exit(3);
	    }
	    printf("%s\n", buf + 28);
	    if(strcmp(buf + 28,"Hi!") == 0)
			break;	
    }
    close(raw);
    return 0;
}
