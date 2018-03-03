#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
	int count, sockid;
	char buff[50];
	socklen_t addr_size;
	
	if(strlen(argv[2]) > 32){
		printf("Error: Message out of range\n");
		exit(0);
	}

	sockid = socket(PF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(argv[1]);
	serv.sin_port = htons(4440);
	addr_size = sizeof(serv);

	sendto(sockid, argv[2], 50, 0, (struct sockaddr *)&serv, sizeof(serv));
	
	printf("Client: %s\n", argv[2]);

	count = recvfrom(sockid, buff, 50, 0, NULL, NULL);

	printf("Client: Recieved from server: %s\n", buff);
	return 0;
}
