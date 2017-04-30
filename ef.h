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


#define EVENTSIZEMAX	64	/* Maximum size of an event mesage. */
#define EVENTQUEUEMAX	1024	/* Maximum number events in event queue. */

#define EVENTHANDLERMAX 64	/* Maximum number of event handlers. */

extern char	auxEventString[EVENTSIZEMAX];

int	eventHandlerFrameworkInit();
int	addEventHandler(char  *eventName, void *handlerPtr); 
int	eventHandlerDispatcher();


int	eventQueueEnqueue(char *eventIn, int eventSize);
int	eventQueueEnqueueString(char *eventIn);
int	eventQueueDequeue(char *eventOut);
int	eventQueueInit();
int	eventQueueEmpty();







