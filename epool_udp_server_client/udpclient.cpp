#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include<stdlib.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>


#define BUFFSIZE 5096 
#define MAX_LEN 100000

int sendlen, receivelen;
int received = 0, i,count, rcvCnt=0, sentCnt=0;
unsigned char buffer[BUFFSIZE];
struct sockaddr_in receivesocket;
struct sockaddr_in sendsocket;
int sock;
unsigned int ch;
unsigned int noOfTimes;
    
int sendUDPData();   
    
int main(int argc, char *argv[]) {
    
    int ret = 0;
  int optval = 1;

    /* Create the UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket");
        return -1;
    }

    /* my address */
    memset(&receivesocket, 0, sizeof(receivesocket)); 
    receivesocket.sin_family = AF_INET; 
    receivesocket.sin_addr.s_addr = htonl(INADDR_ANY);
    receivesocket.sin_port = htons(22905);

    receivelen = sizeof(receivesocket);

 if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))== -1)
  {
     perror("setsockopt Fail\n");
     return -1;
  }
  if (bind(sock, (struct sockaddr *) &receivesocket, receivelen) < 0) 
    {
        perror("bind");
        return -1;       
    }  
    /* kernel address */
    memset(&sendsocket, 0, sizeof(sendsocket));
    sendsocket.sin_family = AF_INET;
    sendsocket.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendsocket.sin_port = htons(22905);

   do
    {
       printf("\n");
       printf(" Enter your choice:\t");
       printf(" 1. Send UDP Data \n");
       printf(" 2. exit \n");
       scanf("%d", &ch);
       printf("\n");

       switch(ch)
       {

           case 1:
                   printf("Enter the Length of the Payload \n");
                   scanf("%d", &sendlen);
                   printf("Enter How many times you want to send data \n");
                   scanf("%d", &noOfTimes);
                   sendUDPData();
                   break;

           default:
                  printf("Invalid Choice\n");
                  break;
       }
    }while(ch!=2);
return 0;
}
int sendUDPData()
{
    int count=0;
        memset(buffer, 0x31, sendlen);
        
        for(count=0; count< noOfTimes;  count++)
        {
       if (sendto(sock, buffer, sendlen, 0, (struct sockaddr *) &sendsocket, 
                        sizeof(sendsocket)) != sendlen)       
       {
        perror("sendto");
        return -1;
       }

    printf("\n");
    }
    return 0;
}
