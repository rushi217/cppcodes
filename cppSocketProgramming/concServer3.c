#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argv, char *argc[])
{
     int sockfd, newsockfd;
     pid_t pid;
     socklen_t clilen;
     char buffer[100];
     
     struct sockaddr_in ser_addr, cli_addr;
     
     int n, k;
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
     int portno = atoi(argc[2]);
     
     ser_addr.sin_family = AF_INET;
     ser_addr.sin_addr.s_addr = inet_addr(argc[1]);
     ser_addr.sin_port = htons(portno);
     
     bind(sockfd, (struct sockaddr *) &ser_addr, sizeof(ser_addr));
     
     listen(sockfd, 5) ;
     
	 printf("Server listening on port %d\n", portno);
	 
	 clilen = sizeof(cli_addr);
	//printf("working till here\n");
	 
	 
	 while(1)
	 {
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     
    if((pid = fork()) == 0){
    
    	
    	close(sockfd);
     char str[100];
     
     
     
     int read_size;
       
     while(read_size = recv(newsockfd , buffer , 100 , 0) > 0 )
     {
     	printf("\nReceived from client : %s\n",buffer);
     	int i, j = 0, num[2] = {0,0};
     	int len = strlen(buffer);
     	int temp,ans;
     	char op;
     	int flag[2] = {0, 0};
     	for(i = 0 ; i < len ; i++)
     	{
     		if(i == 0 && buffer[i] == '-')
     		{
     			flag[j] = 1;
     			i++;
     		}
     		if(buffer[i] >= 48 && buffer[i] <= 57)
     		{
     			temp = buffer[i];
     			num[j] = num[j]*10 + (temp-48);
			}
			else
			{
				op = buffer[i];
				j++;
				if(buffer[i+1] == '-')
				{
					flag[j] = 1;
					i++;
				}
			}//printf("%d\n",num[j]);
     	}
     	if(flag[0] == 1)
     		num[0] = num[0]*-1;
     		
     	if(flag[1] == 1)
     		num[1] = num[1]*-1;
     	//printf("%d\t%d\n",num[0],num[1]);
     	switch(op)
     	{
     		case '+':
     			ans = num[0] + num[1];
     			break;
     		case '-':
     			ans = num[0] -num[1];
     			break;
     		case '*':
     			ans = num[0]*num[1];
     			break;
     		case '/':
     			ans = num[0]/num[1];
     			break;
        	case '^':
        		ans = 1;
        		for(k = 1 ; k <= num[1]; k++)
     				ans = ans * num[0];
     			break;
     	}
     	
     	printf("Sending to client : %d\n",ans);
       	//Send the message back to client
       	send(newsockfd , &ans , sizeof(ans), 0);
       
    }
    
    if(read_size == 0)
    	printf("\nClient closed connection\n");
    else if(read_size == -1)
    {
       	perror("recv failed");
       	exit(0);
    }
    }
    }
	close(newsockfd);
	close(sockfd);
    return 0;
}     
