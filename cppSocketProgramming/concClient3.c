#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctype.h>
	
	

int main(int argv, char *argc[])
{
	
    int sockfd, n;
    struct sockaddr_in ser_addr;
    char buffer[100], server_reply[100];
    int ans;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    int portno = atoi(argc[2]);
    
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(argc[1]);
    ser_addr.sin_port = htons(portno);
    
    connect(sockfd,(struct sockaddr *) &ser_addr,sizeof(ser_addr));
    
    printf("Connected...\n");
    printf("TCP Client connected to %s on port %d\n",argc[1], portno);
    
    while(1)
     {
     	 printf("\n\nEnter the expression in the format as given below\noperand1 operator operand2\nTo quit, enter -1\n");
         scanf("%s",&buffer);
         if(strcmp(buffer,"-1") == 0)
         {
         	printf("Bye!\n");
         	break;
         }
         
        send(sockfd , buffer , 100 , 0) ;
        
        recv(sockfd , &ans , sizeof(ans) , 0) ;
        
        printf("ANS : %s = %d\n", buffer, ans);
     } 
  
    close(sockfd);
    return 0;
}

