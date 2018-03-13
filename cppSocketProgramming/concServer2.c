#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <pthread.h>

void *reverse_string(void *newsock){
	int read_size;
	int newsockfd = *(int *)newsock;
	char word[2000];
	char buffer[2000];
		
	while(read_size = recv(newsockfd , buffer , 2000 , 0))
	{
		printf("\nReceived : %s\n",buffer);
				
		int i, j = 0;
			
		for (i = strlen(buffer) - 1; i >= 0; i--, j++) {
			word[j] = buffer[i];
		}
		word[j] = '\0';
			
		printf("Sent to client : %s\n",word);
				//Send the message back to client
	   	send(newsockfd , word , 2000, 0);
			   
	}
	if(read_size == 0){
		printf("Xlient dead\n");
		close(newsockfd);
		return 0;
	}
}

int main(){

     int sockfd, newsockfd, portno;
     
     //pid_t pid;
     pthread_t t[10];
     
     socklen_t clientlen;
     
     struct sockaddr_in ser_addr, cli_addr;
     
     int n, i;
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
        
     portno = 11015;
     
     ser_addr.sin_family = AF_INET;
     ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
     ser_addr.sin_port = htons(portno);
     
    bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    
	printf("Server started... Waiting for connection...\n");
	
	listen(sockfd,5);
	
    clientlen = sizeof(cli_addr);
    
    while(1){
    
    	i = -1;
    	
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clientlen);
		printf("New Xlient Connected\n");
		i++;
		
			
		pthread_create(&t[i], NULL, reverse_string, (void *)&newsockfd);
		
		
		
	}
	close(newsockfd);
	close(sockfd);
    return 0;
}
