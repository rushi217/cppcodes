#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
	int count, sockid;
	char buff[50];
	socklen_t addr_size;

	sockid = socket(PF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in serv, client;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("172.31.92.75");
	serv.sin_port = htons(4440);
	addr_size = sizeof(serv);
	
	printf("Server started... Waiting for connection...\n");

	bind(sockid, (struct sockaddr *)&serv, sizeof(serv));

	count = recvfrom(sockid, buff, 50, 0, (struct sockaddr *)&client, &addr_size);

	printf("Server: recieved %s\n", buff);

	sendto(sockid, buff, strlen(buff), 0, (struct sockaddr *)&client, addr_size);
	
	printf("Server: sent %s\n", buff);
	return 0;
}
