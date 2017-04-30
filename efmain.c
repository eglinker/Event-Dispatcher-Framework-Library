#include <stdio.h>
#include <string.h>

#define EVENTSIZEMAX	64	/* Maximum size of an event mesage. */
#define EVENTQUEUEMAX	1024	/* Maximum number events in event queue. */

#define EVENTHANDLERMAX 64	/* Maximum number of event handlers. */

int	eventHandlerInit();
int	addEventHandler(char  *eventName, void *handlerPtr); 
int	eventHandlerDispatcher();


int	eventQueueEnqueue(char *eventIn, int eventSize);
int	eventQueueDequeue(char *eventOut);
int	eventQueueInit();
int	eventQueueEmpty();


int 	eventHandlerCount = 0;	/* Number of event handlers added. */
char	eventHandlerEventString[EVENTHANDLERMAX][EVENTSIZEMAX]; /* Name of event to match hendler. */
void 	(*ehPointers[EVENTHANDLERMAX])();	/* Pointers to event handlers. */


char	eventQueue[EVENTQUEUEMAX][EVENTSIZEMAX];  /* Buffer of event queue. */
int	eventQueueTail;
int	eventQueueHead;


void	testeh1();
void	testeh2();
void	testeh3();
void	testeh4();




int	main()
{

	char tempString[EVENTSIZEMAX];

	printf("hello\n");
	eventQueueInit();

	printf("hello\n");

	eventQueueEnqueue("hello, this is #1.", strlen("hello, this is #1.")+1);
	eventQueueEnqueue("hello, this is #2.", strlen("hello, this is #2.")+1);
	eventQueueEnqueue("hello, this is #3.", strlen("hello, this is #3.")+1);

	while(!eventQueueEmpty())
	{
		eventQueueDequeue(tempString);
		puts(tempString);
	}

	eventHandlerInit();


	addEventHandler("EV01", testeh1);
	addEventHandler("EV01", testeh2);
	addEventHandler("EV01", testeh3);
	addEventHandler("EV02", testeh4);

	eventQueueEnqueue("EV01", strlen("EV01")+1);
	eventQueueEnqueue("EV02", strlen("EV02")+1);
	eventQueueEnqueue("EV01", strlen("EV01")+1);

	eventHandlerDispatcher();


	return(1);
}

void	testeh1()
{
	printf("test event handler 1\n");
	return;
}

void	testeh2()
{
	printf("test event handler 2\n");
	return;
}

void	testeh3()
{
	printf("test event handler 3\n");
	return;
}

void	testeh4()
{
	printf("test event handler 4\n");
	return;
}




/* Clears all of the event handlers and their strings */
int	eventHandlerInit()
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

	while(!eventQueueEmpty())
	{
		eventQueueDequeue(tempString);
		eventToken = strtok(tempString,",");

//		printf("hello %s \n",eventToken);
		
		for(i=0; i<eventHandlerCount; i++)
		{
//		printf("    %s \n",eventHandlerEventString[i]);

			if(strcmp(eventToken,eventHandlerEventString[i])==0)
			{
//				printf("          beep\n");
				if(ehPointers[i]!=0)
				{
					(*ehPointers[i])();
				}
			}
		}
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

