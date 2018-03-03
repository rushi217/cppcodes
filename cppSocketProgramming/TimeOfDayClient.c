#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int count, sockid;
	char buff[50] = "What's the Time";
	socklen_t addr_size;

	sockid = socket(PF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(argv[1]);
	serv.sin_port = htons(atoi(argv[2]));
	addr_size = sizeof(serv);

	sendto(sockid, buff, strlen(buff) + 1, 0, (struct sockaddr *)&serv, sizeof(serv));

	count = recvfrom(sockid, buff, 50, 0, NULL, NULL);

	printf("Client: Server says time is %s\n", buff);
	return 0;
}
