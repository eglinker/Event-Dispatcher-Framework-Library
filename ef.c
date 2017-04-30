/****************************************************************
ef.c

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


#include <string.h>
#include "ef.h"


int 	eventHandlerCount = 0;	/* Number of event handlers added. */
char	eventHandlerEventString[EVENTHANDLERMAX][EVENTSIZEMAX]; /* Name of event to match hendler. */
void 	(*ehPointers[EVENTHANDLERMAX])();	/* Pointers to event handlers. */

char	auxEventString[EVENTSIZEMAX];

char	eventQueue[EVENTQUEUEMAX][EVENTSIZEMAX];  /* Buffer of event queue. */
int	eventQueueTail;
int	eventQueueHead;




/* Clears all of the event handlers and their strings */
int	eventHandlerFrameworkInit()
{
	int i,j;

	for(i=0; i<EVENTHANDLERMAX;i++)
	{
		ehPointers[i] = 0;
		for(j=0; j<EVENTSIZEMAX; j++)
		{
			eventHandlerEventString[i][j] = 0;
		}
	}

	return(1);
}

/* Add event handlers to the dispatcher. */ 
int	addEventHandler(char  *eventName, void *handlerPtr)
{
	strcpy(eventHandlerEventString[eventHandlerCount],eventName);
	ehPointers[eventHandlerCount++] = handlerPtr;
	return(1);
}

/* Dispatch the event handlers when event are in the event queue. */
int	eventHandlerDispatcher()
{
	int i;
	char tempString[EVENTSIZEMAX];
	char *eventToken;

	if(!eventQueueEmpty())
	{
		eventQueueDequeue(tempString);
		strcpy(auxEventString, tempString);
		eventToken = strtok(tempString,",");

		
		for(i=0; i<eventHandlerCount; i++)
		{

			if(strcmp(eventToken,eventHandlerEventString[i])==0)
			{
				if(ehPointers[i]!=0)
				{
					(*ehPointers[i])();
				}
			}
		}
	}
	else
	{
		strcpy(auxEventString, "");
	}

	return(1);
}



/* This function sets up the event queue. */
int	eventQueueInit()
{
	int i, j;

	eventQueueTail = 0;
	eventQueueHead = 0;

	for(i=0; i<EVENTQUEUEMAX; i++)
	{
		for(j=0; j<EVENTSIZEMAX;j++)
		{
			eventQueue[i][j]=0;
		}
	}

	return(1);
}

/* This function enters a event into the queue. */
int	eventQueueEnqueue(char *eventIn, int eventSize)
{
	int i;

	for(i=0; i<eventSize; i++)
	{
		eventQueue[eventQueueHead][i] = *(eventIn++);
	}
	
	eventQueueHead++;
	if(eventQueueHead==EVENTQUEUEMAX)
	{
		eventQueueHead = 0;
	}

	return(0);
}


/* This function enters a event string into the queue. */
int	eventQueueEnqueueString(char *eventIn)
{
	eventQueueEnqueue(eventIn, strlen(eventIn)+1);
	return(0);
}




/* This function removes a function from the event queue. */
int	eventQueueDequeue(char *eventOut)
{
	int i;

	for(i=0; i<EVENTSIZEMAX; i++)
	{
		*(eventOut++)=eventQueue[eventQueueTail][i];
		eventQueue[eventQueueTail][i] = 0;

	}


	eventQueueTail++;
	if(eventQueueTail==EVENTQUEUEMAX)
	{
		eventQueueTail = 0;
	}

	return(1);
}

/* test to see if the event queue is empty. */
int	eventQueueEmpty()
{
	if(eventQueueTail==eventQueueHead)
	{
		return(1);
	}

	return(0);
}

