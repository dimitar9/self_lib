#include <stdio.h>          // for printf() and fprintf() 
#include <sys/socket.h>     // for socket(), bind(), and connect() 
#include <arpa/inet.h>      // for sockaddr_in and inet_ntoa() 
#include <stdlib.h>         // for atoi() and exit() 
#include <string.h>         // for memset() 
#include <unistd.h>         // for close() 
#include <fcntl.h>          // for fcntl() 
#include <errno.h>
#include <sys/epoll.h> 

#define MAX_EVENTS 100

#define BUFFSIZE 5096

unsigned char buf[BUFFSIZE];

/*
 * Dump Data
 */
void dumpData(unsigned char *data,  unsigned int len)
{
  unsigned int uIndx;

  if(data)
    {
      for(uIndx=0; uIndx<len; ++uIndx)
        {
          if(uIndx%32 == 0)
            {
              printf("\n%4d:", uIndx);
            }
          if(uIndx%4 == 0)
            {
              printf(" ");
            }
          printf("%02x", data[uIndx]);
        }
    }
  printf(" Length of Bytes: %d\n", len);
  printf("\n");
}


/*
 * make_socket_non_blocking :
 *   This Function makes socket as Non blocking
 */
static int make_socket_non_blocking(int sockFd)
{
  int getFlag, setFlag;
  
  getFlag = fcntl(sockFd, F_GETFL, 0);
  
  if(getFlag == -1)
  {
    perror("fnctl");
    return -1;
  }
  
  /* Set the Flag as Non Blocking Socket */ 
  getFlag |= O_NONBLOCK;
  
  setFlag = fcntl(sockFd, F_GETFL, getFlag);
  
  if(setFlag == -1)
  {
    perror("fnctl");
    return -1;
  }
  
  return 0;
}

/*
 *  Main Routine
 */
int main()
{
  int i, length, receivelen;

  /* Socket Parameters */
  int sockFd;
  int optval = 1;   // Socket Option Always = 1

  /* Server Address */
  struct sockaddr_in serverAddr, receivesocket;

  /* Epoll File Descriptor */
  int epollFd;       

  /* EPOLL Event structures */
  struct epoll_event  ev;                   
  struct epoll_event  events[MAX_EVENTS];                
  int numEvents;     
              
  int ctlFd;  
  // Step 1: First Create UDP Socket  
  
  /* Create UDP socket 
   * socket(protocol_family, sock_type, IPPROTO_UDP); 
   */
  sockFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  /* Check socket is successful or not */
  if (sockFd == -1)
  {
    perror(" Create SockFd Fail \n");
    return -1;
  }

  // Step 2: Make Socket as Non Blocking Socket.
  //         To handle multiple clients Asychronously, required to 
  //         configure socket as Non Blocking socket 

  /* Make Socket as Non Blocking Socket */
  make_socket_non_blocking(sockFd);

  // Step 3: Set socket options
  //    One can set different sock Options as RE-USE ADDR, 
  //    BROADCAST etc.
  
  /*  In this Program, the socket is set to RE-USE ADDR
   *  So this gives flexibilty to other sockets to BIND to the 
      same port Num */ 

  if(setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))== -1)
  {
     perror("setsockopt Fail\n");
     return -1;
  }

  // Step 4: Bind to the Recieve socket 
  /* Bind to its own port Num  ( Listen on Port Number) */
   
  /* Setup the addresses */
  
   /* my address or Parameters
     ( These are required for Binding the Port and IP Address )
      Bind to my own port and Address */
  memset(&receivesocket, 0, sizeof(receivesocket));
  receivesocket.sin_family = AF_INET;
  receivesocket.sin_addr.s_addr = htonl(INADDR_ANY);
  receivesocket.sin_port = htons(2905);

  receivelen = sizeof(receivesocket);

  /* Bind the my Socket */
  if (bind(sockFd, (struct sockaddr *) &receivesocket, receivelen) < 0)
  {
    perror("bind");
    return -1;
  }

  // EPOLL Implementation Starts 
  // Step 5: Create Epoll Instance
             /* paramater is Optional */
  
  epollFd = epoll_create(6);

  if(epollFd == -1)
  {
     perror("epoll_create");
     return -1;
  }

  /* Add the udp Sock File Descriptor to Epoll Instance */
  ev.data.fd = sockFd; 
  
  /* Events are Read Only and Edge-Triggered */
  ev.events = EPOLLIN | EPOLLET;

  
  // Step 6: control interface for an epoll descriptor
  /* EPOLL_CTL_ADD
      Register the target file descriptor fd on the epoll instance
      referred to by the file descriptor epfd and
      associate the event event with the internal file linked to fd.
  */

  /* Add the sock Fd to the EPOLL */
  ctlFd  = epoll_ctl (epollFd, EPOLL_CTL_ADD, sockFd, &ev);
  
  if (ctlFd == -1)
  {
    perror ("epoll_ctl");
    return -1;
  }

 // Step 7: Start the Event Loop using epoll_wait() in while Loop.

 /* Event Loop */
 while(1)
 {
     /*  Wait for events.
      *  int epoll_wait(int epfd, struct epoll_event *events, int
      *  maxevents, int timeout);
      *  Specifying a timeout of -1 makes epoll_wait() wait
      *  indefinitely.
      */
     
     /* Epoll Wait Indefently since Time Out is -1 */
     numEvents = epoll_wait(epollFd, events, MAX_EVENTS, -1);

     for (i = 0; i < numEvents; i++)
     {
       if ((events[i].events & EPOLLERR) ||
           (events[i].events & EPOLLHUP) ||
           (!(events[i].events & EPOLLIN)))
        {
           /* An error has occured on this fd, or  the socket is not
            * ready for reading (why were we notified then?) 
            */
           fprintf (stderr, "epoll error\n");
           close (events[i].data.fd);
           continue;
        }
       /* We have data on the fd waiting to be read. Read and
        * display it. We must read whatever data is available
        * completely, as we are running in edge-triggered mode
        * and won't get a notification again for the same data.
        */
       else if ( (events[i].events & EPOLLIN) && 
           (sockFd == events[i].data.fd) )
       {
         while (1)
         {

           memset(buf, 0, BUFFSIZE);
           /* Recieve the Data from Other system */
           if ((length = recvfrom(sockFd, buf, BUFFSIZE, 0, NULL, NULL)) < 0)
            {
                perror("recvfrom");
                return -1;
            }

           else if(length == 0)
             {
               printf( " The Return Value is 0\n");
               break;
             }
           else
             {
               /* Print The data */
               printf("Recvd Byte length : %d",  length);
               dumpData(buf, length);
             }
          }
       }
     }
  }

close( sockFd );
close( epollFd );
return 0;
}
