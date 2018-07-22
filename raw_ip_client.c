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
#include <netinet/ip.h>

char buf[1024];
int sr;

int main()
{
    int udp = 0;
    struct sockaddr_in addr;
	struct udphdr udp_str;
	struct iphdr ip_str;
    udp = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(udp < 0)
    {
        perror("socket");
        exit(1);
    }
    
    u_int yes = 1;
	if (setsockopt(udp, IPPROTO_IP, IP_HDRINCL, &yes, sizeof(yes)) < 0){
		perror("setsockopt");
		exit(2);
	}
	
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5455); 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	udp_str.source = htons(25455);
	udp_str.dest = htons(5455);
	udp_str.len = htons(sizeof(buf) - sizeof(ip_str));
	udp_str.check = 0;
	
	ip_str.version = 4;
	ip_str.ihl = 5;
	ip_str.tos = 0;
	ip_str.tot_len = htons(sizeof(buf));
	ip_str.id = htons(7777);
	ip_str.frag_off = 0;
	ip_str.ttl = 15;
	ip_str.protocol = IPPROTO_UDP;
	ip_str.check = 0;
	ip_str.saddr = inet_addr("10.0.2.15");
	ip_str.daddr = inet_addr("127.0.0.1");
	memcpy(buf, &ip_str, sizeof(ip_str));
	memcpy(buf + sizeof(ip_str), &udp_str, sizeof(udp_str));	
	strcpy(buf + sizeof(ip_str) + sizeof(udp_str), "Hello)");

    sr = sendto (udp, buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));    
    printf("%s\n", buf);
    if(sr < 0)
    {
        perror("send");
        exit(3);
    }
    while(1){
	    sr = recvfrom(udp, buf, sizeof(buf), 0, NULL, NULL);
	    if(sr < 0)
	    {
	        perror("recv");
	        exit(4);
	    }
	    printf("%s\n", buf + 28);
		if(strcmp(buf + 28,"Hi!") == 0)
			break;	
    }
    close(udp);
    return 0;
}

