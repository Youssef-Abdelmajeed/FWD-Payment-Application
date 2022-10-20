#include "string.h"

uint8_t len(uint8_t* str)
{
	uint8_t lenght = 0;
	/*Transverse throght the arr of string to get it's lenght*/
	while (str[lenght] != '\0')
	{
		lenght++;
	}
	return lenght;
}

_Bool isnum(uint8_t* str)
{
	_Bool isnum = 1;
	while ((* str ) != '\0' && isnum)
	{
		/* numbers in ascii table is between DEC(48) and DEC(57) */
		isnum = ((* str) >= 48 && (* str) <= 57||(* str)== '/' )? 1 : 0;
		str++;
	}
	return isnum;
}

_Bool isalphabetic(uint8_t* str)
{
	_Bool isalpha = 1;
	while ((* str) != '\0' && isalpha)
	{
		/* alphabetic charaters in ascii table is between DEC(65) - DEC(90) (uppercase) or DEC(97) - DEC(122) (lowercase) */
		isalpha = (((* str) >= 65 && (* str) <= 90) || ((* str) >= 97 && (* str) <= 122) || ((* str) == ' '))? 1 : 0;
		str++;
	}
	return isalpha;
}