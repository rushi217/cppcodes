#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
	int count, sockid;
	char buff[100];
	sockid = socket(PF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(8080);
	bind(sockid, (struct sockaddr *)&serv, sizeof(serv));
	count = recvfrom(sockid, (void *)&buff, sizeof(buff), 0, NULL, NULL);
	printf("recieved %d bytes", count);
	return 0;
}
