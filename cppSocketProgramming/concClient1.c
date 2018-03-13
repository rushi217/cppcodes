#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>


int main()
{
    int sockfd, portno, n;
    struct sockaddr_in ser_addr;

    char buffer[2000],server_reply[2000];
    
    portno = 11009;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ser_addr.sin_port = htons(portno);
    
    connect(sockfd,(struct sockaddr *) &ser_addr,sizeof(ser_addr));
     printf("Connected...\n");
     
     while(1)
     {
     	 printf("\n\nEnter a message : ");
         scanf("%s",&buffer);
         
        //Send some data
        send(sockfd , buffer , 2000, 0);
         
        //Receive a reply from the server
        recv(sockfd , server_reply , 2000 , 0);
        
        printf("Sever reply : %s", server_reply);
     }
    
    close(sockfd);
    return 0;
}

