#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int udp = 0, tcp = 0, fd_tcp = 0;
    struct sockaddr_in addr;
    char buf[1024];

    udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(udp < 0)
    {
        perror("socket");
        exit(1);
    }
 
    tcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(tcp < 0)
    {
        perror("socket");
        exit(2);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5455);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    
    if(bind(udp, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(3);
    }
 
	addr.sin_port = htons(5454);
 
    if(bind(tcp, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(4);
    }   
        
    int fd1;
    if (tcp > udp)
		fd1 = tcp;
    else
		fd1 = udp;
	
    listen (tcp, 10);
    
    while (1) {
		fd_set read;
		FD_ZERO (&read);
		FD_SET (tcp, &read);
		FD_SET (udp, &read);
		
		struct timeval tv;
		tv.tv_sec = 10;
		tv.tv_usec = 0;
		
		select (fd1 + 1, &read, NULL, NULL, &tv);

		if (FD_ISSET (tcp, &read)) {
	    	fd_tcp = accept (tcp, NULL, NULL);
	    		if(fd_tcp < 0) {
          			perror("accept");
        			exit(5);
	        	}
		    recv (fd_tcp, buf, sizeof(buf), 0);
		    printf ("%s\n", buf);
		    close (fd_tcp);
		}

		if (FD_ISSET (udp, &read)) {
		    recvfrom (udp, buf, sizeof(buf), 0, NULL, NULL);
		    printf ("%s\n", buf);
		}
    }
    close (tcp);
    close (udp);
    return 0;
}
