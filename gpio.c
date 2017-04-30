/****************************************************************
gpio.c

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


#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>

#define	MAXGPIO 21

char GPIOMode[MAXGPIO];
char GPIOLastState[MAXGPIO];
char GPIOChangeState[MAXGPIO];

void itoa(int valueIn, char *string, int base)
{
	char *numStrings[] = {"0","1","2","3","4","5"
		,"6","7","8","9"
		,"10","11","12","13","14","15","16"
		,"17","18","19","20","21"};
	strcpy(string, numStrings[valueIn]);

	return;
}

void	GPIOInit()
{
	int i;
	wiringPiSetup();
	for(i=0; i<MAXGPIO; i++) 
	{
		GPIOLastState[i] = 0;
		GPIOChangeState[i] = 0;
	}
	return;
}


void	GPIOOutputMode(int pinNo)
{
	GPIOMode[pinNo] = 1;
	pinMode(pinNo,OUTPUT);

	return;
}


void	GPIOInputMode(int pinNo)
{
	GPIOMode[pinNo] = -1;
	pinMode(pinNo,INPUT);

	return;
}

void	GPIOWrite(int pinNo, int value)
{
	if(value!=0)
	{
		digitalWrite(pinNo,HIGH);
	}
	else
	{
		digitalWrite(pinNo,LOW);
	}
	return;
}

int	GPIORead(int pinNo)
{
	return((int)digitalRead(pinNo));
}

void	GPIOEdgeEventDetect()
{
	int i, currentState;	
	char eventNameString[64],numberString[16]; 

	for(i=0; i<MAXGPIO; i++) 
	{
		currentState = digitalRead(i);
		if((currentState==1)&&(GPIOLastState[i]==0)&&GPIOMode[i]!=0)
		{
			strcpy(eventNameString,"GPIORISE");
			itoa(i, numberString,10);
			strcat(eventNameString, numberString);
			eventQueueEnqueue(eventNameString, strlen(eventNameString)+1);
		}
		else if((currentState==0)&&(GPIOLastState[i]==1)&&GPIOMode[i]!=0)
		{
			strcpy(eventNameString,"GPIOFALL");
			itoa(i, numberString,10);
			strcat(eventNameString, numberString);
			eventQueueEnqueue(eventNameString, strlen(eventNameString)+1);
		}
	
		GPIOLastState[i] = currentState;
	}

	return;
}
				
void	GPIOPolledStateEvent()
{
	int i, currentState;	
	char eventNameString[64],numberString[16]; 

	for(i=0; i<MAXGPIO; i++) 
	{
		currentState = digitalRead(i);
		if(currentState==1)
		{
			strcpy(eventNameString,"GPIOHIGH");
			itoa(i, numberString,10);
			strcat(eventNameString, numberString);
			eventQueueEnqueue(eventNameString, strlen(eventNameString)+1);
		}
		else if(currentState==0)
		{
			strcpy(eventNameString,"GPIOLOW");
			itoa(i, numberString,10);
			strcat(eventNameString, numberString);
			eventQueueEnqueue(eventNameString, strlen(eventNameString)+1);
		}
	

	}

	return;
}

