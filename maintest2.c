/****************************************************************
main.c

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

#include <stdio.h>
#include <string.h>
#include "ef.h"

void	GPIO5RisingEventHandler();

int	main()
{
	/* Event dispatcher init */
	eventQueueInit();
	eventHandlerFrameworkInit();

	GPIOInit();  /* GPIO init */

	/* Initalize GPIO6 as output and switch to off. */
	GPIOOutputMode(6);    
	GPIOWrite(6, 0);

	GPIOInputMode(5);  /* Initalize GPIO5 as input. */  

	/* This installs the handler that flicks GPIO ON or OFF */
	/* when ever the GPIO 5 rising event occures. */
	addEventHandler("GPIORISE5", GPIO5RisingEventHandler);

	while(1)
	{
		/* Check to see if on of the initialized GPIO pins */ 
		/* change state, then automatricaly adds a GPIO rising */
		/* or GPIO falling event message to the event queue occures. */ 
		GPIOEdgeEventDetect();

		/* Keep looping and dispatching events if event queu */
		/* is not empty.  */
		while(!eventQueueEmpty()) 
		{
			eventHandlerDispatcher();
			printf("Event log: %s\n", auxEventString);
			fflush(stdout);
		}
		delay(10);
	}

	return(1);
}

/* This is the event handler that flips the state of GPIO6 */
/* when ever the GPIO5 experiences a rising edge event. */
void	GPIO5RisingEventHandler()
{
	if(GPIORead(6))
	{
		GPIOWrite(6, 0);
	}
	else
	{
		GPIOWrite(6, 1);
	}
	return;
}

