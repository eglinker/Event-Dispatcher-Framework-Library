/****************************************************************
lcdwrapper.c

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


#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <lcd.h>

static int lcdHandle ;

int	LCDWrapperInit()
{

	lcdHandle = lcdInit (2, 16, 4, 11,10, 0,1,2,3,0,0,0,0) ;
	return;
}

void	LCDWrapperPuts(char *inString)
{
	lcdPuts     (lcdHandle, inString);
	return;
}

void	LCDWrapperClear()
{
	lcdClear(lcdHandle);
	return;
}

void	LCDWrapperPosition(int x, int y)
{
	lcdPosition (lcdHandle, x, y) ;
	return;
}



