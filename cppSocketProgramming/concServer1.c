#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

int main(){

     int sockfd, newsockfd, portno;
     pid_t pid;
     socklen_t clientlen;
     char buffer[2000];
     struct sockaddr_in ser_addr, cli_addr;
     int n;
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
        
     portno = 11009;
     ser_addr.sin_family = AF_INET;
     ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
     ser_addr.sin_port = htons(portno);
     
    bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    
	printf("Server started... Waiting for connection...\n");
	
	listen(sockfd,5);
	
    clientlen = sizeof(cli_addr);
    while(1){
    
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clientlen);
		
		if((pid = fork()) == 0){
			close(sockfd);
			int read_size;  
			char word[2000];
		
			while(read_size = recv(newsockfd , buffer , 2000 , 0) > 0 )
			{
				if(read_size == 0){
					printf("\nClient disconnected\n");
					close(newsockfd);
					exit(0);
				}
			   
			   
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
		
			
		
		}
	}
	close(newsockfd);
	close(sockfd);
    return 0;
}
