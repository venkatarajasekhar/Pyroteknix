// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Util
//      Game-wide utilities.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"


// |----------------------------------------------------------------------------|
// |                                 Debug                                      |
// |----------------------------------------------------------------------------|
void Debug(const char * strText, ...)
{
	if (DEBUG)
	{
		// Unpack the extra arguments (...) using the format specificiation in 
		// strText into strBuffer
		va_list args;
		char strBuffer[4096];

		if (!strText)
			return;

		va_start(args, strText);
		vsprintf(strBuffer, strText, args);
		va_end(args);
		
		printf (strBuffer);
		printf ("\n");
	}
}