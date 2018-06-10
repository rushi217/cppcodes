#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	int sock, rv;
	
	char *recv_buf = (char *)malloc(2000);
	struct sockaddr_in serv_addr;
	struct addrinfo hints, *servinfo, *p;
	//struct sockaddr serv_conn;
	socklen_t addr_size;
	
	hints.ai_family = AF_INET; // use AF_INET6 to force IPv6
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
		perror("resolution");
		exit(1);
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		printf("looping\n");
		if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
		    perror("socket");
		    continue;
		}

		if (connect(sock, p->ai_addr, p->ai_addrlen) == -1) {
		    perror("connect");
		    close(sock);
		    continue;
		}

		break; // if we get here, we must have connected successfully
	}

	if (p == NULL) {
		// looped off the end of the list with no connection
		fprintf(stderr, "failed to connect\n");
		exit(2);
	}

	/*Normal operation
	//sock = socket(AF_INET, SOCK_STREAM, 0);
	
	
	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//serv_addr.sin_port = htons(8096);
	//printf("%s\n",argv[1]);
	//printf("%d\n",atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	addr_size = sizeof(serv_addr);
	*/
	
	/*
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		perror("connect failed"); 
		return 0;
	}
	*/
	
	printf("Connected\n");
	
	//while(1){
	
		
		//char *send_buf = "GET /send.txt HTTP/1.0\r\n";
		char *send_buf = (char *)malloc(100);
		*send_buf = 0;
		//printf("%s and %s\n", argv[3], argv[4]);
		strcat(send_buf, argv[3]);
		strcat(send_buf, " /");
		strcat(send_buf, argv[4]);
		strcat(send_buf, " HTTP/1.0\r\n");
		strcat(send_buf, "Host: ");
		strcat(send_buf, argv[1]);
		strcat(send_buf, "\r\n\r\n");
		
		if(strcmp(argv[3], "GET") == 0){
			int getBytes = send(sock, send_buf, strlen(send_buf), 0);
			//printf("%s sent\n",send_buf);
			printf("GET sent %d\n",getBytes);
			//recv(sock, recv_buf, 99999, 0);
			FILE *fp = fopen("index.html", "w");
			printf("File opened\n");
			
			char *file_buf = (char *)malloc(9000);
			
			int bytes;
			
			//Successful Attempt using timeout
			struct timeval tv = {5, 2};
			setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
			
			while(bytes = (recv(sock, file_buf, 9000, 0)) > 0){
				int results = fputs(file_buf, fp);
					//free(file_buf);
				//file_buf = (char *)malloc(1000);
				if (results == EOF) {
					// Failed to write do error code here.
					printf("Writing failed");
				}
				printf("File written %d\n",bytes);
				
			}
			/*Failed Attempt
			while((bytes = recv(sock, file_buf, 1000, 0)) > 0 && file_buf[bytes - 1] != '\0'){
					int results = fputs(file_buf, fp);
					//free(file_buf);
					file_buf = (char *)malloc(1000);
					if (results == EOF) {
						// Failed to write do error code here.
						printf("Writing failed");
					}
					printf("File written %d\n",bytes);
					//printf("Recieved:\n%s\n", recv_buf);
			}
			
			fputs(file_buf, fp);
			*/
			fclose(fp);
			printf("File saved and closed\n");
			free(file_buf);
		
			//printf("Recieved:\n%s\n", recv_buf);
		}
		else if(strcmp(argv[3], "PUT") == 0){
			int putBytes = send(sock, send_buf, strlen(send_buf), 0);
			printf("PUT sent %d\n",putBytes);
			
			char *file_buf = NULL;
			size_t size;
			
			FILE *fp = fopen(argv[4], "r");
			
			fseek(fp, 0, SEEK_END);
			size = ftell(fp);
			
			rewind(fp);
			file_buf = (char *)malloc((size + 1) * (sizeof(*file_buf)));
			
			fread(file_buf, size, 1, fp);
			file_buf[size] = '\0';
			
			int bytes = send(sock, file_buf, strlen(file_buf), 0);
			printf("File sent %d\n",bytes);
			
			fclose(fp);
		}
	//}
}
