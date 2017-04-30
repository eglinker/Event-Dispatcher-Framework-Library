/****************************************************************
UDPEvents.c

This file is part of an event driven framwork developed for 
use in embedded systems by Erich Glinker. It may be used for
free under the terms of the licence below:

Copyright © 2013 by Erich Glinker.  
All Rights Reserved Worldwide.

By using this source code you agree to the following terms:

a)	You are permitted to use this source code for personal 
	and/or commercial purposes.
b)	You may redistribute this text as part of a project 
	ONLY IF this legal agreement remains, and any 
	changes/additions to the text or documentation are 
	clearly marked.
c)	This source code is provided "as is", with NO WARRANTY of 
	any kind, express or implied, not even "fitness for 
	a particular purpose".
d)	Erich Glinker shall not be held liable under any 
	circumstances for any damage resulting from the use 
	or misuse of this source code.
e)	In jurisdictions where any part of this legal agreement 
	is not legal or not enforceable by law, part 'e' shall 
	remain upheld, and you are expressly forbidden to use 
	this text for any purpose.

****************************************************************/




#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<fcntl.h>
#include"ef.h"
 
#define BUFLEN 512  //Max length of serverBuffer
//#define PORT 8888   //The port on which to listen for incoming data
 
struct sockaddr_in si_me, si_other;

int s, i, slen, recv_len;
char serverBuf[BUFLEN];

struct sockaddr_in si_other2;
int s2, i2, slen2;
char buf2[BUFLEN];
char message2[BUFLEN];

void die(char *s);

void	UDPEventsInit(int serverPort)
{
	int flags; 
	
	slen = sizeof(si_other);
	//create a UDP socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
        	die("socket");
	}

	// Make sure that recieve is non blocking
	flags = fcntl(s, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(s, F_SETFL, flags);

	// zero out the structure
	memset((char *) &si_me, 0, sizeof(si_me));
     
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(serverPort);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
	//bind socket to port
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		die("bind");
    	}

	
	slen2 = sizeof(si_other2);
	if ( (s2=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    	{
        	die("socket2");
    	}
 
    	//memset((char *) &si_other2, 0, sizeof(si_other2));
    	si_other2.sin_family = AF_INET;


	return;
}

int	serverRecieveEvents()
{
	
	strcpy(serverBuf,"");
	// zero out the structure
	memset((char *) serverBuf, 0, BUFLEN);
     
         
	//try to receive some data, this is a non -blocking call
	if ((recv_len = recvfrom(s, serverBuf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
	{
		//die("recvfrom()");
	}
         
	if(strlen(serverBuf)>0)
	{
		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n" , serverBuf);

		eventQueueEnqueueString(serverBuf);
	}

	return(1);
}


int	clientSendEvents(char *destination, int destinationPort, char *eventString)
{
	memset((char *) &si_other2, 0, sizeof(si_other2));
	si_other2.sin_port = htons(destinationPort);

  	if (inet_aton(destination , &si_other2.sin_addr) == 0) 
    	{
        	fprintf(stderr, "inet_aton() failed\n");
        	exit(1);
    	}
	
	//send the message
        if (sendto(s2, eventString, strlen(eventString)+1 , 0 , (struct sockaddr *) &si_other2, slen2)==-1)
        {
            die("sendto()");
        }

	return(1);
}



void die(char *s)
{
    perror(s);
    exit(1);
}
 
