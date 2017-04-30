/****************************************************************
main.c

This file is part of an event dispatcher framwork developed for 
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


 
#include <stdio.h>
#include <string.h>
#include "ef.h"

void	testeh1();
void	testeh2();

int	main()
{
	char eventMesageString[EVENTSIZEMAX];

	/* Initialize event queue and event dispatcher. */
	eventQueueInit();
	eventHandlerFrameworkInit();

	/* Add event handler / event mesage string pairs. */
	addEventHandler("HELLO", testeh1);
	addEventHandler("BYE", testeh2);

	while(1)
	{	/* Enter an event mesage string at the keyboard. */
		printf("Type in HELLO or BYE.\n");
		scanf("%s", eventMesageString);		
		
		/* Enqueue the event nesage string. */
		eventQueueEnqueueString(eventMesageString);
		
		/* Keep looping and dispatching events untill */
		/* event queue is empty. */
		while(!eventQueueEmpty())
		{
			eventHandlerDispatcher();
		}
	}
	return(1);
}

void	testeh1() /* Event handler that responds to HELLO. */
{
	printf("Hi buddy!\n");
	return;
}

void	testeh2() /* Event handler that responds to BYE. */
{
	printf("By buddy!\n");
	return;
}

