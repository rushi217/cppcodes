#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

	int sock, new_sock, pid, port = 9014;
	
	char *recv_buf = (char *)malloc(2000);
	struct sockaddr_in serv_addr;
	socklen_t addr_size;
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("cannot create socket");
		return 0;
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(port);
	addr_size = sizeof(serv_addr);
	
	if((bind(sock, (struct sockaddr*)&serv_addr, addr_size)) < 0){
		perror("bind failed");
		return 0;
	}
	
	printf("waiting at %d\n", port);
	
	if(listen(sock, 5) < 0){
		perror("listen failed");
		return 0;
	}
	
	while(1){
	
		if((new_sock = accept(sock, (struct sockaddr*)&serv_addr, &addr_size)) < 0){
			perror("accept failed");
			return 0;
		}
		
		if((pid = fork()) == 0){
			close(sock);
			char *tokens[3];
			printf("Accepted\n");
			
			recv(new_sock, recv_buf, 44, 0);
			//printf("Recieved: %s\n", recv_buf);
			tokens[0] = strtok(recv_buf, "/");
			//printf("%s",tokens[0]);
			if(strncmp(tokens[0], "GET", 3) == 0){
			
				tokens[1] = strtok(NULL, " ");
				tokens[2] = strtok(NULL, "\r\n");
				//printf("%s and %s\n",tokens[1], tokens[2]);
				char *send_buf = NULL;
				size_t size;
				
				FILE *fp = fopen(tokens[1], "r");
				printf("%s file opened\n",tokens[1]);
				
				fseek(fp, 0, SEEK_END);
				size = ftell(fp);
				
				rewind(fp);
				
				send_buf = (char *)malloc((size + 1)*sizeof(*send_buf));
				
				fread(send_buf, size, 1, fp);
				send_buf[size] = '\0';
				
				int bytes = send(new_sock, send_buf, strlen(send_buf), 0);
				printf("Sent data %d\n",bytes);
				
				char *end = "\0";
				send(new_sock, end, 1, 0);
				printf("End sent\n");
				//write(new_sock, send_buf, strlen(send_buf));
			}
			else if(strncmp(tokens[0], "PUT", 3) == 0){
				tokens[1] = strtok(NULL, " ");
				tokens[2] = strtok(NULL, "\r\n");
				//printf("%s and %s\n",tokens[1], tokens[2]);
				
				char *file_buf = (char *)malloc(99999);
				int bytes = recv(new_sock, file_buf, 99999, 0);
				printf("Recieved: %d\n", bytes);
				
				//printf("Data recieved\n");
				
				FILE *fp = fopen("put.html", "w");
				//while(recv(sock, file_buf, 99999, 0) > 0){
				int results = fputs(file_buf, fp);
		
				if (results == EOF) {
					// Failed to write do error code here.
					printf("Writing failed");
				}
				printf("File written\n");
				//printf("Recieved:\n%s\n", recv_buf);
				//}
				fclose(fp);
				printf("File saved and closed\n");
				
			}
			else{
				printf("Wrong format of get request\n");
			}
			
			
			close(new_sock);
			printf("closed socket\n");
			new_sock = -1;
			exit(0);
		}
		
	}	
	
}
