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
#include "lcdwrapper.h"
#include "UDPEvents.h"

void itoa(int valueIn, char *string, int base);

void	testeh1();
void	testeh2();
void	testeh3();
void	testeh4();

void	GPIO5RisingEventHandler();
void	LEDOff();
void	LEDOn();
void	playMusic();
void	stopMusic();

int	main()
{

	char tempString[EVENTSIZEMAX];
	char testString[64];
	int i;

	printf("Event queue init\n");
	eventQueueInit();

	printf("GPIO init\n");
	GPIOInit();

	printf("Event dispatcher init.\n");
	eventHandlerFrameworkInit();

	printf("UDP Event init\n");
	UDPEventsInit(8888);

	clientSendEvents("127.0.0.1", 45000, "TESTEVENT");

	printf("LCD init\n");
	LCDWrapperInit();
	LCDWrapperClear();
	LCDWrapperPosition(0, 0);
	LCDWrapperPuts("LCD test");


	GPIOOutputMode(6);
	GPIOWrite(6, 0);


	GPIOOutputMode(12);
	GPIOInputMode(5);

	GPIOInputMode(4);
	GPIOInputMode(5);
	GPIOInputMode(6);
	GPIOInputMode(13);
	GPIOInputMode(14);

	GPIOInputMode(12);
	GPIOInputMode(18);
	GPIOInputMode(20);



	printf("Start event dispatcher test.\n");

	addEventHandler("EV01", testeh1);
	addEventHandler("EV01", testeh2);
	addEventHandler("EV01", testeh3);
	addEventHandler("EV02", testeh4);
	addEventHandler("GPIORISE5", GPIO5RisingEventHandler);
	addEventHandler("LED TOGGLE", GPIO5RisingEventHandler);
	addEventHandler("LED ON", LEDOn);
	addEventHandler("LED OFF", LEDOff);
	addEventHandler("PLAY MUSIC", playMusic);
	addEventHandler("STOP MUSIC", stopMusic);


	eventQueueEnqueueString("EV01,This is an argument");
	eventQueueEnqueueString("EV02");
	eventQueueEnqueueString("EV01");

	while(1)
	{
		GPIOEdgeEventDetect();

		serverRecieveEvents();

		while(!eventQueueEmpty())
		{
			eventHandlerDispatcher();
			printf("Event log: %s\n", auxEventString);
			fflush(stdout);
		}
		delay(10);
	}

	printf("End event dispatcher test.\n");

	return(1);
}

void	testeh1()
{
	printf("Event handler dispatcher test #1.\n");
	return;
}

void	testeh2()
{
	printf("Event handler dispatcher test #2.\n");
	return;
}

void	testeh3()
{
	printf("Event handler dispatcher test #3.\n");
	return;
}

void	testeh4()
{
	printf("Event handler dispatcher test #4.\n");
	return;
}

void	GPIO5RisingEventHandler()
{
	if(GPIORead(6))
	{
		GPIOWrite(6, 0);
		LCDWrapperClear();
		LCDWrapperPosition(0, 0);
		LCDWrapperPuts("LED OFF");
		clientSendEvents("127.0.0.1", 45000, "LED OFF");
	}
	else
	{
		GPIOWrite(6, 1);
		LCDWrapperClear();
		LCDWrapperPosition(0, 0);
		LCDWrapperPuts("LED ON");
		clientSendEvents("127.0.0.1", 45000, "LED ON");
	}
	return;
	
}


void	LEDOn()
{
	
	GPIOWrite(6, 1);
	LCDWrapperClear();
	LCDWrapperPosition(0, 0);
	LCDWrapperPuts("LED ON");
	
}

void	LEDOff()
{
	
	GPIOWrite(6, 0);
	LCDWrapperClear();
	LCDWrapperPosition(0, 0);
	LCDWrapperPuts("LED OFF");
	
}

void	playMusic()
{
	system("ffplay Thirtyfive.mp3 &");
	return;
}

void	stopMusic()
{
	system("kill $!");
	return;
}
