#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<time.h>

int main(){
	int count, sockid;
	char buff[50];
	socklen_t addr_size;

	sockid = socket(PF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in serv, client;

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(4444);
	addr_size = sizeof(serv);

	bind(sockid, (struct sockaddr *)&serv, addr_size);

	count = recvfrom(sockid, buff, 50, 0, (struct sockaddr *)&client, &addr_size);

	printf("Server: Client asks %s\n", buff);
	
	time_t servtime;
	servtime = time(NULL);
	//char sendbuf[50] = ctime(&servtime);

	sendto(sockid, ctime(&servtime), 30, 0, (struct sockaddr *)&client, addr_size);

	return 0;
}
